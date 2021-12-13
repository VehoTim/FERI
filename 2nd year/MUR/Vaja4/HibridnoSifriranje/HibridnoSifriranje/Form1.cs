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

        int izracunVrednosti(int a, int b, int P)
        {
            if (b == 1)
                return a;
            else
                return ((int)Math.Pow(a, b) % P);
        }

        public static byte[] Encrypt(byte[] clearData, byte[] Key, byte[] IV)
        {
            MemoryStream ms = new MemoryStream(); 
            Rijndael alg = Rijndael.Create();
            alg.Key = Key;
            alg.IV = IV;
            CryptoStream cs = new CryptoStream(ms,
               alg.CreateEncryptor(), CryptoStreamMode.Write);

            cs.Write(clearData, 0, clearData.Length);
            cs.Close();

            byte[] encryptedData = ms.ToArray();

            return encryptedData;
        }

        public static byte[] Encrypt(byte[] clearData, string Password)
        {
            PasswordDeriveBytes pdb = new PasswordDeriveBytes(Password,
                new byte[] {0x49, 0x76, 0x61, 0x6e, 0x20, 0x4d,
            0x65, 0x64, 0x76, 0x65, 0x64, 0x65, 0x76});

            return Encrypt(clearData, pdb.GetBytes(32), pdb.GetBytes(16));
        }


        public static byte[] Decrypt(byte[] cipherData, byte[] Key, byte[] IV)
        {
            MemoryStream ms = new MemoryStream();

            Rijndael alg = Rijndael.Create();

            alg.Key = Key;
            alg.IV = IV;

            CryptoStream cs = new CryptoStream(ms,
                alg.CreateDecryptor(), CryptoStreamMode.Write);

            cs.Write(cipherData, 0, cipherData.Length);

            cs.Close();

            byte[] decryptedData = ms.ToArray();

            return decryptedData;
        }

        public static byte[] Decrypt(byte[] cipherData, string Password)
        { 
            PasswordDeriveBytes pdb = new PasswordDeriveBytes(Password, new byte[] {0x49, 0x76, 0x61, 0x6e, 0x20, 0x4d, 0x65, 0x64, 0x76, 0x65, 0x64, 0x65, 0x76});

            return Decrypt(cipherData, pdb.GetBytes(32), pdb.GetBytes(16));
        }


        public Form1()
        {
            InitializeComponent();
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

        public static byte[] Beri(Socket client)
        {
            byte[] buffer = new byte[1024];
            int size = client.Receive(buffer);

            return buffer;
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            UTF8Encoding encoding = new UTF8Encoding();
            int a = 4245;

            string ip = GetIpAddress();
            TcpClient tcpClient = new TcpClient();
            tcpClient.Connect(IPAddress.Parse(ip), 1234);
            stream = tcpClient.GetStream();

            int P = 12123;
            stream.Write(BitConverter.GetBytes(P), 0, BitConverter.GetBytes(P).Length);

            byte[] tujKljuc = new byte[1024];
            int k = stream.Read(tujKljuc, 0, tujKljuc.Length);

            int x = izracunVrednosti(BitConverter.ToInt32(tujKljuc, 0), a, P);

            stream.Write(BitConverter.GetBytes(x), 0, BitConverter.GetBytes(x).Length);

            byte[] yKey = new byte[1024];
            k = stream.Read(yKey, 0, yKey.Length);

            int ka = izracunVrednosti(BitConverter.ToInt32(yKey, 0), a, P);

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

            string ext = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                ext = openFileDialog1.SafeFileName;
            }

            label1.Text = ext;

            stream.Write(Encoding.UTF8.GetBytes(ext), 0, Encoding.UTF8.GetBytes(ext).Length);

            byte[] fileBytes = File.ReadAllBytes(openFileDialog1.FileName);

            byte[] encryptedtext = Encrypt(fileBytes, ka.ToString());

            stream.Write(BitConverter.GetBytes(encryptedtext.Length), 0, BitConverter.GetBytes(encryptedtext.Length).Length);

            for (int i = 0; i < encryptedtext.Length; i++)
            {
                stream.WriteByte(encryptedtext[i]);
            }

            tcpClient.Close();
        }

        private void buttonRcv_Click(object sender, EventArgs e)
        {
            int b = 6544;
            UTF8Encoding encoding = new UTF8Encoding();

            TcpListener listener = new TcpListener(IPAddress.Any, 1234);
            listener.Start();

            Socket socket = listener.AcceptSocket();

            byte[] tujKljuc = Beri(socket);

            int G = 51349;

            socket.Send(BitConverter.GetBytes(G));

            int y = izracunVrednosti(G, b, BitConverter.ToInt32(tujKljuc, 0));

            byte[] xKey = Beri(socket);

            socket.Send(BitConverter.GetBytes(y));

            int kb = izracunVrednosti(BitConverter.ToInt32(xKey, 0), b, BitConverter.ToInt32(tujKljuc, 0));

            byte[] bf = new byte[1024];
            socket.Receive(bf);

            string ext = Encoding.UTF8.GetString(bf);

            label1.Text = ext;

            ext = ext.Replace("\0", "");

            int st = BitConverter.ToInt32(Beri(socket), 0);

            label1.Text = st.ToString();

            byte[] encryptedText = new byte[st];

            for (int i = 0; i < st; i++)
            {
                byte[] buffer = new byte[1];
                socket.Receive(buffer);
                encryptedText[i] = buffer[0];
            }

            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.InitialDirectory = @"C:\";
            saveFileDialog1.Title = "Save text Files";
            saveFileDialog1.CheckPathExists = true;
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                ext = saveFileDialog1.FileName + ext;
            }

            label1.Text = ext;


            if (File.Exists(@ext))
            {
                File.Delete(@ext);
            }

            byte[] decrypted = Decrypt(encryptedText, kb.ToString());
                        
            using (FileStream fs = File.Create(@ext))
            {
                fs.Write(decrypted, 0, decrypted.Length);
            }

            listener.Stop();
        }
    }
}
