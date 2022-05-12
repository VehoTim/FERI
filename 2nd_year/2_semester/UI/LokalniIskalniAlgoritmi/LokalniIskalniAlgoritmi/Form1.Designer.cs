namespace LokalniIskalniAlgoritmi
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbGenet = new System.Windows.Forms.RadioButton();
            this.rbLokal = new System.Windows.Forms.RadioButton();
            this.rbOhlajanje = new System.Windows.Forms.RadioButton();
            this.rbVzpenjanje = new System.Windows.Forms.RadioButton();
            this.btnStart = new System.Windows.Forms.Button();
            this.labelHev = new System.Windows.Forms.Label();
            this.labelHev2 = new System.Windows.Forms.Label();
            this.labelStPomikov = new System.Windows.Forms.Label();
            this.nmStPomikov = new System.Windows.Forms.NumericUpDown();
            this.labelDim = new System.Windows.Forms.Label();
            this.labelStKorakov2 = new System.Windows.Forms.Label();
            this.labelStKorakov = new System.Windows.Forms.Label();
            this.btnGeneriraj = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.nmTemp = new System.Windows.Forms.NumericUpDown();
            this.nmDelTemp = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.nmStanja = new System.Windows.Forms.NumericUpDown();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nmStPomikov)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmDelTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmStanja)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "4x4",
            "5x5",
            "6x6",
            "7x7",
            "8x8",
            "9x9",
            "10x10",
            "11x11",
            "12x12"});
            this.comboBox1.Location = new System.Drawing.Point(638, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(75, 23);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(400, 400);
            this.flowLayoutPanel1.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbGenet);
            this.groupBox1.Controls.Add(this.rbLokal);
            this.groupBox1.Controls.Add(this.rbOhlajanje);
            this.groupBox1.Controls.Add(this.rbVzpenjanje);
            this.groupBox1.Location = new System.Drawing.Point(431, 121);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(282, 72);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // rbGenet
            // 
            this.rbGenet.AutoSize = true;
            this.rbGenet.Enabled = false;
            this.rbGenet.Location = new System.Drawing.Point(134, 47);
            this.rbGenet.Name = "rbGenet";
            this.rbGenet.Size = new System.Drawing.Size(124, 19);
            this.rbGenet.TabIndex = 3;
            this.rbGenet.TabStop = true;
            this.rbGenet.Text = "Genetski algoritem";
            this.rbGenet.UseVisualStyleBackColor = true;
            // 
            // rbLokal
            // 
            this.rbLokal.AutoSize = true;
            this.rbLokal.Location = new System.Drawing.Point(6, 47);
            this.rbLokal.Name = "rbLokal";
            this.rbLokal.Size = new System.Drawing.Size(93, 19);
            this.rbLokal.TabIndex = 2;
            this.rbLokal.TabStop = true;
            this.rbLokal.Text = "Lokalni žarek";
            this.rbLokal.UseVisualStyleBackColor = true;
            this.rbLokal.CheckedChanged += new System.EventHandler(this.rbVzpenjanje_CheckedChanged);
            // 
            // rbOhlajanje
            // 
            this.rbOhlajanje.AutoSize = true;
            this.rbOhlajanje.Location = new System.Drawing.Point(134, 22);
            this.rbOhlajanje.Name = "rbOhlajanje";
            this.rbOhlajanje.Size = new System.Drawing.Size(133, 19);
            this.rbOhlajanje.TabIndex = 1;
            this.rbOhlajanje.TabStop = true;
            this.rbOhlajanje.Text = "Simulirano ohlajanje";
            this.rbOhlajanje.UseVisualStyleBackColor = true;
            this.rbOhlajanje.CheckedChanged += new System.EventHandler(this.rbVzpenjanje_CheckedChanged);
            // 
            // rbVzpenjanje
            // 
            this.rbVzpenjanje.AutoSize = true;
            this.rbVzpenjanje.Checked = true;
            this.rbVzpenjanje.Location = new System.Drawing.Point(6, 22);
            this.rbVzpenjanje.Name = "rbVzpenjanje";
            this.rbVzpenjanje.Size = new System.Drawing.Size(122, 19);
            this.rbVzpenjanje.TabIndex = 0;
            this.rbVzpenjanje.TabStop = true;
            this.rbVzpenjanje.Text = "Vzpenjanje na hrib";
            this.rbVzpenjanje.UseVisualStyleBackColor = true;
            this.rbVzpenjanje.CheckedChanged += new System.EventHandler(this.rbVzpenjanje_CheckedChanged);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(638, 366);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 3;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // labelHev
            // 
            this.labelHev.AutoSize = true;
            this.labelHev.Location = new System.Drawing.Point(573, 51);
            this.labelHev.Name = "labelHev";
            this.labelHev.Size = new System.Drawing.Size(65, 15);
            this.labelHev.TabIndex = 4;
            this.labelHev.Text = "Hevristika: ";
            // 
            // labelHev2
            // 
            this.labelHev2.AutoSize = true;
            this.labelHev2.Location = new System.Drawing.Point(638, 51);
            this.labelHev2.Name = "labelHev2";
            this.labelHev2.Size = new System.Drawing.Size(0, 15);
            this.labelHev2.TabIndex = 5;
            // 
            // labelStPomikov
            // 
            this.labelStPomikov.AutoSize = true;
            this.labelStPomikov.Location = new System.Drawing.Point(437, 201);
            this.labelStPomikov.Name = "labelStPomikov";
            this.labelStPomikov.Size = new System.Drawing.Size(187, 15);
            this.labelStPomikov.TabIndex = 6;
            this.labelStPomikov.Text = "St. pomikov v enakovredna stanja:";
            // 
            // nmStPomikov
            // 
            this.nmStPomikov.Location = new System.Drawing.Point(630, 199);
            this.nmStPomikov.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.nmStPomikov.Name = "nmStPomikov";
            this.nmStPomikov.Size = new System.Drawing.Size(83, 23);
            this.nmStPomikov.TabIndex = 8;
            this.nmStPomikov.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // labelDim
            // 
            this.labelDim.AutoSize = true;
            this.labelDim.Location = new System.Drawing.Point(514, 15);
            this.labelDim.Name = "labelDim";
            this.labelDim.Size = new System.Drawing.Size(118, 15);
            this.labelDim.TabIndex = 9;
            this.labelDim.Text = "Dimenzija šahovnice:";
            // 
            // labelStKorakov2
            // 
            this.labelStKorakov2.AutoSize = true;
            this.labelStKorakov2.Location = new System.Drawing.Point(638, 77);
            this.labelStKorakov2.Name = "labelStKorakov2";
            this.labelStKorakov2.Size = new System.Drawing.Size(0, 15);
            this.labelStKorakov2.TabIndex = 11;
            // 
            // labelStKorakov
            // 
            this.labelStKorakov.AutoSize = true;
            this.labelStKorakov.Location = new System.Drawing.Point(565, 77);
            this.labelStKorakov.Name = "labelStKorakov";
            this.labelStKorakov.Size = new System.Drawing.Size(68, 15);
            this.labelStKorakov.TabIndex = 10;
            this.labelStKorakov.Text = "Št. korakov:";
            // 
            // btnGeneriraj
            // 
            this.btnGeneriraj.Location = new System.Drawing.Point(557, 366);
            this.btnGeneriraj.Name = "btnGeneriraj";
            this.btnGeneriraj.Size = new System.Drawing.Size(75, 23);
            this.btnGeneriraj.TabIndex = 12;
            this.btnGeneriraj.Text = "Generiraj";
            this.btnGeneriraj.UseVisualStyleBackColor = true;
            this.btnGeneriraj.Click += new System.EventHandler(this.btnGeneriraj_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(432, 237);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 15);
            this.label1.TabIndex = 13;
            this.label1.Text = "Temperatura:";
            // 
            // nmTemp
            // 
            this.nmTemp.Enabled = false;
            this.nmTemp.Location = new System.Drawing.Point(451, 255);
            this.nmTemp.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.nmTemp.Name = "nmTemp";
            this.nmTemp.Size = new System.Drawing.Size(57, 23);
            this.nmTemp.TabIndex = 14;
            this.nmTemp.Value = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            // 
            // nmDelTemp
            // 
            this.nmDelTemp.Enabled = false;
            this.nmDelTemp.Location = new System.Drawing.Point(630, 255);
            this.nmDelTemp.Name = "nmDelTemp";
            this.nmDelTemp.Size = new System.Drawing.Size(60, 23);
            this.nmDelTemp.TabIndex = 16;
            this.nmDelTemp.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(548, 237);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(142, 15);
            this.label2.TabIndex = 15;
            this.label2.Text = "Sprememba temperature:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(551, 298);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 15);
            this.label3.TabIndex = 17;
            this.label3.Text = "Stevilo stanj:";
            // 
            // nmStanja
            // 
            this.nmStanja.Enabled = false;
            this.nmStanja.Location = new System.Drawing.Point(629, 296);
            this.nmStanja.Name = "nmStanja";
            this.nmStanja.Size = new System.Drawing.Size(60, 23);
            this.nmStanja.TabIndex = 18;
            this.nmStanja.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(734, 401);
            this.Controls.Add(this.nmStanja);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.nmDelTemp);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.nmTemp);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnGeneriraj);
            this.Controls.Add(this.labelStKorakov2);
            this.Controls.Add(this.labelStKorakov);
            this.Controls.Add(this.labelDim);
            this.Controls.Add(this.nmStPomikov);
            this.Controls.Add(this.labelStPomikov);
            this.Controls.Add(this.labelHev2);
            this.Controls.Add(this.labelHev);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.comboBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(750, 440);
            this.MinimumSize = new System.Drawing.Size(750, 440);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nmStPomikov)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmDelTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nmStanja)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private ComboBox comboBox1;
        private FlowLayoutPanel flowLayoutPanel1;
        private GroupBox groupBox1;
        private RadioButton rbVzpenjanje;
        private RadioButton rbOhlajanje;
        private RadioButton rbLokal;
        private RadioButton rbGenet;
        private Button btnStart;
        private Label labelHev;
        private Label labelHev2;
        private Label labelStPomikov;
        private NumericUpDown nmStPomikov;
        private Label labelDim;
        private Label labelStKorakov2;
        private Label labelStKorakov;
        private Button btnGeneriraj;
        private Label label1;
        private NumericUpDown nmTemp;
        private NumericUpDown nmDelTemp;
        private Label label2;
        private Label label3;
        private NumericUpDown nmStanja;
    }
}