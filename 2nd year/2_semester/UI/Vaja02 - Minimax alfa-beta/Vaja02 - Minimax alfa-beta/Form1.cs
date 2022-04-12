namespace Vaja02___Minimax_alfa_beta
{
    public partial class Form1 : Form
    {
        public struct Stanje
        {
            public int h;
            public int[] stanjePolja;
        };


        public Form1()
        {
            InitializeComponent();
        }

        int naVrsti = 1;

        int[,] zmagovalnePozicije = new int[8, 3] {
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 },
            { 0, 3, 6 },
            { 1, 4, 7 },
            { 2, 5, 8 },
            { 0, 4, 8 },
            { 2, 4, 6 }};

        int zmage = 0;
        int izenaceno = 0;
        int porazi = 0;
        int stPotez = 9;

        int[] globalPoz = new int[9] { 0, 0, 0, 0, 0, 0, 0, 0, 0 };


        int hev(int poteza, int[] pozicije)
        {
            int hevristika = 0;
            int bestHev = 0;

            int doZmage = 0;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (pozicije[zmagovalnePozicije[i, j]] == 1 || pozicije[zmagovalnePozicije[i, j]] == 0)
                    {
                        if (pozicije[zmagovalnePozicije[i, j]] == 1) doZmage++;
                    }
                    else
                    {
                        doZmage = 0;
                        break;
                    }

                    if (j == 2)
                    {
                        hevristika++;
                    }
                }

                if (doZmage == 3)
                {
                    bestHev = 100;
                    //return 100;
                    //zmagal je
                }
                else if (doZmage == 2)
                {
                    if (bestHev != 100) bestHev = 10;
                    //if (poteza == -1) hevristika = 10;
                    //else return 10;
                    //zmagal bo
                }
                doZmage = 0;
            }

            if (bestHev == 100) return 100;
            else if (bestHev == 10 && poteza == -1) hevristika = 10;
            else return 10;


            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (pozicije[zmagovalnePozicije[i, j]] == -1 || pozicije[zmagovalnePozicije[i, j]] == 0)
                    {
                        if (pozicije[zmagovalnePozicije[i, j]] == -1) doZmage++;
                    }
                    else
                    {
                        doZmage = 0;
                        break;
                    }

                    if (j == 2)
                    {
                        hevristika--;
                    }
                }

                if (doZmage == 3)
                {
                    bestHev = -100;
                    //zmagal je
                }
                else if (doZmage == 2)
                {
                    if (bestHev != -100) bestHev = -10;
                    //zmagal bo
                }
                doZmage = 0;
            }

            if (bestHev == -100) return -100;
            else if (bestHev == -10 && poteza == 1) hevristika = -10;
            else return -10;


            return hevristika;
        }

        bool jeList(int[] P)
        {
            for (int i = 0; i < 9; i++)
            {
                if(P[i] == 0) return false;
            }
            return true;
        }


        struct Pomoc
        {
            public int hev;
            public int pos;
        }


        Pomoc alfaBeta(int[] trenPolozaj, int ig, int d,ref int a,ref int b, int index)
        {
            Pomoc p = new Pomoc();
            Pomoc bestP = new Pomoc();

            if (jeList(trenPolozaj) || d == 0)
            {
                p.hev = hev(ig, trenPolozaj);
                p.pos = index;
                return p;
            }

            int[] tmp = new int [9];
            Array.Copy(trenPolozaj,tmp, 9);

            for (int i = 0; i < 9; i++)
            {
                if (tmp[i] == 0)
                {
                    tmp[i] = ig;

                    p = alfaBeta(tmp, -ig, d - 1,ref a,ref b, i);
                    if (index != 10) tmp[p.pos] = 0;
                    else bestP = p;
                    if (ig == 1 && p.hev > a)
                    {
                        if (p.hev > a)
                        {
                            a = p.hev;
                            bestP = p;
                        }
                    }
                    else if (ig == -1 && p.hev < b)
                    {
                        if (p.hev < b)
                        {
                            b = p.hev;
                            bestP = p;
                        }
                    }
                    if (a >= b) return bestP;
                }
            }
            return bestP;
        }



        private void button_Click(object sender, EventArgs e)
        {
            //if (naVrsti == 1)
            //{

            ((Button)sender).Text = "X";
            ((Button)sender).Click -= button_Click;
            int pos = ((Button)sender).Name[6] - '0';
            stPotez--;
            globalPoz[pos] = 1;
            label1.Text = hev(naVrsti, globalPoz).ToString();

            //naVrsti = -1;

            //Stanje s = new Stanje();


            if (hev(1, globalPoz) == 100)
            {
                /*button0.Enabled = false;
                button1.Enabled = false;
                button2.Enabled = false;
                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;
                button6.Enabled = false;
                button7.Enabled = false;
                button8.Enabled = false;*/

                button0.Click -= button_Click;
                button1.Click -= button_Click;
                button2.Click -= button_Click;
                button3.Click -= button_Click;
                button4.Click -= button_Click;
                button5.Click -= button_Click;
                button6.Click -= button_Click;
                button7.Click -= button_Click;
                button8.Click -= button_Click;


                label1.Text = "Damn wp";

                zmage++;
                labelZmage.Text = "Zmage: " + zmage;

                stPotez = 9;
            }
            else
            {


                Pomoc p = new Pomoc();

                int a = int.MinValue;
                int b = int.MaxValue;

                p = alfaBeta(globalPoz, -1, 3, ref a, ref b, 10);

                stPotez--;

                switch (p.pos)
                {
                    case 0:
                        {
                            globalPoz[p.pos] = -1;
                            button0.Text = "O";
                            button0.Click -= button_Click;
                            break;
                        }
                    case 1:
                        {
                            globalPoz[p.pos] = -1;
                            button1.Text = "O";
                            button1.Click -= button_Click;
                            break;
                        }
                    case 2:
                        {
                            globalPoz[p.pos] = -1;
                            button2.Text = "O";
                            button2.Click -= button_Click;
                            break;
                        }
                    case 3:
                        {
                            globalPoz[p.pos] = -1;
                            button3.Text = "O";
                            button3.Click -= button_Click;
                            break;
                        }
                    case 4:
                        {
                            globalPoz[p.pos] = -1;
                            button4.Text = "O";
                            button4.Click -= button_Click;
                            break;
                        }
                    case 5:
                        {
                            globalPoz[p.pos] = -1;
                            button5.Text = "O";
                            button5.Click -= button_Click;
                            break;
                        }
                    case 6:
                        {
                            globalPoz[p.pos] = -1;
                            button6.Text = "O";
                            button6.Click -= button_Click;
                            break;
                        }
                    case 7:
                        {
                            globalPoz[p.pos] = -1;
                            button7.Text = "O";
                            button7.Click -= button_Click;
                            break;
                        }
                    case 8:
                        {
                            globalPoz[p.pos] = -1;
                            button8.Text = "O";
                            button8.Click -= button_Click;
                            break;
                        }
                }

                if(hev(-1, globalPoz) == -100)
                {
                    button0.Click -= button_Click;
                    button1.Click -= button_Click;
                    button2.Click -= button_Click;
                    button3.Click -= button_Click;
                    button4.Click -= button_Click;
                    button5.Click -= button_Click;
                    button6.Click -= button_Click;
                    button7.Click -= button_Click;
                    button8.Click -= button_Click;
                    label1.Text = "Zguba";

                    porazi++;
                    labelPoraz.Text = "Porazi: " + porazi;

                    stPotez = 9;
                }
            }


            if (stPotez <= 0)
            {
                label1.Text = "Izenaceno";
                izenaceno++;
                labelIzenaceno.Text = "Izenaceno: " + izenaceno;
                stPotez = 9;
            }

            //globalPoz = s.stanjePolja;

            /*}
            else
            {
                ((Button)sender).Text = "O";
                int pos = ((Button)sender).Name[6] - '0';
                globalPoz[pos] = -1;
                label1.Text = hev(naVrsti, globalPoz).ToString();
                naVrsti = 1;
            }*/
        }

        private void buttonRetry_Click(object sender, EventArgs e)
        {
            button0.Click += button_Click;
            button1.Click += button_Click;
            button2.Click += button_Click;
            button3.Click += button_Click;
            button4.Click += button_Click;
            button5.Click += button_Click;
            button6.Click += button_Click;
            button7.Click += button_Click;
            button8.Click += button_Click;
            label1.Text = "";

            button0.Text = "";
            button1.Text = "";
            button2.Text = "";
            button3.Text = "";
            button4.Text = "";
            button5.Text = "";
            button6.Text = "";
            button7.Text = "";
            button8.Text = "";

            globalPoz = new int[9] { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        }
    }
}