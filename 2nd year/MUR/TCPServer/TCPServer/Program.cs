using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Security.Cryptography;

namespace Vaja02
{
    class TCPServer
    {
        static public string FEN(string s)
        {
            string odgovor = "";
            int v = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (v == 8) odgovor += '\n';
                if (Char.IsLetter(s[i]))
                {
                    odgovor += s[i];
                    v++;
                }
                else if (Char.IsDigit(s[i]))
                {
                    for (int j = 0; j < int.Parse(s[i].ToString()); j++)
                    {
                        //s[i];
                        odgovor += ' ';
                        v++;
                    }
                }
                else if (s[i] == '/')
                {
                    v = 0;
                    continue;
                }
                else if (s[i] == ' ')
                {
                    if (s[i + 1] == 'w') odgovor += "\n\nNa vrsti beli";
                    else odgovor += "\n\nNa vrsti crni";

                    odgovor += "\n\nMoznosti rokade:";
                    int j = 3;
                    while (s[i + j] != ' ' && s[i + j] != '-')
                    {
                        if (s[i + j] == 'K')
                            odgovor += "\nBeli kraljeva stran";
                        if (s[i + j] == 'Q')
                            odgovor += "\nBeli damina stran";
                        if (s[i + j] == 'k')
                            odgovor += "\nCrni kraljeva stran";
                        if (s[i + j] == 'q')
                            odgovor += "\nCrni damina stran";
                        j++;
                    }
                    j++;

                    odgovor += "\n\nMoznosti en passant:";
                    if (s[i + j] == '-')
                    {
                        odgovor += "ne";
                        j++;
                    }
                    else
                    {
                        odgovor += s[i + j].ToString() + s[i + j + 1].ToString();
                        j += 2;
                    }
                    j++;

                    odgovor += "\n\nStevilo polpotez: " + s[i + j];
                    j += 2;
                    odgovor += "\n\nStevilka trenutne poteze: " + s[i + j];
                    break;
                }
            }
            
            return odgovor;
        }

        static public string Encrypt(string source, string key)
        {
            TripleDESCryptoServiceProvider desCryptoProvider = new TripleDESCryptoServiceProvider();
            MD5CryptoServiceProvider hashMD5Provider = new MD5CryptoServiceProvider();

            byte[] byteHash;
            byte[] byteBuff;

            byteHash = hashMD5Provider.ComputeHash(Encoding.ASCII.GetBytes(key));
            desCryptoProvider.Key = byteHash;
            desCryptoProvider.Mode = CipherMode.ECB; //CBC, CFB
            byteBuff = Encoding.ASCII.GetBytes(source);

            string encoded =
                Convert.ToBase64String(desCryptoProvider.CreateEncryptor().TransformFinalBlock(byteBuff, 0, byteBuff.Length));
            return encoded;
        }

        static void Main(string[] args)
        {
            byte[] buffer = new byte[1024];                             //en byte za glavo prejetega paketa ostalo za sporocilo (maksimalna dolzina sporocila v tem primeru je 1023)
            string data = null;                                         //sem se bo shranila vsebina prejetega sporocila
            char header;                                                //sem se bo shranila glava prejetega sporocila

            byte[] msg = Encoding.ASCII.GetBytes("");                   //to bo poslano clientu


            IPAddress ipNaslov = Dns.GetHostEntry(Dns.GetHostName()).AddressList[0];    
            IPEndPoint cilj = new IPEndPoint(ipNaslov, 1234);                           //cilj je ip naslov in vrata preko katerih se bomo povezali (lahko so karkoli)

            Socket vticnica = new Socket(ipNaslov.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            vticnica.Bind(cilj);                                        //povezemo vticnico z ciljem
            vticnica.Listen(100);

            while (true)
            {

                Console.WriteLine("\nPoslušam na naslovu " + vticnica.LocalEndPoint.ToString());
                Socket povezava = vticnica.Accept();                                                        //sprejmemo prosnjo za povezavo z clientom, ko ta pride
                Console.WriteLine("\nOdjemalec se je povezal na " + povezava.LocalEndPoint.ToString());

                int b = povezava.Receive(buffer);                       //dolzina paketa
                data += Encoding.ASCII.GetString(buffer, 0, b);         //paket shranimo v string

                header = data.ToString().ToUpper()[0];                  //ter ga locimo na glavo in sporocilo
                Console.WriteLine("Glava sporocila: " + header);
                data = data.Remove(0, 1);
                Console.WriteLine("Vsebina sporocila: " + data);

                switch (header)
                {
                    case 'A':
                        msg = Encoding.ASCII.GetBytes("Pozdravljen " + povezava.LocalEndPoint.ToString());
                        break;
                    case 'B':
                        msg = Encoding.ASCII.GetBytes("Trenutni cas je " + DateTime.Now);
                        break;
                    case 'C':
                        msg = Encoding.ASCII.GetBytes("Trenuten delovni direktorij je " + Directory.GetCurrentDirectory());
                        break;
                    case 'D':
                        msg = Encoding.ASCII.GetBytes(data.ToString());
                        break;
                    case 'E':
                        msg = Encoding.ASCII.GetBytes("Ime naprave: " + Environment.MachineName + ", verzija os: " + Environment.OSVersion);
                        break;
                    case 'F':
                        msg = Encoding.ASCII.GetBytes(FEN(data));
                        break;
                    case 'G':
                        string x = Encrypt(data, "mykey");
                        msg = Encoding.ASCII.GetBytes(x);
                        break;
                    default:
                        msg = Encoding.ASCII.GetBytes("Vnesel si napačen tip sporočila. Poskusi enega izmed: A/B/C/D/E/F/G");
                        break;
                }
                data = null;

                Console.WriteLine("Odgovoril sem: " + Encoding.Default.GetString(msg));
                povezava.Send(msg);
                povezava.Close();
            }
        }
    }
}