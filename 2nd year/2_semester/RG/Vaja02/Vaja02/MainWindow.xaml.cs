using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Vaja02
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        List<Point> points = new List<Point>();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {

        }


        //generiranje tock
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            canvas.Children.Clear();
            points.Clear();

            Random rnd = new Random();

            int stTock = int.Parse(textBoxSt.Text);

            Point pt = new Point();

            Rectangle tocka1 = new Rectangle();

            if (rbEnakomerno.IsChecked == true)
            {
                for (int i = 0; i < stTock; i++)
                {
                    pt.X = rnd.Next(0, (int)canvas.ActualWidth);
                    pt.Y = rnd.Next(0, (int)canvas.ActualHeight);

                    points.Add(pt);

                    tocka1.Width = 1; tocka1.Height = 1;
                    //tocka1.Width = 2; tocka1.Height = 2;

                    tocka1.Fill = Brushes.Black;
                    tocka1.Stroke = Brushes.Black;

                    tocka1.Margin = new Thickness(pt.X, pt.Y, 0, 0);

                    canvas.Children.Add(tocka1);
                }
            }
            else
            {
                int mean1 = (int)canvas.ActualWidth / 2;
                int mean2 = (int)canvas.ActualHeight / 2;
                int stdDev = 50;

                for (int i = 0; i < stTock; i++)
                {

                    double u1x = 1.0 - rnd.NextDouble();
                    double u2x = 1.0 - rnd.NextDouble();
                    double randStdNormalx = Math.Sqrt(-2.0 * Math.Log(u1x)) * Math.Sin(2.0 * Math.PI * u2x);
                    double u1y = 1.0 - rnd.NextDouble();
                    double u2y = 1.0 - rnd.NextDouble();
                    double randStdNormaly = Math.Sqrt(-2.0 * Math.Log(u1y)) * Math.Sin(2.0 * Math.PI * u2y);

                    pt.X = (int)(mean1 + stdDev * randStdNormalx) + 50;
                    pt.Y =(int)(mean2 + stdDev * randStdNormaly) + 50;

                    points.Add(pt);

                    tocka1.Width = 1; tocka1.Height = 1;

                    tocka1.Fill = Brushes.Black;
                    tocka1.Stroke = Brushes.Black;

                    tocka1.Margin = new Thickness(pt.X, pt.Y , 0, 0);

                    canvas.Children.Add(tocka1);
                }
            }
        }


        //struktura za pomoc pri sortiranju kotov (graham)
        struct Koti
        {
            public Point point;
            public double kot;
        }


        //zacetek iskanja konveksne lupine
        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            var watch = new System.Diagnostics.Stopwatch();
            obhodQH.Clear();

            //jarvisov obhod
            if (rbJarvis.IsChecked == true)
            {
                watch.Start();
                List<Point> obhod = new List<Point>();

                //poiscemo ekstremni element po X osi
                int E = 0;
                
                for (int i = 0; i < points.Count; i++)
                {
                    if(points[i].X < points[E].X) E = i;
                }

                int trenuten, naslednji;
                trenuten = E;
                //-----------------------------------------


                do
                {
                    //trenutno tocko dodamo v obhod
                    obhod.Add(points[trenuten]);

                    //ce smo prisli okoli do prvega
                    if(trenuten + 1 % points.Count == 0) naslednji = 0;
                    else naslednji = (trenuten + 1) % points.Count;


                    //poiscemo ekstremno orientacijo (kot)
                    for (int i = 0; i < points.Count; i++)
                    {
                        int y1 = (int)(points[trenuten].Y) - (int)(points[i].Y);
                        int y2 = (int)(points[trenuten].Y) - (int)(points[naslednji].Y);
                        int x1 = (int)(points[trenuten].X) - (int)(points[i].X);
                        int x2 = (int)(points[trenuten].X) - (int)(points[naslednji].X);

                        //izracun orientacije glede na tocke
                        int ori = y2*x1 - y1*x2;

                        //ce je boljsa jo nastavimo na naslednjo
                        if (ori > 1) naslednji = i;
                    }

                    //najdli smo naslednjo tocko
                    trenuten = naslednji;

                    //loopamo dokler ne pridemo z trenutnim do prvega
                } while (trenuten != E);

                watch.Stop();

                lbTime.Content = "Cas: " + watch.ElapsedMilliseconds + "ms";

                watch.Reset();

                //narisemo dobljen obhod
                for (int i = 0; i < obhod.Count; i++)
                {
                    Line linija = new Line();
                    linija.Stroke = Brushes.Black;
                    linija.StrokeThickness = 1;
                    linija.Fill = Brushes.Black;

                    linija.X1 = obhod[i].X;
                    linija.Y1 = obhod[i].Y;

                    if (i == obhod.Count - 1)
                    {
                        linija.X2 = obhod[0].X;
                        linija.Y2 = obhod[0].Y;
                    }
                    else
                    {
                        linija.X2 = obhod[i + 1].X;
                        linija.Y2 = obhod[i + 1].Y;
                    }

                    canvas.Children.Add(linija);
                }

            }
            else if (rbGraham.IsChecked == true)
            {
                /*Random rnd = new Random();

                int t1 = rnd.Next(0, points.Count);
                int t2 = rnd.Next(0, points.Count);
                int t3 = rnd.Next(0, points.Count);

                int Ox = (int)(points[t1].X + points[t2].X + points[t3].X) / 3;
                int Oy = (int)(points[t1].Y + points[t2].Y + points[t3].Y) / 3;*/

                watch.Start();

                //najdemo ekstremno tocko
                int E = 0;

                for (int i = 0; i < points.Count; i++)
                {
                    if (points[i].X < points[E].X) E = i;
                }

                //to bo nasa prva tocka
                Point prva = points[E];

                List<double> koti = new List<double>();

                //dodamo se ostale
                for (int i = 0; i < points.Count; i++)
                {
                    if (i == E)
                    {
                        koti.Add(0);
                        continue;
                    }
                    //Δθi =  atan2(xi - Ox, yi - Oy)
                    double o = Math.Atan2(points[i].X - prva.X, points[i].Y - prva.Y);
                    //if (Δθ < 0) Δθ + = 2π
                    if(o < 0) o += 180*Math.PI;

                    koti.Add(o);
                }

                //list kotov + tock
                List<Koti> k = new List<Koti>();
                Koti kot = new Koti();

                //napolnimo list z vsemi razen prvim
                for (int i = 0; i < points.Count; i++)
                {
                    if (i == E) continue;

                    kot.kot = koti[i];
                    kot.point = points[i];
                    k.Add(kot);
                }

                //jih sortiramo
                k.Sort((x,y) => x.kot.CompareTo(y.kot));

                kot.kot = 0;
                kot.point = prva;

                //dodamo se prvo
                k.Insert(0, kot);


                /*int E = 0;

                for (int i = 0; i < k.Count; i++)
                {
                    if (k[i].point.X < k[E].point.X) E = i;
                }*/
;
                //nastavimo zacetne vrednosti
                int Pi, P1, P2;
                Pi = 0;
                P1 = 1;
                P2 = 2;

                do
                {

                    //izracun vektorskega produkta
                    //U = (Pi+1-Pi) x (Pi+2-Pi) = (x2-x1)(y3-y1) - (x3-x1)(y2-y1)
                    double U = ((k[P1].point.X - k[Pi].point.X) * (k[P2].point.Y - k[Pi].point.Y) -
                              (k[P2].point.X - k[Pi].point.X) * (k[P1].point.Y - k[Pi].point.Y));

                    //glede na usmerjenost dolocimo ali se pomaknemo naprej
                    if (U < 0)
                    {
                        Pi++;
                        P1++;
                        P2++;

                        if (P2 > k.Count - 1) P2 = 0;
                        if (P1 > k.Count - 1) P1 = 0;
                        if (Pi > k.Count - 1) Pi = 0;
                    }
                    //ali pa ga odstranimo in se premaknemo nazaj
                    else
                    {
                        k.RemoveAt(P1);

                        Pi--;
                        P1--;
                        P2--;

                        if (P2 < 0) P2 = k.Count - 1;
                        if (P1 < 0) P1 = k.Count - 1;
                        if (Pi < 0) Pi = k.Count - 1;
                    }
                    //zanka dokler ne pridemo okoli
                } while (P1 != 0);


                watch.Stop();

                lbTime.Content = "Cas: " + watch.ElapsedMilliseconds + "ms";

                watch.Reset();

                //narisemo dobljeno konveksno lupino
                for (int i = 0; i < k.Count; i++)
                {

                    Line linija = new Line();
                    linija.Stroke = Brushes.Black;
                    linija.StrokeThickness = 1;
                    linija.Fill = Brushes.Black;

                    linija.X1 = k[i].point.X;
                    linija.Y1 = k[i].point.Y;

                    if (i == k.Count - 1)
                    {
                        linija.X2 = k[0].point.X;
                        linija.Y2 = k[0].point.Y;
                    }
                    else
                    {
                        linija.X2 = k[i + 1].point.X;
                        linija.Y2 = k[i + 1].point.Y;
                    }

                    canvas.Children.Add(linija);
                }

            }
            else
            {
                watch.Start();

                int E1 = 0, E2 = 0;
                for (int i = 0; i < points.Count; i++)
                {
                    if (points[i].X < points[E1].X)
                    {
                        E1 = i;
                    }
                    if (points[i].X > points[E2].X)
                    {
                        E2 = i;
                    }
                }

                QuickHull(points[E1], points[E2], 1);
                QuickHull(points[E1], points[E2], -1);


                watch.Stop();

                lbTime.Content = "Cas: " + watch.ElapsedMilliseconds + "ms";

                watch.Reset();

                for (int i = 0; i < obhodQH.Count; i++)
                {

                    Line linija = new Line();
                    linija.Stroke = Brushes.Black;
                    linija.StrokeThickness = 1;
                    linija.Fill = Brushes.Black;

                    linija.X1 = obhodQH[i].X;
                    linija.Y1 = obhodQH[i].Y;

                    if (i == obhodQH.Count - 1)
                    {
                        linija.X2 = obhodQH[0].X;
                        linija.Y2 = obhodQH[0].Y;
                    }
                    else
                    {
                        linija.X2 = obhodQH[i + 1].X;
                        linija.Y2 = obhodQH[i + 1].Y;
                    }
                    i++;
                    canvas.Children.Add(linija);
                }
            }

        }

        int najdiStran(Point t1, Point t2, Point t3)
        {
            int val = (int)((t3.Y - t1.Y) * (t2.X - t1.X) - (t2.Y - t1.Y) * (t3.X - t1.X));

            if (val > 0) return 1;
            else if (val < 0) return -1;
            else return 0;
        }

        List<Point> obhodQH = new List<Point>();
        void QuickHull(Point E1, Point E2, int stran)
        {
            int index = -1;
            int maxOddaljeno = 0;
            // poiscemo najvecjo razdaljo od tocke do daljice, ki je na pravi strani daljice
            for (int i = 0; i < points.Count; i++)
            {
                int tmp = Math.Abs((int)((points[i].Y - E1.Y) * (E2.X - E1.X) - 
                                        (E2.Y - E1.Y) * (points[i].X - E1.X)));

                if (najdiStran(E1, E2, points[i]) == stran && tmp > maxOddaljeno)
                {
                    index = i;
                    maxOddaljeno = tmp;
                }
            }

            // ce ne najdemo dobene damo zadni dve tocki v lupino
            if (index == -1)
            {
                obhodQH.Add(E1);
                obhodQH.Add(E2);
                return;
            }

            // Rekurzivno klice sama sebe 
            QuickHull(points[index], E1, -najdiStran(points[index], E1, E2));
            QuickHull(points[index], E2, -najdiStran(points[index], E2, E1));
        }

    }
}
