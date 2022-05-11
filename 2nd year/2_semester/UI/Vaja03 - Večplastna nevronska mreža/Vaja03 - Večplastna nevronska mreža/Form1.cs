namespace Vaja03___Večplastna_nevronska_mreža
{
    public partial class Form1 : Form
    {
        public struct Seznam
        {
            public string znak;
            public List<Normalizirana> tocke;

            public Seznam(string znak, List<Normalizirana> tocke)
            {
                this.znak = znak; this.tocke = new List<Normalizirana>(tocke);
            }
        }

        public struct Normalizirana
        {
            public double x, y;

            public Normalizirana(double x, double y) { this.x = x; this.y = y; }
        }

        public Form1()
        {
            InitializeComponent();
            g = panel1.CreateGraphics();
        }

        bool clicked = false;
        Point previousPoint;
        public Graphics g;

        List<Point> points = new List<Point>();
        List<Normalizirana> normalizirane = new List<Normalizirana>();
        List<Seznam> vnosi = new List<Seznam> ();

        bool ucenje = true;


        private void button1_Click(object sender, EventArgs e)
        {
            if (ucenje)
            {


                ucenje = false;
            }
            else
            {

            }

            //panel1.Invalidate();
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            panel1.Invalidate();

            clicked = true;
            previousPoint = e.Location;

            points.Clear();
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (clicked)
            {
                g.DrawLine(Pens.Black, previousPoint, e.Location);
                points.Add(previousPoint);
                points.Add(e.Location);
                previousPoint = e.Location;

                Invalidate();
            }
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            if (ucenje)
            {


                clicked = false;

                string znak = PupUpForm.ShowDialog("Vpisi znacko narisanega znaka");

                Point prva = points[0];
                Point zadnja = points[points.Count - 1];

                g.DrawRectangle(Pens.Red, prva.X - 1, prva.Y - 1, 3, 3);
                g.DrawRectangle(Pens.Red, zadnja.X - 1, zadnja.Y - 1, 3, 3);

                decimal N = numVectors.Value;

                List<Point> tmp = new List<Point>(points);
                Point zacasna = new Point();

                do
                {
                    for (int i = 1; i < tmp.Count - 2; i++)
                    {
                        zacasna.X = (tmp[i].X + tmp[i + 1].X) / 2;
                        zacasna.Y = (tmp[i].Y + tmp[i + 1].Y) / 2;

                        tmp[i] = zacasna;
                        tmp.RemoveAt(i+1);
                        if (tmp.Count <= N + 1) break;
                    }
                } while (tmp.Count > N + 1);

                panel1.Controls.Clear(); panel1.Refresh();

                double maxX = points[0].X;
                double maxY = points[0].Y;

                for (int i = 0; i < tmp.Count - 1; i++)
                {

                    if (tmp[i + 1].X > maxX) maxX = tmp[i + 1].X;
                    if (tmp[i + 1].Y > maxY) maxY = tmp[i + 1].Y;

                    g.DrawRectangle(Pens.Red, tmp[i].X - 1, tmp[i].Y - 1, 3, 3);
                    g.DrawRectangle(Pens.Red, tmp[i+1].X - 1, tmp[i+1].Y - 1, 3, 3);

                    g.DrawLine(Pens.Black, tmp[i], tmp[i + 1]);
                }

                normalizirane.Clear();
                //normalizacija
                for (int i = 0; i < tmp.Count; i++)
                {

                    normalizirane.Add(new(tmp[i].X / maxX, tmp[i].Y / maxY));
                }

                vnosi.Add(new(znak, normalizirane));
            }
            else
            {
                clicked = false;

                Point prva = points[0];
                Point zadnja = points[points.Count - 1];

                g.DrawRectangle(Pens.Red, prva.X - 1, prva.Y - 1, 3, 3);
                g.DrawRectangle(Pens.Red, zadnja.X - 1, zadnja.Y - 1, 3, 3);

                decimal N = numVectors.Value;

                List<Point> tmp = new List<Point>(points);
                Point zacasna = new Point();

                do
                {
                    for (int i = 1; i < tmp.Count - 2; i++)
                    {
                        zacasna.X = (tmp[i].X + tmp[i + 1].X) / 2;
                        zacasna.Y = (tmp[i].Y + tmp[i + 1].Y) / 2;

                        tmp[i] = zacasna;
                        tmp.RemoveAt(i+1);
                        if (tmp.Count <= N + 1)
                        {
                            break;
                        }
                    }
                } while (tmp.Count > N + 1);

                panel1.Controls.Clear(); panel1.Refresh();

                double maxX = points[0].X;
                double maxY = points[0].Y;

                for (int i = 0; i < tmp.Count - 1; i++)
                {

                    if (tmp[i + 1].X > maxX) maxX = tmp[i + 1].X;
                    if (tmp[i + 1].Y > maxY) maxY = tmp[i + 1].Y;

                    g.DrawRectangle(Pens.Red, tmp[i].X - 1, tmp[i].Y - 1, 3, 3);
                    g.DrawRectangle(Pens.Red, tmp[i+1].X - 1, tmp[i+1].Y - 1, 3, 3);

                    g.DrawLine(Pens.Black, tmp[i], tmp[i + 1]);
                }

                normalizirane.Clear();
                //normalizacija
                for (int i = 0; i < tmp.Count; i++)
                {

                    normalizirane.Add(new(tmp[i].X / maxX, tmp[i].Y / maxY));
                }

                vnosi.Add(new("", normalizirane));
            }
        }
    }
    public static class PupUpForm
    {
        public static string ShowDialog(string text, string caption = "")
        {
            Form popUpForm = new Form()
            {
                Width = 250,
                Height = 100,
                FormBorderStyle = FormBorderStyle.FixedDialog,
                Text = caption,
                StartPosition = FormStartPosition.CenterScreen
            };

            Label textLabel = new Label() { Left = 10, Top = 10, Text = text };
            TextBox textBox = new TextBox() { Left = 10, Top = 30, Width = 150 };
            Button confirmation = new Button() { Text = "Ok", Left = 160, Width = 50, Top = 30, DialogResult = DialogResult.OK };
            confirmation.Click += (sender, e) => { popUpForm.Close(); };
            popUpForm.Controls.Add(textBox);
            popUpForm.Controls.Add(confirmation);
            popUpForm.Controls.Add(textLabel);
            popUpForm.AcceptButton = confirmation;

            return popUpForm.ShowDialog() == DialogResult.OK ? textBox.Text : "";
        }
    }
}