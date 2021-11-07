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
        static public bool PreveriFEN(string s)
        {
            int v = 0;
            int skupaj = 0;
            int vrstica = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] == '/' && v != 8) return false;
                else if (s[i] == '/' && v == 8)
                {
                    v = 0;
                    vrstica++;
                    continue;
                }
                else if (Char.IsDigit(s[i]))
                {
                    v += int.Parse(s[i].ToString());
                    skupaj += int.Parse(s[i].ToString());
                    vrstica++;
                }
                else if (Char.IsLetter(s[i]))
                {
                    v++;
                    skupaj++;
                    vrstica++;
                }
                else if (skupaj == 64) break;
            }

            int stPresledkov = 0;

            for (int i = vrstica; i < s.Length; i++)
            {
                if (s[i] == ' ')
                {
                    stPresledkov++;
                    continue;
                }
                else if (s[i].ToString().ToLower() == "w" || s[i].ToString().ToLower() == "b" && stPresledkov == 1) continue;
                else if ((s[i] == 'k' || s[i] == 'q' || s[i] == 'K' || s[i] == 'Q' || s[i] == '-') && stPresledkov == 2) continue;
                else if(s[i] == '-' || Char.IsLetter(s[i]) && stPresledkov == 3)
                {
                    if (Char.IsLetter(s[i]) && Char.IsDigit(s[i + 1])) i++;
                    continue;
                }
                else if (Char.IsDigit(s[i]) && stPresledkov > 3) continue;
                else return false;
            }

            return true;
        }

        static public string FEN(string s)                  //FEN funkcija za Forsyth-Edwards notacijo
        {
            if (!PreveriFEN(s)) return "Ni pravilna FEN oblika";
            string odgovor = "";                            //v odgovor se bo sestavljalo sporocilo streznika
            int v = 0;                                      //spremenljivka v je da vem kdaj se vrstica konča (vsaka vrstica v sahu ima 8 mest)
            for (int i = 0; i < s.Length; i++)
            {
                if (v == 8) odgovor += '\n';
                if (Char.IsLetter(s[i]))                    //ce je crko jo izpisemo in povecamo v
                {
                    odgovor += s[i];
                    v++;
                }
                else if (Char.IsDigit(s[i]))                //ce je stevilka izpisemo toliko presledkov kolikor je stevilka in povecujemo v
                {
                    for (int j = 0; j < int.Parse(s[i].ToString()); j++)
                    {
                        odgovor += ' ';
                        v++;
                    }
                }
                else if (s[i] == '/')                       //znak / oznacuje konec vrstice (v postavimo na 0 in nadaljujemo)
                {
                    v = 0;
                    continue;
                }
                else if (s[i] == ' ')                       //ko pridemo do presledka pomeni da smo koncali z izrisovanjem polja
                {
                    //dolocitev kdo je na potezi
                    if (s[i + 1] == 'w') odgovor += "\n\nNa vrsti beli";
                    else odgovor += "\n\nNa vrsti crni";

                    //dolocitev mogocih rokad
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

                    //dolocitev ali je mogoce izvesti en passant in izpis kje je mogoc
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

                    //izpis polpotez in potez
                    odgovor += "\n\nStevilo polpotez: " + s[i + j];
                    j += 2;
                    odgovor += "\n\nStevilka trenutne poteze: " + s[i + j];
                    break;
                }
            }
            
            return odgovor;
        }

        static public string Sifriranje(string besedilo, string kljuc)
        {
            TripleDESCryptoServiceProvider tripleDes = new TripleDESCryptoServiceProvider();        //uporabljen za sifriranje sporocila
            MD5CryptoServiceProvider hash = new MD5CryptoServiceProvider();                         //uporabljen za ustvarjanje kljuca prave velikosti iz nasega kljuca

            byte[] byteHash = hash.ComputeHash(Encoding.ASCII.GetBytes(kljuc));                     //s pomocjo kljuca ustvarimo hash, ki bo uporabljen pri sifriranju
            tripleDes.Key = byteHash;                                                               //ta hash shranimo kot kljuc za tripleDes
            tripleDes.Mode = CipherMode.ECB;                                                        //nacin sifriranja (druge moznosti so CBC, CFB)
            byte[] byteBes = Encoding.ASCII.GetBytes(besedilo);

            return Convert.ToBase64String(tripleDes.CreateEncryptor().TransformFinalBlock(byteBes, 0, byteBes.Length)); //sifriramo sporocilo in ga vrnemu programu, ki ga bo poslal naprej
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
                        int dolzina = int.Parse(data[0].ToString());
                        data = data.Remove(0, 1);
                        string key = data.Substring(0, dolzina);
                        data = data.Remove(0, dolzina);
                        string x = Sifriranje(data, key);
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