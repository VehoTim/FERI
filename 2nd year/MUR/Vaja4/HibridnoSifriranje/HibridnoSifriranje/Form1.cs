using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HibridnoSifriranje
{
    public partial class Form1 : Form
    {
        Stream stream;

        // za izracun vrednosti, ki bo skupna posiljatelju in prejemniku
        // uporabljala se bo pri enkripciji kot geslo
        int izracunVrednosti(int a, int b, int P)
        {
            return ((int)Math.Pow(a, b) % P);
        }

        //enkripcija sporocila s pomocjo rijndael algoritma (AES)
        public static byte[] Encrypt(byte[] clearData, string Password)
        {
            //s pomocjo gesla dobimo pdb, ki ga bomo uporabili pri enkripciji in dekripciji
            PasswordDeriveBytes pdb = new PasswordDeriveBytes(Password, new byte[] {0x49, 0x76, 0x61, 0x6e, 0x20, 0x4d, 0x65, 0x64, 0x76, 0x65, 0x64, 0x65, 0x76});

            MemoryStream ms = new MemoryStream();

            Rijndael alg = Rijndael.Create();

            alg.Key = pdb.GetBytes(32);
            alg.IV = pdb.GetBytes(16);

            CryptoStream cs = new CryptoStream(ms, alg.CreateEncryptor(), CryptoStreamMode.Write);

            cs.Write(clearData, 0, clearData.Length);

            cs.Close();

            return ms.ToArray();
        }

        //dekripcija sporocila s pomocjo rijndael algoritma (AES)
        public static byte[] Decrypt(byte[] cipherData, string Password)
        { 
            PasswordDeriveBytes pdb = new PasswordDeriveBytes(Password, new byte[] {0x49, 0x76, 0x61, 0x6e, 0x20, 0x4d, 0x65, 0x64, 0x76, 0x65, 0x64, 0x65, 0x76});

            MemoryStream ms = new MemoryStream();

            Rijndael alg = Rijndael.Create();

            alg.Key = pdb.GetBytes(32);
            alg.IV = pdb.GetBytes(16);

            CryptoStream cs = new CryptoStream(ms, alg.CreateDecryptor(), CryptoStreamMode.Write);

            cs.Write(cipherData, 0, cipherData.Length);

            cs.Close();

            return ms.ToArray();
        }

        public Form1()
        {
            InitializeComponent();
        }

        // iskanje ip naslova
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

        //branje sporocil
        public static byte[] Beri(Socket client)
        {
            byte[] buffer = new byte[1024];
            int size = client.Receive(buffer);

            return buffer;
        }
        public static byte[] Beri(Stream stream)
        {
            byte[] buffer = new byte[1024];
            int k = stream.Read(buffer, 0, buffer.Length);

            return buffer;
        }

        public static void poslji(byte[] vsebina, Stream stream)
        {
            stream.Write(vsebina, 0, vsebina.Length);
        }

        public static void poslji(byte[] vsebina, Socket socket)
        {
            socket.Send(vsebina);
        }
        private void buttonSend_Click(object sender, EventArgs e)
        {
            UTF8Encoding encoding = new UTF8Encoding();
            Random rnd = new Random();
            TcpClient tcpClient = null;
            string ext = "";
            byte[] fileBytes = null;
            byte[] encryptedtext = null;

            //a je private key
            int a = rnd.Next();
            //P je public key
            int P = rnd.Next();
            //ka bo geslo za enkripcijo in dekripcijo
            int ka = 0;

            //vzpostavitev povezave
            string ip = GetIpAddress();
            try
            {
                tcpClient = new TcpClient();
                tcpClient.Connect(IPAddress.Parse(ip), 1234);
                stream = tcpClient.GetStream();
            }
            catch
            {
                label1.Text = "Prislo je do napake pri povezovanju";
                return;
            }

            //izmenjava kljucev
            try
            {
                //posljemo svoj public key
                poslji(BitConverter.GetBytes(P), stream);

                //prejmemo njihov public key
                byte[] tujKljuc = Beri(stream);

                //izracunamo in posljemo x, ki je vmesna vrednost
                int x = izracunVrednosti(BitConverter.ToInt32(tujKljuc, 0), a, P);
                poslji(BitConverter.GetBytes(x), stream);

                //prejmemo njihovo vmesno vrednost
                byte[] yKey = new byte[1024];
                int k = stream.Read(yKey, 0, yKey.Length);

                //izracunamo geslo za enkripcijo in dekripcijo
                ka = izracunVrednosti(BitConverter.ToInt32(yKey, 0), a, P);
            }
            catch
            {
                label1.Text = "Prislo je do napake pri izmenjavi kljucev";
                return;
            }

            //izberemo datoteko, ki jo zelimo poslati
            try
            {
                OpenFileDialog ofd = new OpenFileDialog
                {
                    InitialDirectory = @"D:\",
                    Title = "Browse Text Files",

                    CheckFileExists = true,
                    CheckPathExists = true,

                    FilterIndex = 2,
                    RestoreDirectory = true,

                    ReadOnlyChecked = true,
                    ShowReadOnly = true
                };

                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    ext = openFileDialog1.SafeFileName;
                }

                label1.Text = ext;
                
                //posljemo ime datoteke in koncnico, da bo nastala datoteka enaka trenutni
                poslji(Encoding.UTF8.GetBytes(ext), stream);
            }
            catch
            {
                label1.Text = "Napaka pri izbiri datoteke";
                return;
            }

            label1.Text = "Posiljanje datoteke...";

            //posiljanje enkriptirane datoteke
            try
            {
                //preberemo bajte datoteke
                fileBytes = File.ReadAllBytes(openFileDialog1.FileName);
                //jih enkriptiramo
                encryptedtext = Encrypt(fileBytes, ka.ToString());
                //posljemo dolzino kriptirane datoteke, da bo prejemnik vedel koliko bajtov mora prebrati
                poslji(BitConverter.GetBytes(encryptedtext.Length), stream);

                //posiljamo bajt po bajt
                for (int i = 0; i < encryptedtext.Length; i++)
                {
                    stream.WriteByte(encryptedtext[i]);

                    //label1.Text = i.ToString() + "/" + (encryptedtext.Length - 1);
                }
            }
            catch
            {
                label1.Text = "Prislo je do napake pri posiljanju kriptiranju datoteke";
                return;
            }

            label1.Text = "Datoteka uspešno poslana";

            tcpClient.Close();
        }

        private void buttonRcv_Click(object sender, EventArgs e)
        {
            Random rnd = new Random();
            //b je private key
            int b = rnd.Next();
            //G je public key
            int G = rnd.Next();
            int kb = 0;
            TcpListener listener = null;
            Socket socket = null;
            byte[] tujKljuc = null;

            label1.Text = "Prejemanje datoteke...";

            //zazenemo poslusalca za prejemnika datoteke
            try
            {
                listener = new TcpListener(IPAddress.Any, 1234);
                listener.Start();

                socket = listener.AcceptSocket();
            }
            catch
            {
                label1.Text = "Prislo je do napake pri vzpostavljanju povezave";
                return;
            }

            //izmenjava kljucev
            try
            {
                //prejmemo public key posiljatelja
                tujKljuc = Beri(socket);
                //posljemo svoj public key
                poslji(BitConverter.GetBytes(G), socket);
                //izracunamo vmesno vrednost
                int y = izracunVrednosti(G, b, BitConverter.ToInt32(tujKljuc, 0));
                //prejmemo vmesno vrednost posiljatelja
                byte[] xKey = Beri(socket);
                //posljemo svojo vmesno vrednost
                poslji(BitConverter.GetBytes(y), socket);
                //izracunamo geslo za dekripcijo
                kb = izracunVrednosti(BitConverter.ToInt32(xKey, 0), b, BitConverter.ToInt32(tujKljuc, 0));
            }
            catch
            {
                label1.Text = "Prislo je do napake pri izmenjavi kljucev";
                return;
            }

            //dobimo ime datoteke
            byte[] bf = Beri(socket);
            string ext = Encoding.UTF8.GetString(bf);

            ext = ext.Replace("\0", "");
            label1.Text = ext;

            //prejmemo dolzino datoteke
            int st = BitConverter.ToInt32(Beri(socket), 0);

            //kriptiran text je te dolzine
            byte[] encryptedText = new byte[st];

            try
            {

                //zacnemo prejemati bajt po bajt in sestavljamo sporocilo
                for (int i = 0; i < st; i++)
                {
                    byte[] buffer = new byte[1];
                    socket.Receive(buffer);
                    encryptedText[i] = buffer[0];

                    //label1.Text = i.ToString () + "/" + (st-1);
                }
            }
            catch 
            { 
                label1.Text = "Prislo je do napake pri prejemanju kriptirane datoteke";
                return;
            }

            //Po potrebi ustvarimo mapo PREJETO
            Directory.CreateDirectory(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "PREJETO"));

            //nastavimo pot kamor bomo shranili novo datoteko
            ext = AppDomain.CurrentDomain.BaseDirectory + "PREJETO\\" + ext;

            label1.Text = ext;

            //ce datoteka ze obstaja jo izbrisemo
            if (File.Exists(@ext)) File.Delete(@ext);

            //
            try
            {
                //dekriptiramo prejeto datoteko
                byte[] decrypted = Decrypt(encryptedText, kb.ToString());

                //shranimo jo v prej doloceno pot
                using (FileStream fs = File.Create(@ext)) fs.Write(decrypted, 0, decrypted.Length);
            }
            catch
            {
                label1.Text = "Prislo je do napake pri dekripciji in shranjevanju datoteke";
                return;
            }

            listener.Stop();
        }
    }
}
