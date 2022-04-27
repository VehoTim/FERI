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
            Point x;
            Point y;
            double razdalja;

            public Povezave(Point x, Point y, double razdalja)
            {
                this.x = x; this.y = y; this.razdalja = razdalja;
            }
        }

        List<Povezave> povezaneTocke = new List<Povezave>();

        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            if(rbMinUtez.IsChecked == true)
            {
                for (int i = 0; i < points.Count; i++)
                {
                    for (int j = i + 1; j < points.Count; j++)
                    {
                        double razdalja = Math.Max(Math.Abs(points[i].X -points[j].X), Math.Abs(points[i].Y - points[j].Y));
                        povezaneTocke.Add(new Povezave(points[i], points[j], razdalja));
                    }   
                }

                //sortirati
                povezaneTocke.Sort((x, y) => x.razdalja.CompareTo(y.razdalja));
            }
            else if(rbHamilton.IsChecked == true)
            {

            }
        }
    }
}
