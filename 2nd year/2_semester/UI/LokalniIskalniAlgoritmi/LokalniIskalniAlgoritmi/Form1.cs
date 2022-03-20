namespace LokalniIskalniAlgoritmi
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //Resizing image (slika kraljice)
        public static Image resizeImage(Image imgToResize, Size size)
        {
            return (Image)(new Bitmap(imgToResize, size));
        }

        //panel array in queen position array
        private Panel[,] _chessBoardPanels;
        private bool[,] qnPos;
        //st korakov
        private int stKorakov = 0;

        //postavitev polja
        void boardSetUp(int x)
        {
            //velikost polj (400 je velikost okna)
            int tileSize = 400 / x;
            var clr1 = Color.DarkGray;
            var clr2 = Color.White;

            _chessBoardPanels = new Panel[x, x];

            //zanka za dodajanje panel v polje
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    //ustvarimo panel
                    var newPanel = new Panel
                    {
                        Size = new Size(tileSize, tileSize),
                        Location = new Point(tileSize * i, tileSize * j),
                        Margin = new Padding(0, 0, 0, 0)
                    };

                    //ga dodamo v control od layouta
                    flowLayoutPanel1.Controls.Add(newPanel);

                    //dodamo barve
                    if (i % 2 == 0)
                        newPanel.BackColor = j % 2 != 0 ? clr1 : clr2;
                    else
                        newPanel.BackColor = j % 2 != 0 ? clr2 : clr1;

                    //dodamo v polje
                    _chessBoardPanels[i, j] = newPanel;
                }
            }

            //dodamo sliko kraljice
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    if (qnPos[i, j])
                    {
                        Image img = Image.FromFile("queen.png");
                        img = resizeImage(img, new Size(tileSize, tileSize));
                        _chessBoardPanels[i, j].BackgroundImage = img;
                    }
                }
            }
        }

        //generiramo nakljucne pozicije kraljic na polju
        void GenerateRandomly(int x, bool[,] qnPos)
        {
            Random rd = new Random();
            for (int y = 0; y < x; y++)
            {
                int rand = rd.Next(0, x);
                for (int i = 0; i < x; i++)
                {
                    if (i == rand) qnPos[i, y] = true;
                    else qnPos[i, y] = false;
                }
            }
        }

        //izracun H
        int Hevristika(int x, bool [,] S)
        {
            int h = 0;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    //ce je kraljica na tem polju
                    if(S[i,j])
                    {
                        int l = 1;
                        for (int k = j + 1; k < x; k++)
                        {
                            //ce je kraljica v isti vrstici
                            if (S[i,k])
                            {
                                h++;
                            }
                            //ce je kraljica diagonalno spodaj
                            if(i + l < x)
                            {
                                if (S[i + l, k])
                                {
                                    h++;
                                }
                            }
                            //ce je kraljica diagonalno zgoraj
                            if (i - l >= 0)
                            {
                                if (S[i - l, k])
                                {
                                    h++;
                                }
                            }
                            l++;
                        }
                    }
                }
            }
            return h;
        }

        //vzpenjanje na hrib
        bool[,] HillClimbing(int x, ref int nMoves)
        {
            //backtracking list
            int backtrack = 0;
            List<bool[,]> vs = new List<bool[,]>();

            //trenutni najboljsi je originalna pozicija
            bool[,] curBest = (bool[,])qnPos.Clone();

            //originalni H
            int najmanj = Hevristika(x, curBest);

            //loop dokler H == 0 ali stKorakov doseze nMoves
            while (najmanj > 0 && nMoves > stKorakov)
            {
                //prejsnji H za backtracking
                int prev = najmanj;

                //loop stolpce
                for (int i = 0; i < x; i++)
                {
                    bool[,] S = (bool[,])qnPos.Clone();
                    //loop vrstice
                    for (int j = 0; j < x; j++)
                    {
                        //ce kraljice ni tukaj nadaljujemo
                        if (!S[j, i]) continue;
                        //najdena kraljica
                        else
                        {
                            int n = j;
                            //loop polja pod najdenim
                            while (n < x - 1)
                            {
                                //premik kraljice
                                S[n, i] = false;
                                S[n + 1, i] = true;
                                //primerajmo nov H
                                int newH = Hevristika(x, S);
                                if (najmanj >= newH)
                                {
                                    //ce je enak kot prejsnji najboljsi shranimo za backtrackanje
                                    if (najmanj == newH)
                                    {
                                        vs.Add((bool[,])S.Clone());
                                    }
                                    //ce boljsi nastavimo na trenutnega
                                    else
                                    {
                                        vs.Add((bool[,])S.Clone());
                                        najmanj = newH;
                                        curBest = (bool[,])S.Clone();
                                    }
                                }
                                //premik nizje
                                n++;
                            }

                            //loopanje gor
                            n = j;
                            while (n > 0)
                            {
                                //premik kraljice
                                S[n, i] = false;
                                S[n - 1, i] = true;
                                //primerjamo nov H
                                int newH = Hevristika(x, S);
                                if (najmanj >= newH)
                                {
                                    //ce je enak kot prejsnji najboljsi shranimo za backtrackanje
                                    if (najmanj == newH)
                                    {
                                        vs.Add((bool[,])S.Clone());
                                    }
                                    //ce boljsi nastavimo na trenutnega
                                    else
                                    {
                                        vs.Add((bool[,])S.Clone());
                                        najmanj = newH;
                                        curBest = (bool[,])S.Clone();
                                    }
                                }
                                n--;
                            }

                            break;
                        }
                    }
                }
                //ce se H ni izbobljsal in imamo moznosti v listu za backtrackanje poskusimo katero drugo moznost
                if(backtrack < vs.Count())
                {
                    qnPos = (bool[,])vs[backtrack].Clone();
                    //premaknemo naprej po listu backtrack
                    backtrack++;
                }
                //curBest je nov qnPos
                else qnPos = (bool[,])curBest.Clone();

                stKorakov++;
            }

            //izpis stevila korakov
            labelStKorakov2.Text = stKorakov.ToString();
            return curBest;
        }

        //simulirano ohlajanje
        bool[,] simulatedAnnealing(int x, int temp, int delT)
        {
            int T = temp;
            int spT = delT;

            //list
            List<bool[,]> vs = new List<bool[,]>();

            //trenutni najboljsi je originalna pozicija
            bool[,] curBest = (bool[,])qnPos.Clone();

            //originalni H
            int najmanj = Hevristika(x, curBest);

            //izracun maximalne vrednosti s pomocjo fakultete za normalizacijo
            int maxH = 1;
            int fact = x - 1;

            while (fact != 1)
            {
                maxH = maxH * fact;
                fact = fact - 1;
            }
            //---------------------------


            Random r = new Random();

            bool[,] S = (bool[,])qnPos.Clone();

            //loop dokler T == 0
            while (T > 0 && najmanj > 0)
            {
                //loop stolpce
                for (int i = 0; i < x; i++)
                {
                    //loop vrstice v stolpcu
                    for (int j = 0; j < x; j++)
                    {
                        //ce kraljice ni na tej poziciji gremo naprej
                        if (!S[j, i]) continue;
                        //najdena kraljica
                        else
                        {
                            //nakljucno novo polje
                            int rnd = r.Next(x-1);
                            if (rnd == j && rnd < x - 1) rnd += 1;
                            else if(rnd == j) rnd -= 1;

                            S[j, i] = false;
                            S[rnd, i] = true;
                        }
                        break;
                    }

                    //izracun nove hevristike
                    int hev = Hevristika(x, S);

                    int delH = najmanj - hev;
                    //ce je delH boljsi nadaljujemo
                    //if (delH >= 0)
                    if (delH > 0)
                    {
                        if (hev == 0)
                        {
                            labelStKorakov2.Text = (temp - T).ToString();
                            return S;
                        }
                        najmanj = hev;
                        continue;
                    }
                    //drugace glede na forumo in nakljucno vrednostjo dolocimo ali nadaljujemo ali generiramo novo nakljucno pozicijo
                    else
                    {
                        double rnd = r.NextDouble();
                        if (rnd > (Math.Exp(((double)delH / (double)T)) / maxH)) continue;
                        else
                        {
                            GenerateRandomly(x, S);
                            break;
                        }
                    }
                }

                //zmanjsamo T
                T -= spT;
            }

            //izpis korakov
            labelStKorakov2.Text = (temp - T).ToString();
            return S;
        }

        //razred Pozicije za lazje sortiranje k-stevilo polj in ohranjanje njihovih hevristik
        class Pozicije
        {
            public bool[,] qnPos;
            public int H;

            public Pozicije(bool[,] qnPos, int H)
            {
                this.qnPos = qnPos;
                this.H = H;
            }
        }

        //lokalni zarek
        bool[,] localBeamSearch(int x, int k, ref int nMoves)
        {
            Pozicije[] P = new Pozicije[k];

            // generiramo 15 nakljucnih pozicij
            for (int i = 0; i < k; i++)
            {
                bool[,] tmp = new bool[x, x];
                GenerateRandomly(x, tmp);

                P[i] = new Pozicije(tmp, Hevristika(x, tmp));
            }

            //sortiramo po hevristiki
            Array.Sort(P, delegate (Pozicije x, Pozicije y) { return x.H.CompareTo(y.H); });

            //ce je najmanjsa 0 imamo koncno stanje
            if (P[0].H == 0) return P[0].qnPos;
            
            while(nMoves > 0)
            {
                nMoves--;
                //stevilo novih stanj (max. k)
                int index = 0;

                Pozicije[] Q = new Pozicije[k];

                for (int i = 0; i < k; i++)
                {
                    Q[i] = new Pozicije((bool[,])P[i].qnPos.Clone(), P[i].H);
                }

                //loopamo skozi nasih k stanj
                for (int l = 0; l < k; l++)
                {
                    //loop columns
                    for (int i = 0; i < x; i++)
                    {
                        //loop rows
                        for (int j = 0; j < x; j++)
                        {
                            //if queen not on this position we continue
                            if (!P[l].qnPos[j, i]) continue;
                            //queen is on this position
                            else
                            {
                                bool[,] tmp = (bool[,])P[l].qnPos.Clone();
                                int n = j;
                                //loop rows in this column up
                                while (n < x - 1)
                                {
                                    //move the queen lower
                                    tmp[n, i] = false;
                                    tmp[n + 1, i] = true;
                                    //move lower
                                    n++;

                                    if (index == k)
                                    {
                                        Array.Sort(Q, delegate (Pozicije x, Pozicije y) { return x.H.CompareTo(y.H); });

                                        int hev = Hevristika(x, tmp);
                                        if (Q[k-1].H >= hev)
                                        {
                                            if (hev == 0) return tmp;
                                            Q[k-1].H = hev;
                                            Q[k-1].qnPos = (bool[,])tmp.Clone();
                                        }
                                    }
                                    else
                                    {
                                        Pozicije p = new Pozicije(tmp, Hevristika(x, tmp));
                                        Q[index] = p;
                                        index++;
                                    }
                                }

                                tmp = (bool[,])P[l].qnPos.Clone();
                                //loop rows in this column down
                                n = j;
                                while (n > 0)
                                {
                                    //move queen higher
                                    tmp[n, i] = false;
                                    tmp[n - 1, i] = true;
                                    n--;

                                    if (index == k)
                                    {
                                        Array.Sort(Q, delegate (Pozicije x, Pozicije y) { return x.H.CompareTo(y.H); });

                                        int hev = Hevristika(x, tmp);
                                        if (Q[14].H >= hev)
                                        {
                                            if (hev == 0) return tmp;
                                            Q[k-1].H = hev;
                                            Q[k-1].qnPos = (bool[,])tmp.Clone();
                                        }
                                    }
                                    else
                                    {
                                        Pozicije p = new Pozicije(tmp, Hevristika(x, tmp));
                                        Q[index] = p;
                                        index++;
                                    }
                                }
                            }
                        }
                    }
                }

                Array.Sort(Q, delegate (Pozicije x, Pozicije y) { return x.H.CompareTo(y.H); });

                if (Q[0].H == 0) return Q[0].qnPos;
                for (int i = 0; i < k; i++)
                {
                    P[i] = new Pozicije((bool[,])Q[i].qnPos.Clone(), Q[i].H);
                }
            }

            return P[0].qnPos;
        }

        //genetic algorithm
        //bool[,] genetskiAlg()
        //{

        //}

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            boardSetUp(4);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //ob spremembi indexa resetiramo vrednosti
            stKorakov = 0;
            labelStKorakov2.Text = stKorakov.ToString();
            flowLayoutPanel1.Controls.Clear();
            int x = comboBox1.SelectedIndex + 4;
            qnPos = new bool[x, x];
            GenerateRandomly(x, qnPos);
            boardSetUp(comboBox1.SelectedIndex + 4);
            labelHev2.Text = Hevristika(x, qnPos).ToString();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            stKorakov = 0;
            labelStKorakov2.Text = stKorakov.ToString();

            //zazenemo hill climb algoritem
            if (rbVzpenjanje.Checked)
            {
                int stevilka = (int)nmStPomikov.Value;
                qnPos = HillClimbing(comboBox1.SelectedIndex + 4,ref stevilka);

            }
            //zazenemo algoritem simuliranega ohlajanja
            else if (rbOhlajanje.Checked)
            {
                qnPos = simulatedAnnealing(comboBox1.SelectedIndex + 4, (int)nmTemp.Value, (int)nmDelTemp.Value);
            }
            //zazenemo algoritem z lokalnim zarkom
            else if (rbLokal.Checked)
            {
                int stevilka = (int)nmStPomikov.Value;
                int before = (int)nmStPomikov.Value;
                qnPos = localBeamSearch(comboBox1.SelectedIndex + 4, (int)nmStanja.Value, ref stevilka);

                labelStKorakov2.Text = (before - stevilka).ToString();
            }
            //else if (rbGenet.Checked)
            //{
            //    qnPos = genetskiAlg();
            //}
            labelHev2.Text = Hevristika(comboBox1.SelectedIndex + 4, qnPos).ToString();
            flowLayoutPanel1.Controls.Clear();
            boardSetUp(comboBox1.SelectedIndex + 4);
        }

        private void btnGeneriraj_Click(object sender, EventArgs e)
        {
            //generiramo novo polje, resetiramo stare stevilke
            stKorakov = 0;
            labelStKorakov2.Text = stKorakov.ToString();
            flowLayoutPanel1.Controls.Clear();
            int x = comboBox1.SelectedIndex + 4;
            qnPos = new bool[x, x];
            GenerateRandomly(x, qnPos);
            boardSetUp(comboBox1.SelectedIndex + 4);
            labelHev2.Text = Hevristika(x, qnPos).ToString();
        }

        private void rbVzpenjanje_CheckedChanged(object sender, EventArgs e)
        {
            if (rbVzpenjanje.Checked)
            {
                nmStPomikov.Enabled = true;
                nmDelTemp.Enabled = false;
                nmTemp.Enabled = false;
                nmStanja.Enabled = false;
            }
            else if (rbOhlajanje.Checked)
            {
                nmStPomikov.Enabled = false;
                nmDelTemp.Enabled = true;
                nmTemp.Enabled = true;
                nmStanja.Enabled = false;
            }
            else if (rbLokal.Checked)
            {
                nmStPomikov.Enabled = true;
                nmDelTemp.Enabled = false;
                nmTemp.Enabled = false;
                nmStanja.Enabled = true;
            }
        }
    }
}