using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Blockchain
{
    internal class Blok
    {
        private int index;
        private string ime;
        private string data;
        private DateTime timeStamp;
        private string hash;
        private string previousHash;
        private Blok prev;
        private int diff;
        private ulong nonce = 0;

        private int searchingTime;

        private int timeExpected = 10;
        private int count = 10;

        public int Index
        {
            get { return index; }
            set { index = value; }
        }
        public string Data
        {
            get { return data; }
            set { data = value; }
        }
        public DateTime TimeStamp
        {
            get { return timeStamp; }
            set { timeStamp = value; }
        }
        public int Diff
        {
            get { return diff; }
            set { diff = value; }
        }
        public string Hash
        {
            get { return hash; }
            set { hash = value; }
        }
        public string PreviousHash
        {
            get { return previousHash; }
            set { previousHash = value; }
        }
        public ulong Nonce
        {
            get { return nonce; }
            set { nonce = value; }
        }
        public Blok Prev
        {
            get { return prev; }
            set { prev = value; }
        }
        public string Ime
        {
            get { return ime; }
            set { ime = value; }
        }

        public Blok(string ime)
        {
            index = 0;
            this.ime = ime;
            data = "block" + index + "data";
            timeStamp = DateTime.Now;
            previousHash = "";
            diff = 5;
            while (true)
            {
                hash = sha256(index + data + timeStamp.ToString() + previousHash + diff + nonce);
                if (ustrezenHash(hash, diff)) break;
                else nonce++;
            }
            searchingTime = 0;
            prev = null;
        }

        public Blok(Blok a, string ime)
        {
            //pomeni da bo prvi
            if(a == null)
            {
                index = 0;
                this.ime = ime;
                data = "block" + index + "data";
                timeStamp = DateTime.Now;
                previousHash = "";
                diff = 5;
                while (true)
                {
                    hash = sha256(index + data + timeStamp.ToString() + previousHash + diff + nonce);
                    if (ustrezenHash(hash, diff)) break;
                    else nonce++;
                }
                searchingTime = 0;
                prev = null;
            }
            //drugace dodamo v verigo
            else
            {
                index = a.Index + 1;
                this.ime = ime;
                data = "block" + index + "data";
                timeStamp = DateTime.Now;
                previousHash = a.hash;

                diff = a.diff;

                if (index % count == 0)
                {
                    Blok b = a.prev;
                    while(b.prev != null)
                    {
                        b = b.prev;
                    }

                    int timeExpectedCount = timeExpected * count;

                    int timeTaken = (int)(timeStamp - b.timeStamp).TotalSeconds;

                    if (timeTaken < (timeExpectedCount / 2))
                    {
                        diff++;
                    }
                    else if (timeTaken > (timeExpectedCount * 2))
                    {
                        diff--;
                    }
                }
                while (true)
                {
                    hash = sha256(index + data + timeStamp.ToString() + previousHash + diff + nonce);
                    if (ustrezenHash(hash, diff)) break;
                    else nonce++;
                }
                /*searchingTime = (int)(DateTime.Now - timeStamp).TotalSeconds;
                if (searchingTime >= timeExpected || (int)(DateTime.Now - a.timeStamp).TotalSeconds >= timeExpected)
                {
                    prev = a;
                }
                else prev = null;*/
                prev = a;
            }
            
        }

        //pretvorba iz bitnega arraya v Blok
        public Blok(byte[] byteArr)
        {
            string s = Encoding.UTF8.GetString(byteArr, 0, byteArr.Length);

            index = int.Parse(s.Substring(0, s.IndexOf(";")));
            s = s.Substring(s.IndexOf(";") + 1);

            ime = s.Substring(0, s.IndexOf(";"));
            s = s.Substring(s.IndexOf(";") + 1);

            data = s.Substring(0, s.IndexOf(";"));
            s = s.Substring(s.IndexOf(";") + 1);

            timeStamp = DateTime.Parse(s.Substring(0, s.IndexOf(";")));
            s = s.Substring(s.IndexOf(";") + 1);

            hash = s.Substring(0, s.IndexOf(";"));
            s = s.Substring(s.IndexOf(";") + 1);

            previousHash = s.Substring(0, s.IndexOf(";"));
            s = s.Substring(s.IndexOf(";") + 1);

            diff = int.Parse(s.Substring(0, s.IndexOf(";")));
            s = s.Substring(s.IndexOf(";") + 1);

            nonce = ulong.Parse(s.Substring(0, s.IndexOf(";")));
            s = s.Substring(s.IndexOf(";") + 1);
        }

        //sha256 kodiranje za hash
        public static string sha256(string rawData)
        {
            using (SHA256 sha256Hash = SHA256.Create())
            { 
                byte[] bytes = sha256Hash.ComputeHash(Encoding.UTF8.GetBytes(rawData));

                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < bytes.Length; i++)
                {
                    builder.Append(bytes[i].ToString("x2"));
                }
                return builder.ToString();
            }
        }

        //preverjanje hasha za tezavnost
        static bool ustrezenHash(string hash, int diff)
        {
            for(int i = 0; i < diff; i++)
            {
                if(hash[i] != '0')
                {
                    return false;
                }
            }
            return true;
        }
    }
}
