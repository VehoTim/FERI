using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;
using System.Security.Cryptography;

namespace HibridnoSifriranje
{
    public partial class Form1 : Form
    {
        Stream stream;
        DH_AES uporabnik = new DH_AES();

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
            byte[] buffer = new byte[140];
            int size = client.Receive(buffer);

            return buffer;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void buttonPosiljanje_click(object sender, EventArgs e)
        {
            UTF8Encoding encoding = new UTF8Encoding();

            string ip = GetIpAddress();
            TcpClient tcpClient = new TcpClient();
            tcpClient.Connect(IPAddress.Parse(ip), 1234);
            stream = tcpClient.GetStream();

            byte[] publicKey= uporabnik.PubKey;
            stream.Write(publicKey, 0, publicKey.Length);

            byte[] tujKljuc = new byte[140];
            int k = stream.Read(tujKljuc, 0, tujKljuc.Length);

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
            }

            byte[] fileBytes = File.ReadAllBytes(openFileDialog1.FileName);
            fileBytes = uporabnik.Encrypt(tujKljuc, fileBytes);
            stream.Write(fileBytes, 0, fileBytes.Length);
        }

        private void buttonPrejemanje_click(object sender, EventArgs e)
        {
            UTF8Encoding encoding = new UTF8Encoding();

            TcpListener listener = new TcpListener(IPAddress.Any, 1234);
            listener.Start();

            Socket socket = listener.AcceptSocket();

            byte[] tujKljuc = Beri(socket);

            socket.Send(uporabnik.PubKey);

            byte[] sporocilo = Beri(socket);

            if (File.Exists(@"D:\meh.txt"))
            {
                File.Delete(@"D:\meh.txt");
            }

            string s = uporabnik.Decrypt(tujKljuc, sporocilo, uporabnik.IV);

            // Create a new file     
            using (FileStream fs = File.Create(@"D:\meh.txt"))
            {
                // Add some text to file    
                fs.Write(sporocilo, 0, sporocilo.Length);
            }
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }
    }

    class DH_AES : IDisposable
    {
        private Aes aes = null;
        private ECDiffieHellmanCng dh = null;

        private readonly byte[] pubKey;

        public DH_AES()
        {
            this.aes = new AesCryptoServiceProvider();

            this.dh = new ECDiffieHellmanCng
            {
                KeyDerivationFunction = ECDiffieHellmanKeyDerivationFunction.Hash,
                HashAlgorithm = CngAlgorithm.Sha256
            };

            this.pubKey = this.dh.PublicKey.ToByteArray();
        }

        public byte[] PubKey
        {
            get { return this.pubKey; }
        }

        public byte[] IV
        {
            get
            {
                return this.aes.IV;
            }
        }

        public byte[] Encrypt(byte[] pubKey, byte[] data)
        {
            byte[] encData;
            var key = CngKey.Import(pubKey, CngKeyBlobFormat.EccPublicBlob);
            var novKey = this.dh.DeriveKeyMaterial(key);

            this.aes.Key = novKey;

            using (var cData = new MemoryStream())
            {
                using (var encryptor = this.aes.CreateEncryptor())
                {
                    using (var cryptoStream = new CryptoStream(cData, encryptor, CryptoStreamMode.Write))
                    {
                        byte[] cipherTxtMessage = data;
                        cryptoStream.Write(cipherTxtMessage, 0, cipherTxtMessage.Length);
                    }
                }
                encData = cData.ToArray();
            }
            return encData;
        }

        public string Decrypt(byte[] publicKey, byte[] encryptedMessage, byte[] iv)
        {
            string decryptedMessage;
            var key = CngKey.Import(publicKey, CngKeyBlobFormat.EccPublicBlob);
            var derivedKey = this.dh.DeriveKeyMaterial(key);

            this.aes.Key = derivedKey;
            this.aes.IV = iv;

            using (var plainText = new MemoryStream())
            {
                using (var decryptor = this.aes.CreateDecryptor())
                {
                    using (var cryptoStream = new CryptoStream(plainText, decryptor, CryptoStreamMode.Write))
                    {
                        cryptoStream.Write(encryptedMessage, 0, encryptedMessage.Length);
                    }
                }

                decryptedMessage = Encoding.UTF8.GetString(plainText.ToArray());
            }

            return decryptedMessage;
        }
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (this.aes != null)
                    this.aes.Dispose();

                if (this.dh != null)
                    this.dh.Dispose();
            }
        }
    }
}
