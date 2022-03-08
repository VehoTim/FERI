using System.ComponentModel;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace KlepetGUI
{
    public partial class Form1 : Form
    {
        Stream stream;
        bool connected = false;

        static public string Sifriranje(string besedilo)
        {

            try
            {
                string kljuc = "kljuc";
                TripleDESCryptoServiceProvider tripleDes = new TripleDESCryptoServiceProvider();        //uporabljen za sifriranje sporocila
                MD5CryptoServiceProvider hash = new MD5CryptoServiceProvider();                         //uporabljen za ustvarjanje kljuca prave velikosti iz nasega kljuca

                byte[] byteHash = hash.ComputeHash(Encoding.ASCII.GetBytes(kljuc));                     //s pomocjo kljuca ustvarimo hash, ki bo uporabljen pri sifriranju
                tripleDes.Key = byteHash;                                                               //ta hash shranimo kot kljuc za tripleDes
                tripleDes.Mode = CipherMode.ECB;                                                        //nacin sifriranja (druge moznosti so CBC, CFB)
                byte[] byteBes = Encoding.ASCII.GetBytes(besedilo);

                return Convert.ToBase64String(tripleDes.CreateEncryptor().TransformFinalBlock(byteBes, 0, byteBes.Length)); //sifriramo sporocilo in ga vrnemu programu, ki ga bo poslal naprej
            }
            catch
            {
                return "Sifriranje ni uspelo";
            }
        }

        public static string Desifriranje(string besedilo)
        {
            try
            {
                besedilo = besedilo.Replace("\0", string.Empty);

                string key = "kljuc";
                TripleDESCryptoServiceProvider desCryptoProvider = new TripleDESCryptoServiceProvider();
                MD5CryptoServiceProvider hashMD5Provider = new MD5CryptoServiceProvider();

                byte[] byteHash;
                byte[] byteBuff;

                byteHash = hashMD5Provider.ComputeHash(Encoding.ASCII.GetBytes(key));
                desCryptoProvider.Key = byteHash;
                desCryptoProvider.Mode = CipherMode.ECB; //CBC, CFB
                byteBuff = Convert.FromBase64String(besedilo);

                return Encoding.ASCII.GetString(desCryptoProvider.CreateDecryptor().TransformFinalBlock(byteBuff, 0, byteBuff.Length));
            }
            catch
            {
                return "Desifriranje ni uspelo";
            }
        }

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

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            byte[] prejeto = new byte[1024];                                                //sem se bo shranilo sporocilo serverja

            string ip = GetIpAddress();

            try
            {
                TcpClient client = new TcpClient();
                client.Connect(IPAddress.Parse(ip), 1234);
                richTextBoxVsebina.AppendText("Povezan na naslovu : " + ip + ":" + 1234);

                stream = client.GetStream();

                ASCIIEncoding encoding = new ASCIIEncoding();
                byte[] ba = encoding.GetBytes(Sifriranje("#U" + textBoxUsername.Text));

                stream.Write(ba, 0, ba.Length);      
                
                connected = true;
                backgroundWorker1.RunWorkerAsync();

                textBoxSporocilo.Enabled = true;
                buttonPoslji.Enabled = true;
                buttonPrekini.Enabled = true;
                textBoxUsername.Enabled = false;
                buttonConnect.Enabled = false;
                this.AcceptButton = buttonPoslji;
            }
            catch (Exception ex)
            {
                richTextBoxVsebina.AppendText(ex.StackTrace);
            }
        }

        private void buttonPoslji_Click(object sender, EventArgs e)
        {
            //------------------------------------------------------------------------------------------

            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] ba;
            try
            {
                if (textBoxSporocilo.Text.ToUpper() == "#GAMESTART" || textBoxSporocilo.Text.ToUpper() == "#GAMESTOP")
                {
                    ba = encoding.GetBytes(Sifriranje("#G" + textBoxSporocilo.Text));
                }
                else
                {
                    ba = encoding.GetBytes(Sifriranje("#S" + textBoxSporocilo.Text));
                }

                stream.Write(ba, 0, ba.Length);
            }
            catch
            {
                richTextBoxVsebina.AppendText("Posiljanje je bilo neuspesno");
            }

            textBoxSporocilo.Text = "";
            //------------------------------------------------------------------------------------------
        }

        private void buttonPrekini_Click(object sender, EventArgs e)
        {
            try
            {
                connected = false;
                byte[] ba = Encoding.ASCII.GetBytes(Sifriranje("#P"));
                stream.Write(ba, 0, ba.Length);
                buttonPoslji.Enabled = false;
                textBoxSporocilo.Enabled = false;
                buttonPrekini.Enabled = false;
                buttonConnect.Enabled = true;
                textBoxUsername.Enabled = true;
                this.AcceptButton = buttonConnect;

                backgroundWorker1.CancelAsync();
                stream.Close();
            }
            catch (Exception ex)
            {
                richTextBoxVsebina.Text = ex.Message;
            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            object userObject = e.UserState;
            int percentage = e.ProgressPercentage;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                BackgroundWorker worker = (BackgroundWorker)sender;
                while (!worker.CancellationPending)
                {
                    byte[] bb = new byte[1024];
                    int k = stream.Read(bb, 0, bb.Length);
                    string data = Desifriranje(Encoding.ASCII.GetString(bb));
                    string izpis = data;

                    if (data[0] == '#') izpis = data.Substring(1);

                    if (richTextBoxVsebina.InvokeRequired)
                    {
                        richTextBoxVsebina.Invoke(new MethodInvoker(delegate {
                            richTextBoxVsebina.AppendText("\n");
                            richTextBoxVsebina.AppendText(izpis);
                            richTextBoxVsebina.ScrollToCaret();
                        }));
                    }


                    if (data[0] == '#')
                    {
                        richTextBoxVsebina.Invoke((MethodInvoker)delegate {
                            richTextBoxVsebina.AppendText("\n");
                            richTextBoxVsebina.ScrollToCaret();
                        });
                        worker.Dispose();
                    }
                }
            }
            catch
            {
                richTextBoxVsebina.AppendText("Napaka pri poslušanjo za sporocila (background worker)");
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (connected)
            {
                try
                {
                    connected = false;
                    byte[] ba = Encoding.ASCII.GetBytes(Sifriranje("#P"));
                    stream.Write(ba, 0, ba.Length);
                    buttonPoslji.Enabled = false;
                    textBoxSporocilo.Enabled = false;
                    buttonPrekini.Enabled = false;
                    buttonConnect.Enabled = true;
                    textBoxUsername.Enabled = true;
                    this.AcceptButton = buttonConnect;

                    backgroundWorker1.CancelAsync();
                    stream.Close();
                }
                catch (Exception ex)
                {
                    richTextBoxVsebina.Text = ex.Message;
                }
            }
        }
    }
}