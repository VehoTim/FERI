using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Security.Cryptography;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Vaja02
{

    class TCPServer
    {
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
        
        public static string Beri(Socket client)
        {
            try
            {
                byte[] buffer = new byte[1024];
                int size = client.Receive(buffer);

                return Desifriranje(Encoding.ASCII.GetString(buffer, 0, size));
            }
            catch
            {
                return "Napaka pri prejemu sporocila";
            }
        }

        public static bool Logika(string data, Socket[] seznam, string[] imena, ref int[] tockovnik, int cur, int stSocket, ref bool igranje, ref string beseda, ASCIIEncoding asen)
        {
            string head;

            if (data.Length < 2) return true;

            if (data.Length <= 2) head = data;
            else head = data.Substring(0, 2);

            switch (head)
            {
                case "#S":
                    data = data.Remove(0, 2);

                    Console.Write(head + "| ");
                    Console.Write(data + "=" + imena[cur]);
                    Console.WriteLine("");

                    string vsebina = data;

                    data = imena[cur] + ": " + data;

                    for (int i = 0; i < stSocket; i++)
                    {
                        if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje(data)));
                    }

                    if (igranje)
                    {
                        if (vsebina.ToLower() == beseda)
                        {
                            tockovnik[cur]++;

                            beseda = Igra(stSocket, seznam);

                            IzpisTock(stSocket, seznam, imena, tockovnik, true, beseda);
                        }
                    }
                    break;
                case "#G":
                    data = data.Remove(0, 2);

                    Console.Write(head + "| ");
                    Console.Write(data + "=" + imena[cur]);
                    Console.WriteLine("");

                    if (data.ToUpper() == "#GAMESTART") igranje = true;
                    /*else if(data.ToUpper() == "#GAMESTOP" && igranje == false)
                    {
                        for (int i = 0; i < stSocket; i++)
                        {
                            if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje("Igra trenutno ne poteka")));
                            return true;
                        }
                    }*/
                    else igranje = false;

                    data = imena[cur] + ": " + data;

                    for (int i = 0; i < stSocket; i++)
                    {
                        if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje(data)));
                    }

                    if (!igranje)
                    {
                        data = imena[cur] + " je ustavil igro\n";

                        for (int i = 0; i < stSocket; i++)
                        {
                            if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje(data)));
                        }

                        IzpisTock(stSocket, seznam, imena, tockovnik, false, "");
                    }
                    else
                    {
                        beseda = Igra(stSocket, seznam);

                        string poslji = "";
                        for (int i = 0; i < beseda.Length; i++)
                        {
                            if (i % 2 == 0) poslji += beseda[i];
                            else poslji += '_';
                        }

                        for (int i = 0; i < stSocket; i++) if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje("Ugani besedo: " + poslji)));
                    }
                    break;
                case "#P":
                    Console.Write(head + "| ");
                    Console.Write(data + "=" + imena[cur]);
                    Console.WriteLine("");
                    for (int i = 0; i < stSocket; i++)
                    {
                        if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje("#" + imena[cur] + " je prekinil povezavo")));
                    }
                    //dodatno: implementacija ponovne prijave z istim imenom
                    imena[cur] = "#" + imena[cur];
                    seznam[cur] = null;
                    return false;
                default:
                    break;
            }
            return true;
        }

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

        static public string Igra(int stSocket, Socket[] seznam)
        {
            try
            {
                Random rnd = new Random();
                string[] besede = new string[8] { "mrezno", "usmerjeno", "racunanje", "beseda", "vehovar", "nakljucje", "slovenija", "sumniki" };

                return besede[rnd.Next(besede.Length)];
            }
            catch
            {
                return "Napaka pri generiranju nakljucne besede";
            }
        }

        static public void IzpisTock(int stSocket, Socket[] seznam, string[] imena, int[] tockovnik, bool nxt, string beseda)
        {
            string data;
            ASCIIEncoding asen = new ASCIIEncoding();
            for (int i = 0; i < stSocket; i++)
            {
                data = "";
                data += "Rezultati:";
                for (int j = 0; j < stSocket; j++)
                {
                    data += "\n*" + imena[j] + " - " + tockovnik[j];
                }

                string poslji = "";
                for (int j = 0; j < beseda.Length; j++)
                {
                    if (j % 2 == 0) poslji += beseda[j];
                    else poslji += '_';
                }
                try
                {
                    if (seznam[i] != null)
                    {
                        if (nxt) seznam[i].Send(asen.GetBytes(Sifriranje(data + "\nUgani besedo: " + poslji)));
                        else seznam[i].Send(asen.GetBytes(Sifriranje(data)));
                    }
                }
                catch
                {
                    Console.WriteLine("Napaka pri izpisu tock");
                }
            }
        }

        static void Main(string[] args)
        {
            //spremenljivke

            string data;                                         
            bool igranje = false;
            string beseda = "";
            string head = "";
            int stSocket = 0;
            string ip;

            Socket[] seznam = new Socket[32];
            String[] imena = new String[32];
            int[] tockovnik = new int[32];

            ASCIIEncoding asen = new ASCIIEncoding();

            TcpListener listener = null;
            Socket client = null;

            //----------------------------------------------------------------------------

            //vzpostavitev serverja in poslusalca

            try
            {
                ip = GetIpAddress();

                listener = new TcpListener(IPAddress.Any, 1234);
                listener.Start();
                Console.WriteLine("Server zagnan na: " + ip + ":" + 1234);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                Console.WriteLine("Vzpostavitev serverja je neuspesna.");

                Environment.Exit(1);
            }

            //----------------------------------------------------------------------------

            //zanka za poslusanje novih uporabnikov

            while (true)
            {
                try
                {
                    client = listener.AcceptSocket();
                }
                catch
                {
                    Console.WriteLine("Uporabnik ni mogel biti sprejet");
                    continue;
                    //break;
                }

                data = Beri(client);
                
                //locimo na glavo in vsebino
                head = data[0].ToString() + data[1].ToString();
                data = data.Substring(2);

                //vsebina
                seznam[stSocket] = client;
                imena[stSocket] = data;
                tockovnik[stSocket] = 0;

                Console.Write(head + "| ");
                Console.WriteLine(data);

                for (int i = 0; i < stSocket + 1; i++)
                {
                    if (seznam[i] != null) seznam[i].Send(asen.GetBytes(Sifriranje(data + " se je povezal")));
                }

                //ustvarimo nit

                try
                {
                    var thread = new Thread(() =>
                    {
                        ASCIIEncoding asen = new ASCIIEncoding();
                        stSocket++;
                        int cur = stSocket - 1;
                        bool izvajaj = true;

                        Socket nit = client;

                        while (izvajaj)
                        {
                            data = Beri(nit);

                            izvajaj = Logika(data, seznam, imena, ref tockovnik, cur, stSocket, ref igranje, ref beseda, asen);
                        }

                        nit.Close();
                    });

                    thread.Start();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                    Console.WriteLine("");
                }

                //----------------------------------------------------------------------------

            }

            //----------------------------------------------------------------------------

            listener.Stop();
        }
    }
}