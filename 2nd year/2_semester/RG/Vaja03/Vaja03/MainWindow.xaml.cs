using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Vaja03
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

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            canvas.Children.Clear();
            points.Clear();

            Random rnd = new Random();

            int stTock = int.Parse(textBoxSt.Text);

            Point pt = new Point();

            //izris tock enakomerno (random po celem kanvasu)
            if (rbEnakomerno.IsChecked == true)
            {
                for (int i = 0; i < stTock; i++)
                {
                    Rectangle tocka1 = new Rectangle();

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
            //izris tock po Gaussu (osredotoceno na sredino)
            else
            {
                int mean1 = (int)canvas.ActualWidth / 2;
                int mean2 = (int)canvas.ActualHeight / 2;
                int stdDev = 50;

                for (int i = 0; i < stTock; i++)
                {
                    Rectangle tocka1 = new Rectangle();

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

                    tocka1.Margin = new Thickness(pt.X, pt.Y, 0, 0);

                    canvas.Children.Add(tocka1);
                }
            }
        }

        struct Povezave
        {
            public Point x;
            public Point y;
            public double razdalja;

            public Povezave(Point x, Point y, double razdalja)
            {
                this.x = x; this.y = y; this.razdalja = razdalja;
            }
        }

        //funkcija za dolocitev strani glede na nase tocke
        int najdiStran(Point t1, Point t2, Point t3)
        {
            int val = (int)((t3.Y - t1.Y) * (t2.X - t1.X) - (t2.Y - t1.Y) * (t3.X - t1.X));

            if (val > 0) return 1;
            else if (val < 0) return -1;
            else return 0;
        }

        //sem se bojo shranjevale tocke za obhod po quick hull
        List<Point> obhodQH = new List<Point>();
        void QuickHull(Point E1, Point E2, int stran, List<Point> tocke)
        {
            int index = -1;
            int maxOddaljeno = 0;

            //iscemo najbolj oddaljeno tocko na trenutni strani
            for (int i = 0; i < tocke.Count; i++)
            {
                int tmp = Math.Abs((int)((tocke[i].Y - E1.Y) * (E2.X - E1.X) -
                                        (E2.Y - E1.Y) * (tocke[i].X - E1.X)));

                if (najdiStran(E1, E2, tocke[i]) == stran && tmp > maxOddaljeno)
                {
                    index = i;
                    maxOddaljeno = tmp;
                }
            }

            //ce ne najdemo novih bolj oddaljenih pomeni da smo nasli prave tocke
            //koncamo rekurzijo
            if (index == -1)
            {
                obhodQH.Add(E1);
                obhodQH.Add(E2);
                return;
            }

            //rekurzivno se premikamo po straneh
            QuickHull(tocke[index], E1, -najdiStran(tocke[index], E1, E2), tocke);
            QuickHull(tocke[index], E2, -najdiStran(tocke[index], E2, E1), tocke);
        }

        List<Povezave> povezaneTocke = new List<Povezave>();
        List<Povezave> sprejetePovezave = new List<Povezave>();

        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            povezaneTocke.Clear();
            sprejetePovezave.Clear();
            obhodQH.Clear();

            {

                int E1 = 0, E2 = 0;
                for (int j = 0; j < points.Count; j++)
                {
                    if (points[j].X < points[E1].X)
                    {
                        E1 = j;
                    }
                    if (points[j].X > points[E2].X)
                    {
                        E2 = j;
                    }
                }

                //imamo loceno na dve strani in jih posebej resujemo
                QuickHull(points[E1], points[E2], 1, points);
                QuickHull(points[E1], points[E2], -1, points);
            }

            if (rbMinUtez.IsChecked == true)
            {

                

                //Povežemo vse točke iz množice χ. Dobimo m = n * (n - 1) / 2 daljic.
                for (int i = 0; i < points.Count; i++)
                {
                    for (int j = i + 1; j < points.Count; j++)
                    {
                        double razdalja = Math.Max(Math.Abs(points[i].X -points[j].X), Math.Abs(points[i].Y - points[j].Y));
                        povezaneTocke.Add(new Povezave(points[i], points[j], razdalja));
                    }
                }

                //Ta seznam daljic uredimo glede na njihovo dolžino
                povezaneTocke.Sort((x, y) => x.razdalja.CompareTo(y.razdalja));

                //Najkrajšo daljico vzamemo kot začetno daljico, ki je zagotovo del triangulacije.
                sprejetePovezave.Add(povezaneTocke[0]);

                //Preostale daljice obravnavamo po vrstnem redu in jih lahko zavržemo ali sprejmemo.
                //Daljico zavržemo v primeru, če le-ta seka katero izmed že do sedaj sprejetih daljic.
                //V tem primeru, če ne seka nobene, jo dodamo v seznam sprejetih daljic.
                for (int i = 0; i < povezaneTocke.Count; i++)
                {
                    Point T1 = povezaneTocke[i].x;
                    Point T2 = povezaneTocke[i].y;

                    for (int j = 0; j < sprejetePovezave.Count; j++)
                    {

                        Point T3 = sprejetePovezave[j].x;
                        Point T4 = sprejetePovezave[j].y;
                            
                        //Izracun A, B, D
                        double A = (T4.X - T3.X) * (T1.Y - T3.Y) - (T1.X - T3.X) * (T4.Y - T3.Y);
                        double B = (T2.X - T1.X) * (T1.Y - T3.Y) - (T1.X - T3.X) * (T2.Y - T1.Y);
                        double D = (T2.X - T1.X) * (T4.Y - T3.Y) - (T4.X - T3.X) * (T2.Y - T1.Y);

                        double dxc = T3.X - T1.X;
                        double dyc = T3.Y - T1.Y;

                        double dxl = T2.X - T1.X;
                        double dyl = T2.Y - T1.Y;

                        double cross = dxc * dyl - dyc * dxl;

                        dxc = T4.X - T1.X;
                        dyc = T4.Y - T1.Y;

                        dxl = T2.X - T1.X;
                        dyl = T2.Y - T1.Y;

                        double cross2 = dxc * dyl - dyc * dxl;

                        dxc = T1.X - T3.X;
                        dyc = T1.Y - T3.Y;

                        dxl = T4.X - T3.X;
                        dyl = T4.Y - T3.Y;

                        double cross3 = dxc * dyl - dyc * dxl;

                        dxc = T2.X - T3.X;
                        dyc = T2.Y - T3.Y;

                        dxl = T4.X - T3.X;
                        dyl = T4.Y - T3.Y;

                        double cross4 = dxc * dyl - dyc * dxl;

                        //Ua, Ub
                        double Ua = A / D;
                        double Ub = B / D;

                        if (Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1 && cross != 0 && cross2 != 0 && cross3 != 0 && cross4 != 0) break;
                        else if (sprejetePovezave.Count - 1 == j)
                        {
                            sprejetePovezave.Add(povezaneTocke[i]);
                            break;
                        }
                    }


                    //Algoritem prekinite, ko sprejmete 3 * n - 3 - k robov (daljic), kjer je n število točk,
                    //k pa število točk na konveksni lupini, saj je triangulacija končana.
                    if (sprejetePovezave.Count > 3 * points.Count - 3 - (obhodQH.Count / 2)) 
                        break;
                }

                for (int i = 0; i < sprejetePovezave.Count; i++)
                {
                    Line linija = new Line();
                    linija.Stroke = Brushes.Black;
                    linija.StrokeThickness = 1;
                    linija.Fill = Brushes.Black;

                    linija.X1 = sprejetePovezave[i].x.X;
                    linija.Y1 = sprejetePovezave[i].x.Y;
                    linija.X2 = sprejetePovezave[i].y.X;
                    linija.Y2 = sprejetePovezave[i].y.Y;

                    canvas.Children.Add(linija);
                }

            }
            else if(rbHamilton.IsChecked == true)
            {
                List<Point> tmpPoints = new List<Point>(points);

                List<List<Povezave>> vsePovezave = new List<List<Povezave>>();

                //Nad množico χ tvorimo konveksno lupino.
                for (int i = 0; i < obhodQH.Count - 1; i+=2)
                {
                    double razdalja = Math.Max(Math.Abs(obhodQH[i].X -obhodQH[i + 1].X), Math.Abs(obhodQH[i].Y - obhodQH[i + 1].Y));
                    povezaneTocke.Add(new Povezave(obhodQH[i], obhodQH[i + 1], razdalja));
                }

                vsePovezave.Add(new List<Povezave>(povezaneTocke));

                for (int i = 0; i < obhodQH.Count; i++)
                {
                    for (int j = 0; j < tmpPoints.Count; j++)
                    {
                        if (tmpPoints[j] == obhodQH[i]) tmpPoints.RemoveAt(j);
                    }
                }


                /*for (int i = 0; i < povezaneTocke.Count; i++)
                {
                    Line linija = new Line();
                    linija.Stroke = Brushes.Black;
                    linija.StrokeThickness = 1;
                    linija.Fill = Brushes.Black;

                    linija.X1 = povezaneTocke[i].x.X;
                    linija.Y1 = povezaneTocke[i].x.Y;
                    linija.X2 = povezaneTocke[i].y.X;
                    linija.Y2 = povezaneTocke[i].y.Y;
                    canvas.Children.Add(linija);
                }*/

                while(tmpPoints.Count > 0)
                {
                    obhodQH.Clear();
                    povezaneTocke.Clear();

                    {

                        int E1 = 0, E2 = 0;
                        for (int j = 0; j < tmpPoints.Count; j++)
                        {
                            if (tmpPoints[j].X < tmpPoints[E1].X)
                            {
                                E1 = j;
                            }
                            if (tmpPoints[j].X > tmpPoints[E2].X)
                            {
                                E2 = j;
                            }
                        }

                        //imamo loceno na dve strani in jih posebej resujemo
                        QuickHull(tmpPoints[E1], tmpPoints[E2], 1, tmpPoints);
                        QuickHull(tmpPoints[E1], tmpPoints[E2], -1, tmpPoints);
                    }

                    //Nad množico χ tvorimo konveksno lupino.
                    for (int i = 0; i < obhodQH.Count - 1; i+=2)
                    {
                        double razdalja = Math.Max(Math.Abs(obhodQH[i].X -obhodQH[i + 1].X), Math.Abs(obhodQH[i].Y - obhodQH[i + 1].Y));
                        povezaneTocke.Add(new Povezave(obhodQH[i], obhodQH[i + 1], razdalja));
                    }

                    vsePovezave.Add(new List<Povezave>(povezaneTocke));

                    for (int i = 0; i < obhodQH.Count; i++)
                    {
                        for (int j = 0; j < tmpPoints.Count; j++)
                        {
                            if (tmpPoints[j] == obhodQH[i]) tmpPoints.RemoveAt(j);
                        }
                    }


                    /*for (int i = 0; i < povezaneTocke.Count; i++)
                    {
                        Line linija = new Line();
                        linija.Stroke = Brushes.Black;
                        linija.StrokeThickness = 1;
                        linija.Fill = Brushes.Black;

                        linija.X1 = povezaneTocke[i].x.X;
                        linija.Y1 = povezaneTocke[i].x.Y;
                        linija.X2 = povezaneTocke[i].y.X;
                        linija.Y2 = povezaneTocke[i].y.Y;
                        canvas.Children.Add(linija);
                    }*/
                }

                Point povezi;

                for (int i = 0; i < vsePovezave.Count; i++)
                {
                    int index = 0;

                    Point max = vsePovezave[i][0].x;
                    for (int j = 0; j < vsePovezave[i].Count; j++)
                    {
                        if (max.Y >= vsePovezave[i][j].x.Y)
                        {
                            if(!(vsePovezave[i][j].x.Y == max.Y && max.X < vsePovezave[i][j].x.X))
                            {
                                max = vsePovezave[i][j].x;
                                index = j;

                            }
                        }
                        if (max.Y >= vsePovezave[i][j].y.Y)
                        {
                            if (!(vsePovezave[i][j].y.Y == max.Y && max.X < vsePovezave[i][j].y.X))
                            {
                                max = vsePovezave[i][j].y;
                                index = j;

                            }
                        }
                    }

                    if (i != 0)
                    {
                        /*Line linija = new Line();
                        linija.Stroke = Brushes.Black;
                        linija.StrokeThickness = 1;
                        linija.Fill = Brushes.Black;

                        linija.X1 = povezi.X;
                        linija.Y1 = povezi.Y;
                        linija.X2 = max.X;
                        linija.Y2 = max.Y;
                        canvas.Children.Add(linija);*/

                        double razdalja = Math.Max(Math.Abs(povezi.X - max.X), Math.Abs(povezi.Y - max.Y));
                        vsePovezave[i].Add(new Povezave(povezi, max, razdalja));
                    }




                    if (max == vsePovezave[i][index].x)
                    {
                        povezi = vsePovezave[i][index].y;
                    }
                    if (max == vsePovezave[i][index].y)
                    {
                        povezi = vsePovezave[i][index].x;
                    }

                    vsePovezave[i].RemoveAt(index);

                    for (int j = 0; j < vsePovezave[i].Count; j++)
                    {
                        Line linija = new Line();
                        linija.Stroke = Brushes.Black;
                        linija.StrokeThickness = 1;
                        linija.Fill = Brushes.Black;

                        linija.X1 = vsePovezave[i][j].x.X;
                        linija.Y1 = vsePovezave[i][j].x.Y;
                        linija.X2 = vsePovezave[i][j].y.X;
                        linija.Y2 = vsePovezave[i][j].y.Y;
                        canvas.Children.Add(linija);
                    }
                }

                for (int i = 0; i < vsePovezave.Count; i++)
                {
                    
                }

            }
        }
    }
}
