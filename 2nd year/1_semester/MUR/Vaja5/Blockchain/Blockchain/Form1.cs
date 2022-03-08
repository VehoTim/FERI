using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Blockchain
{
    public partial class Form1 : Form
    {
        Blok a = null;
        bool connected = true;
        double kumTezavnost = 0;
        Socket listener;
        Socket client;
        Thread threadIskanje;
        Thread threadListener;
        Thread threadValidacija;
        //Thread threadSync;
        //bool sinhronizacija = false;

        private AutoResetEvent _resetEvent = new AutoResetEvent(false);

        public static string GetIpAddress()
        {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip.ToString();
                }
            }
            throw new Exception("Ip naslov ni bil najden");
        }

        //blok spremenimo v byte array za posiljanje po omrezju
        private byte[] BlokToByte(Blok obj)
        {
            string ou = obj.Index.ToString() + ';';
            ou += obj.Ime + ';';
            ou += obj.Data + ';';
            ou += obj.TimeStamp.ToString() + ';';
            ou += obj.Hash + ';';
            ou += obj.PreviousHash + ';';
            ou += obj.Diff.ToString() + ';';
            ou += obj.Nonce.ToString() + ';';

            return Encoding.UTF8.GetBytes(ou);
        }

        //byte array spremenimo v blok
        private Blok ByteToBlok(byte[] arrBytes)
        {
            return new Blok(arrBytes);
        }

        //preverjamo verigo blokov za napake
        private bool Validacija(Blok a)
        {
            if(a != null)
            {
                Blok c = a;
                while (c.Prev != null)
                {
                    //preverimo nas prevHash in hash prejsnjega bloka
                    if (c.PreviousHash != c.Prev.Hash) return false;

                    //preverimo ali je hash pravilne oblike
                    if (Blok.sha256(c.Index + c.Data + c.TimeStamp.ToString() + c.PreviousHash + c.Diff + c.Nonce) != c.Hash) return false;

                    //validacija casovne znacke
                    if ((int)(c.TimeStamp - c.Prev.TimeStamp).TotalSeconds > 60) return false;

                    //pomik nazaj po verigi
                    c = c.Prev;
                }
            }

            return true;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        //povezava
        private void buttonConnect_Click(object sender, EventArgs e)
        {
            bool connect = false;
            buttonConnect.Enabled = false;
            textBoxVrata.Enabled = false;

            //iskanje se ustavi in se bo nadaljevalo po koncu povezovanja
            threadIskanje.Abort();

            //poskusimo se povezati
            try
            {
                IPEndPoint ipCilj = new IPEndPoint(IPAddress.Parse(GetIpAddress()), int.Parse(textBoxVrata.Text));
                    
                client = new Socket(IPAddress.Parse(GetIpAddress()).AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                client.Connect(ipCilj);

                connected = true;

                try
                {
                    //poslje svojo kum. tezavnost
                    client.Send(Encoding.UTF8.GetBytes("#S" + kumTezavnost.ToString()), 0);

                    byte[] data = new byte[1024];
                    client.Receive(data);

                    //prejme sporocilo za zacetek posiljanja
                    string p = Encoding.UTF8.GetString(data, 0, data.Length);

                    //odvisno od tipa sporocila bomo posiljali/prejemali bloke
                    if (p[0] == '#' && p[1] == '0')
                    {
                        int x = 0;
                        int y = a.Index;
                        while (x <= y)
                        {
                            //pomakne se do x bloka v verigi
                            Blok cur = a;
                            while (cur.Index > x)
                            {
                                cur = cur.Prev;
                            }
                            x++;

                            //in ga poslje
                            byte[] podatki = BlokToByte(cur);
                            client.Send(podatki);

                            //prejme potrdilo
                            byte[] s = new byte[1024];
                            client.Receive(s);
                        }

                        //poslje znak za konec posiljanja blokov
                        client.Send(Encoding.UTF8.GetBytes("#x"));
                    }
                    //prejemanje blokov
                    else if (p[0] == '#' && p[1] != '0')
                    {
                        //preberemo novo kum. tezavnost
                        p = p.Replace("\n", String.Empty);
                        int kumTezavnost2 = int.Parse(p.Substring(1));
                        kumTezavnost = kumTezavnost2;
                        //ponastavimo textbox
                        if (richTextBox2.InvokeRequired)
                        {
                            richTextBox2.Invoke(new MethodInvoker(delegate {
                                richTextBox2.Text = "";
                            }));
                        }
                        else
                            richTextBox2.Text = "";

                        //beremo bloke, ki so nam posiljani
                        while (true)
                        {
                            client.Send(Encoding.UTF8.GetBytes("Ok"));

                            data = new byte[1024];
                            client.Receive(data);

                            string prev = Encoding.UTF8.GetString(data, 0, data.Length);

                            //ce prejmemo #x smo prejeli vse bloke
                            if (prev[0] == '#' && prev[1] == 'x')
                            {
                                break;
                            }

                            //prejme ta x blok in doda v svojo zbirko
                            a = ByteToBlok(data);

                            //ga izpise
                            if (richTextBox2.InvokeRequired)
                            {
                                richTextBox2.Invoke(new MethodInvoker(delegate {
                                    richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");
                                }));
                            }
                            else
                                richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");

                            //ponovi
                        }
                    }
                }
                catch (Exception ex) {
                    richTextBox1.Text = ex.Message;
                }
            }
            // ce ne uspe naredimo listener
            catch
            {
                connect = true;
            }
            if (connect)
            {
                threadListener = new Thread(RunListener);
                threadListener.Start();
            }

            richTextBox1.SelectionColor = Color.Green;
            richTextBox1.AppendText("Povezano na vratih" + textBoxVrata.Text + "\n");
            richTextBox1.SelectionColor = Color.Black;
            richTextBox1.ScrollToCaret();

            //nadaljuje se iskanje blokov
            threadIskanje = new Thread(() =>
            {
                iskanjeBlokov(ref a);
            });

            threadIskanje.Start();

            {

                /*threadSync = new Thread(() =>
                {
                    while (true)
                    {
                        Thread.Sleep(10000);

                        sinhronizacija = true;

                        if (buttonDisconnect.InvokeRequired)
                        {
                            buttonDisconnect.Invoke(new MethodInvoker(delegate {
                                buttonDisconnect.PerformClick();
                            }));
                        }
                    }
                });

                threadSync.Start();*/
            }
        }

        private void RunListener()
        {
            IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Parse(GetIpAddress()), int.Parse(textBoxVrata.Text));

            listener = new Socket(IPAddress.Parse(GetIpAddress()).AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            listener.Bind(localEndPoint);

            listener.Listen(1000);

            while (true)
            {
                //poslusamo za p2p povezavo
                client = listener.Accept();
                connected = true;

                //prejmemo pozdrav
                byte[] data = new byte[1024];
                client.Receive(data);

                string prejeto = Encoding.UTF8.GetString(data, 0, data.Length);

                //preverimo da je pravega tipa
                if(prejeto[1] == 'S')
                {
                    //prejme njegovo kumTezavnost
                    int kumTezavnost2 = int.Parse(prejeto.Substring(2, prejeto.Length - 2));

                    //glede na prejeto kum. tezavnost bomo posiljali/prejemali bloke
                    if (kumTezavnost2 > kumTezavnost)
                    {
                        kumTezavnost = kumTezavnost2;
                        //spraznimo textbox
                        if (richTextBox2.InvokeRequired)
                        {
                            richTextBox2.Invoke(new MethodInvoker(delegate {
                                richTextBox2.Text = "";
                            }));
                        }
                        else
                            richTextBox2.Text = "";

                        //poslje sporocilo za zacetek posiljanja
                        client.Send(Encoding.UTF8.GetBytes("#0"));

                        //zacnemo prejemati bloke
                        while (true)
                        {
                            data = new byte[1024];
                            client.Receive(data);

                            string prev = Encoding.UTF8.GetString(data, 0, data.Length);

                            //koncamo prejemanje ko dobimo #x
                            if (prev[0] == '#' && prev[1] == 'x')
                            {
                                break;
                            }

                            //prejme ta x blok
                            a = ByteToBlok(data);

                            //ga izpise
                            if (richTextBox2.InvokeRequired)
                            {
                                richTextBox2.Invoke(new MethodInvoker(delegate {
                                    richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");
                                }));
                            }
                            else
                                richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");

                            //ponovi

                            client.Send(Encoding.UTF8.GetBytes("Ok"));
                        }
                    }
                    //drugace posiljamo bloke
                    else
                    {
                        //poslje sporocilo za zacetek posiljanja in svojo tezavnost
                        client.Send(Encoding.UTF8.GetBytes("#" + kumTezavnost));

                        int x = 0;
                        int y = a.Index;
                        while (x <= y)
                        {
                            byte[] s = new byte[1024];
                            client.Receive(s);

                            //pomakne se do x bloka v verigi
                            Blok cur = a;
                            while (cur.Index > x)
                            {
                                cur = cur.Prev;
                            }
                            x++;

                            //in ga poslje
                            byte[] podatki = BlokToByte(cur);
                            client.Send(podatki);
                        }
                        //#x za konec posiljanja blokov
                        client.Send(Encoding.UTF8.GetBytes("#x"));
                    }
                }
            }
        }

        //funkcija za iskanje blokov
        private void iskanjeBlokov(ref Blok x)
        {
            a = new Blok(x, textBoxIme.Text);
            kumTezavnost += Math.Pow(2, a.Diff);

            //validacija casovne znacke
            if((int)(DateTime.Now - a.TimeStamp).TotalSeconds > 60)
            {
                threadIskanje.Abort();  
                return;
            }

            //izpis prvega bloka
            if (richTextBox2.InvokeRequired)
            {
                richTextBox2.Invoke(new MethodInvoker(delegate {
                    richTextBox2.SelectionColor = Color.Purple;
                    richTextBox2.AppendText("Kum tezavnost: " + kumTezavnost + "\n");
                    richTextBox2.SelectionColor = Color.Black;
                    richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");

                    richTextBox2.ScrollToCaret();
                }));
            }

            //dodajanje ostalih blokov
            while (buttonZacni.Enabled == false)
            {
                Blok b = new Blok(a, textBoxIme.Text);

                //validacija casovne znacke
                if ((int)(DateTime.Now - b.TimeStamp).TotalSeconds > 60)
                {
                    threadIskanje.Abort();
                    return;
                }

                //ce je blok vredu se doda v naso verigo
                a = b;
                //popravi se kum. tezavnost
                kumTezavnost += Math.Pow(2, a.Diff);

                //izpis bloka
                if (richTextBox2.InvokeRequired)
                {
                    richTextBox2.Invoke(new MethodInvoker(delegate {
                        richTextBox2.SelectionColor = Color.Purple;
                        richTextBox2.AppendText("Kum tezavnost: " + kumTezavnost + "\n");
                        richTextBox2.SelectionColor = Color.Black;
                        richTextBox2.AppendText("Index: " + a.Index + "\nIme: " + a.Ime + "\nData: " + a.Data + "\nCas: " + a.TimeStamp + "\nHash: " + a.Hash + "\nPrejsnji hash: " + a.PreviousHash + "\nTezavnos: " + a.Diff + "\nZeton: " + a.Nonce + "\n");

                        richTextBox2.ScrollToCaret();
                    }));
                }
            }

            _resetEvent.Set();
        }

        private void buttonDisconnect_Click(object sender, EventArgs e)
        {
            connected = false;
            threadValidacija.Abort();
            //ce je listener ga ustavimo, drugace ustavimo client
            if (listener != null)
            {
                listener.Close();
                threadListener.Abort();
            }
            else client.Close();

            //ustavimo iskanje
            threadIskanje.Abort();
            //threadSync.Abort();

            buttonZacni.Enabled = true;
            buttonConnect.Enabled = true;
            textBoxIme.Enabled = true;
            textBoxVrata.Enabled = true;

            {
                /*if (sinhronizacija)
                {
                    sinhronizacija = false;
                    if (richTextBox1.InvokeRequired)
                    {
                        richTextBox1.Invoke(new MethodInvoker(delegate {
                            richTextBox1.AppendText("Sinhronizacija\n");
                        }));
                    }
                    else richTextBox1.AppendText("Sinhronizacija\n");

                    if (buttonZacni.InvokeRequired)
                    {
                        buttonZacni.Invoke(new MethodInvoker(delegate {
                            buttonZacni.PerformClick();
                        }));
                    }
                    else buttonZacni.PerformClick();

                    if (buttonConnect.InvokeRequired)
                    {
                        buttonConnect.Invoke(new MethodInvoker(delegate {
                            buttonConnect.PerformClick();
                        }));
                    }
                    else buttonConnect.PerformClick();
                    return;
                }*/
            }

            richTextBox1.AppendText("Prekinjeno delovanje\n");
        }

        private void buttonZacni_Click(object sender, EventArgs e)
        {
            richTextBox1.AppendText("Zacel iskanje blokov\n");
            buttonZacni.Enabled = false;
            textBoxIme.Enabled = false;

            //nit za iskanje blokov
            threadIskanje = new Thread(() =>
            {
                iskanjeBlokov(ref a);
            });

            threadIskanje.Start();

            //nit za validacijo vsakih 10s
            threadValidacija = new Thread(() =>
            {
                while (true)
                {
                    Thread.Sleep(10000);
                    try
                    {
                        if (richTextBox1.InvokeRequired)
                        {
                            if (!Validacija(a))
                            {
                                richTextBox1.Invoke(new MethodInvoker(delegate
                                {
                                    richTextBox1.SelectionColor = Color.Red;
                                    richTextBox1.AppendText("!!!NAPAKA NAPAKA NAPAKA!!!\n");
                                    richTextBox1.SelectionColor = Color.Black;
                                    richTextBox1.ScrollToCaret();
                                }));
                            }
                            else
                            {
                                richTextBox1.Invoke(new MethodInvoker(delegate
                                {
                                    richTextBox1.SelectionColor = Color.Green;
                                    richTextBox1.AppendText("Validacija uspesna\n");
                                    richTextBox1.SelectionColor = Color.Black;
                                    richTextBox1.ScrollToCaret();
                                }));
                            }
                        }
                    }
                    catch {
                        richTextBox1.AppendText("Napaka pri validaciji");
                    }
                }
            });

            threadValidacija.Start();
        }
    }
}
