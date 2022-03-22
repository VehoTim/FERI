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

namespace Vaja01
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        //nastavljanje gumba calculate
        private void textBoxLostKeyFocus1(object sender, KeyboardFocusChangedEventArgs e)
        {
            if (rbTwoPoints.IsChecked == true)
            {
                if (txtBoxT1x.Text != "" && txtBoxT1y.Text != "" && txtBoxT2x.Text != "" && txtBoxT2y.Text != "")
                {
                    btCalculate.IsEnabled = true;
                }
            }
            else if (rbOnePointOneLine.IsChecked == true)
            {
                if (txtBoxT1x.Text != "" && txtBoxT1y.Text != "" && txtBoxT2x.Text != "" && txtBoxT2y.Text != ""
                    && txtBoxT3x.Text != "" && txtBoxT3y.Text != "")
                {
                    btCalculate.IsEnabled = true;
                }
            }
            else if (rbTwoLines.IsChecked == true)
            {
                if (txtBoxT1x.Text != "" && txtBoxT1y.Text != "" && txtBoxT2x.Text != "" && txtBoxT2y.Text != ""
                   && txtBoxT3x.Text != "" && txtBoxT3y.Text != "" && txtBoxT4x.Text != "" && txtBoxT4y.Text != "")
                {
                    btCalculate.IsEnabled = true;
                }
            }

            
        }

        //switchanje med radio gumbi
        private void checkedChanged(object sender, RoutedEventArgs e)
        {
            if (rbTwoPoints.IsChecked == true)
            {
                txtBoxT3x.IsEnabled = false;
                txtBoxT3y.IsEnabled = false;

                txtBoxT4x.IsEnabled = false;
                txtBoxT4y.IsEnabled = false;
            }
            else if (rbOnePointOneLine.IsChecked == true)
            {
                txtBoxT3x.IsEnabled = true;
                txtBoxT3y.IsEnabled = true;

                txtBoxT4x.IsEnabled = false;
                txtBoxT4y.IsEnabled = false;
            }
            else if(rbTwoLines.IsChecked == true)
            {
                txtBoxT3x.IsEnabled = true;
                txtBoxT3y.IsEnabled = true;

                txtBoxT4x.IsEnabled = true;
                txtBoxT4y.IsEnabled = true;
            }
        }

        //gumb calculate klik
        private void btCalculate_Click(object sender, RoutedEventArgs e)
        {
            canvas1.Children.Clear();

            //prva tocka naloge (razdalje) - dve tocki
            if(rbTwoPoints.IsChecked == true)
            {
                double manhattan = Math.Abs(double.Parse(txtBoxT1x.Text) - double.Parse(txtBoxT2x.Text)) + Math.Abs(double.Parse(txtBoxT1y.Text) - double.Parse(txtBoxT2y.Text));
                double evklid = Math.Sqrt(Math.Pow((double.Parse(txtBoxT1x.Text) - double.Parse(txtBoxT2x.Text)),2)
                                          + Math.Pow((double.Parse(txtBoxT1y.Text) - double.Parse(txtBoxT2y.Text)), 2));
                double chebyshev = Math.Max(Math.Abs(double.Parse(txtBoxT1x.Text) - double.Parse(txtBoxT2x.Text)), Math.Abs(double.Parse(txtBoxT1y.Text) - double.Parse(txtBoxT2y.Text)));

                lbRezultat.Content = "Manhattan: " + manhattan +
                                     "\nEvklid: " + evklid +
                                     "\nChebyshev: " + chebyshev;
            }

            //druga tocka naloge - ena tocka, ena daljicas
            else if(rbOnePointOneLine.IsChecked == true)
            {
                //tocke
                Point T1 = new Point();
                T1.X = double.Parse(txtBoxT1x.Text);
                T1.Y = double.Parse(txtBoxT1y.Text);

                Point T2 = new Point();
                T2.X = double.Parse(txtBoxT2x.Text);
                T2.Y = double.Parse(txtBoxT2y.Text);

                Point T3 = new Point();
                T3.X = double.Parse(txtBoxT3x.Text);
                T3.Y = double.Parse(txtBoxT3y.Text);

                //------------------------------------

                //Izris teh tock

                Rectangle tocka1 = new Rectangle();

                tocka1.Width = 5; tocka1.Height = 5;

                tocka1.Fill = System.Windows.Media.Brushes.Black;
                tocka1.Stroke = System.Windows.Media.Brushes.Black;

                tocka1.Margin = new Thickness(T1.X, T1.Y, 0, 0);

                canvas1.Children.Add(tocka1);

                Rectangle tocka2 = new Rectangle();

                tocka2.Width = 5; tocka2.Height = 5;

                tocka2.Fill = System.Windows.Media.Brushes.Black;
                tocka2.Stroke = System.Windows.Media.Brushes.Black;

                tocka2.Margin = new Thickness(T2.X, T2.Y, 0, 0);

                canvas1.Children.Add(tocka2);

                Rectangle tocka3 = new Rectangle();

                tocka3.Width = 5; tocka3.Height = 5;

                tocka3.Fill = Brushes.Black;
                tocka3.Stroke = Brushes.Black;

                tocka3.Margin = new Thickness(T3.X, T3.Y, 0, 0);

                canvas1.Children.Add(tocka3);

                //------------------------------------

                //Povezava T2 in T3

                Line linija = new Line();
                linija.Stroke = Brushes.Black;
                linija.StrokeThickness = 1;
                linija.Fill = System.Windows.Media.Brushes.Black;

                linija.X1 = T2.X;
                linija.Y1 = T2.Y;

                linija.X2 = T3.X;
                linija.Y2 = T3.Y;


                canvas1.Children.Add(linija);

                //------------------------------------


                //Nastavitev vektorjev V1, V2 in Vn
                Vector v1 = T3 - T2;
                Vector v2 = T1 - T2;

                Vector vn = v1;
                vn.Normalize();

                //Skalarni produkt s pomocjo katerega bomo dolocili pozicijo tocke
                double sp = vn * v2;

                Point Tp;

                //Je pravokotno na linijo
                if (sp >= 0 && sp <= Math.Abs(v1.Length))
                {
                    Tp = T2 + vn * sp;
                }
                //ni pravokotno
                else
                {
                    //poiscemo keri tocki je blizje
                    double r1 = Math.Sqrt(Math.Pow((T1.X - T2.X), 2)
                               + Math.Pow((T1.Y - T2.Y), 2));

                    double r2 = Math.Sqrt(Math.Pow((T1.X - T3.X), 2)
                               + Math.Pow((T1.Y - T3.Y), 2));

                    if(r1 > r2) Tp = T3;
                    else Tp = T2;
                }

                //narisemo tocko na daljici najblizje T1
                Rectangle rectangle2 = new Rectangle();

                rectangle2.Width = 5; rectangle2.Height = 5;

                rectangle2.Fill = Brushes.Red;
                rectangle2.Stroke = Brushes.Red;

                rectangle2.Margin = new Thickness(Tp.X, Tp.Y, 0, 0);

                //in linijo
                Line linija2 = new Line();
                linija2.Stroke = Brushes.Blue;
                linija2.StrokeThickness = 1;
                linija2.Fill = Brushes.Blue;

                linija2.X1 = Tp.X;
                linija2.Y1 = Tp.Y;

                linija2.X2 = T1.X;
                linija2.Y2 = T1.Y;


                canvas1.Children.Add(linija2);

                canvas1.Children.Add(rectangle2);

                //------------------------------------

                //Izpis razdalje

                double razdalja = Math.Sqrt(Math.Pow((T1.X - Tp.X), 2)
                                          + Math.Pow((T1.Y - Tp.Y), 2));

                lbRezultat.Content = "Razdalja: " + razdalja;

                //------------------------------------
            }
            //tretja tocka naloge - dve daljici
            else if(rbTwoLines.IsChecked == true)
            {
                //Tocke
                Point T1 = new Point();
                T1.X = double.Parse(txtBoxT1x.Text);
                T1.Y = double.Parse(txtBoxT1y.Text);

                Point T2 = new Point();
                T2.X = double.Parse(txtBoxT2x.Text);
                T2.Y = double.Parse(txtBoxT2y.Text);

                Point T3 = new Point();
                T3.X = double.Parse(txtBoxT3x.Text);
                T3.Y = double.Parse(txtBoxT3y.Text);

                Point T4 = new Point();
                T4.X = double.Parse(txtBoxT4x.Text);
                T4.Y = double.Parse(txtBoxT4y.Text);

                //------------------------------------

                //Izris teh tock

                Rectangle tocka1 = new Rectangle();

                tocka1.Width = 5; tocka1.Height = 5;

                tocka1.Fill = Brushes.Black;
                tocka1.Stroke = Brushes.Black;

                tocka1.Margin = new Thickness(T1.X, T1.Y, 0, 0);

                canvas1.Children.Add(tocka1);

                Rectangle tocka2 = new Rectangle();

                tocka2.Width = 5; tocka2.Height = 5;

                tocka2.Fill = Brushes.Black;
                tocka2.Stroke = Brushes.Black;

                tocka2.Margin = new Thickness(T2.X, T2.Y, 0, 0);

                canvas1.Children.Add(tocka2);

                Rectangle tocka3 = new Rectangle();

                tocka3.Width = 5; tocka3.Height = 5;

                tocka3.Fill = Brushes.Black;
                tocka3.Stroke = Brushes.Black;

                tocka3.Margin = new Thickness(T3.X, T3.Y, 0, 0);

                canvas1.Children.Add(tocka3);

                Rectangle tocka4 = new Rectangle();

                tocka4.Width = 5; tocka4.Height = 5;

                tocka4.Fill = Brushes.Black;
                tocka4.Stroke = Brushes.Black;

                tocka4.Margin = new Thickness(T4.X, T4.Y, 0, 0);

                canvas1.Children.Add(tocka4);

                //------------------------------------

                //Izris linije

                Line linija = new Line();
                linija.Stroke = Brushes.Black;
                linija.StrokeThickness = 1;
                linija.Fill = System.Windows.Media.Brushes.Black;

                linija.X1 = T1.X;
                linija.Y1 = T1.Y;

                linija.X2 = T2.X;
                linija.Y2 = T2.Y;

                canvas1.Children.Add(linija);

                Line linija2 = new Line();
                linija2.Stroke = Brushes.Black;
                linija2.StrokeThickness = 1;
                linija2.Fill = Brushes.Black;

                linija2.X1 = T3.X;
                linija2.Y1 = T3.Y;

                linija2.X2 = T4.X;
                linija2.Y2 = T4.Y;

                canvas1.Children.Add(linija2);

                //------------------------------------

                //Izracun A, B, D
                double A = (T4.X - T3.X) * (T1.Y - T3.Y) - (T1.X - T3.X) * (T4.Y - T3.Y);
                double B = (T2.X - T1.X) * (T1.Y - T3.Y) - (T1.X - T3.X) * (T2.Y - T1.Y);
                double D = (T2.X - T1.X) * (T4.Y - T3.Y) - (T4.X - T3.X) * (T2.Y - T1.Y);

                //Daljici sovpadata
                if(A == 0 && B == 0 && D == 0)
                {
                    lbRezultat.Content = "Daljici sovpadata";
                    return;
                }
                //Daljici sta vzporedni
                else if (D == 0)
                {
                    lbRezultat.Content = "Daljici sta vzporedni";
                    return;
                }

                //Ua, Ub
                double Ua = A / D;
                double Ub = B / D;

                //Daljici se sekata
                if(Ua >= 0 && Ua <= 1 && Ub >= 0 && Ub <= 1)
                {

                    double x = T1.X + Ua * (T2.X - T1.X);
                    double y = T1.Y + Ua * (T2.Y - T1.Y);

                    lbRezultat.Content = "Daljici se sekata v tocki: " + x + "," + y;


                    Point Tp = new Point();
                    Tp.X = x;
                    Tp.Y = y;

                    Rectangle tockaP = new Rectangle();

                    tockaP.Width = 5; tockaP.Height = 5;

                    tockaP.Fill = System.Windows.Media.Brushes.Red;
                    tockaP.Stroke = System.Windows.Media.Brushes.Red;

                    tockaP.Margin = new Thickness(Tp.X, Tp.Y, 0, 0);

                    canvas1.Children.Add(tockaP);
                }
            }
        }
    }
}
