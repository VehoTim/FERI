using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Security.Cryptography;

namespace Vaja02
{
    class TCPClient
    {
        public static string Desifriranje(string kodiranoBesedilo, string kljuc)
        {
            TripleDESCryptoServiceProvider tripleDes = new TripleDESCryptoServiceProvider();        //uporabljen za desifriranje sporocila
            MD5CryptoServiceProvider hash = new MD5CryptoServiceProvider();                         //uporabljen za ustvarjanje kljuca prave velikosti iz nasega kljuca

            byte[] byteHash = hash.ComputeHash(Encoding.ASCII.GetBytes(kljuc));                     //s pomocjo kljuca ustvarimo hash, ki bo uporabljen pri sifriranju
            tripleDes.Key = byteHash;                                                               //ta hash shranimo kot kljuc za tripleDes
            tripleDes.Mode = CipherMode.ECB;                                                        //nacin sifriranja (druge moznosti so CBC, CFB)
            byte[] byteBes = Convert.FromBase64String(kodiranoBesedilo);

            return Encoding.ASCII.GetString(tripleDes.CreateDecryptor().TransformFinalBlock(byteBes, 0, byteBes.Length));
        }

        private static void Main(String[] args)
        {
            byte[] prejeto = new byte[1024];                                                //sem se bo shranilo sporocilo serverja
            
            IPAddress ipNaslov = Dns.GetHostEntry(Dns.GetHostName()).AddressList[1];        
            IPEndPoint ipCilj = new IPEndPoint(ipNaslov, 1234);                             //cilj je ip naslov in vrata preko katerih se bomo povezali (lahko so karkoli)

            string vnos;                    //uporabnikov vnos (glava in sporocilo)
            string paket = "";              //paket bo sestavljen iz glave in sporocila
            bool nadaljuj;                  

            Socket client = new Socket(ipNaslov.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            
            try
            {
                client.Connect(ipCilj);             //posljemo prosnjo za povezavo s serverjem

                //Console.WriteLine("Vtičnica narejena do " + client.RemoteEndPoint.ToString());

                do
                {
                    Console.Write("Vpisi crko (ce bo vnesenih vec crk se bo gledala samo prva): ");
                    vnos = Console.ReadLine();
                    nadaljuj = false;

                    switch (vnos.ToString().ToUpper()[0])
                    {
                        case 'A':
                            paket = vnos;
                            break;
                        case 'B':
                            paket = vnos;
                            break;
                        case 'C':
                            paket = vnos;
                            break;
                        case 'D':
                            paket = vnos;
                            Console.WriteLine("Vpisi sporocilo: ");
                            vnos = Console.ReadLine();
                            paket += vnos;
                            break;
                        case 'E':
                            paket = vnos;
                            break;
                        case 'F':
                            paket = vnos;
                            Console.WriteLine("Vpisi Forsyth-Edwards notacijo: ");
                            vnos = Console.ReadLine();
                            paket += vnos;
                            break;
                        case 'G':
                            paket = vnos;
                            do
                            {
                                Console.WriteLine("Vpisi kljuc (krajsi od 9 znakov): ");
                                vnos = Console.ReadLine();
                            } while (vnos.Length > 9);
                            paket += vnos.Length;
                            paket += vnos;
                            Console.WriteLine("Vpisi sporocilo, ki bo kodirano: ");
                            vnos = Console.ReadLine();
                            paket += vnos;
                            break;
                        default:
                            nadaljuj = true;
                            Console.WriteLine("Vnesel si napacen tip sporocila. Poskusi enega izmed: A/B/C/D/E/F/G");
                            break;
                    }
                } while (nadaljuj);
                
                byte[] sporocilo = Encoding.ASCII.GetBytes(paket);      //paket zapisemo v sporocilo iz bytov

                int n = client.Send(sporocilo);                         //paket posljemo

                int m = client.Receive(prejeto);                        //nazaj prejmemo sporocilo od serverja

                if (paket.ToString().ToUpper()[0] == 'G')               //ce je glava sporocila enaka G, je potrebno se nekaj modifikacij in dekodiranje 
                {
                    string x = Encoding.Default.GetString(prejeto);
                    x = x.Replace("\0", string.Empty);

                    Console.WriteLine(x);
                    Console.WriteLine("Vnesi kljuc za desifriranje?");
                    string kljuc = Console.ReadLine();
                    try
                    {
                        Console.WriteLine(Desifriranje(x, kljuc));
                    }
                    catch
                    {
                        Console.WriteLine("Vnesen je bil napacen kljuc.");
                    }
                }
                else Console.WriteLine(Encoding.Default.GetString(prejeto));

                client.Shutdown(SocketShutdown.Both);
                client.Close();

            }
            catch           //ce se povezava ne izzide izpisemo to sporocilo
            {
                Console.WriteLine("Povezava je neuspesna. Server verjetno ne operatuje.");
            }

            Console.WriteLine("Konec prenašanja.");
        }
    }
}