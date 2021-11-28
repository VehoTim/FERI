namespace KlepetGUI
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxUsername = new System.Windows.Forms.TextBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.buttonPrekini = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxSporocilo = new System.Windows.Forms.TextBox();
            this.buttonPoslji = new System.Windows.Forms.Button();
            this.richTextBoxVsebina = new System.Windows.Forms.RichTextBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Uporabnik:";
            // 
            // textBoxUsername
            // 
            this.textBoxUsername.Location = new System.Drawing.Point(99, 19);
            this.textBoxUsername.Name = "textBoxUsername";
            this.textBoxUsername.Size = new System.Drawing.Size(185, 23);
            this.textBoxUsername.TabIndex = 1;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(290, 18);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "Povezi";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // buttonPrekini
            // 
            this.buttonPrekini.Enabled = false;
            this.buttonPrekini.Location = new System.Drawing.Point(413, 19);
            this.buttonPrekini.Name = "buttonPrekini";
            this.buttonPrekini.Size = new System.Drawing.Size(75, 23);
            this.buttonPrekini.TabIndex = 3;
            this.buttonPrekini.Text = "Prekini";
            this.buttonPrekini.UseVisualStyleBackColor = true;
            this.buttonPrekini.Click += new System.EventHandler(this.buttonPrekini_Click);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 426);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 15);
            this.label2.TabIndex = 4;
            this.label2.Text = "Sporocilo:";
            // 
            // textBoxSporocilo
            // 
            this.textBoxSporocilo.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.textBoxSporocilo.Enabled = false;
            this.textBoxSporocilo.Location = new System.Drawing.Point(78, 423);
            this.textBoxSporocilo.Name = "textBoxSporocilo";
            this.textBoxSporocilo.Size = new System.Drawing.Size(318, 23);
            this.textBoxSporocilo.TabIndex = 5;
            // 
            // buttonPoslji
            // 
            this.buttonPoslji.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonPoslji.Enabled = false;
            this.buttonPoslji.Location = new System.Drawing.Point(413, 422);
            this.buttonPoslji.Name = "buttonPoslji";
            this.buttonPoslji.Size = new System.Drawing.Size(75, 23);
            this.buttonPoslji.TabIndex = 6;
            this.buttonPoslji.Text = "Poslji";
            this.buttonPoslji.UseVisualStyleBackColor = true;
            this.buttonPoslji.Click += new System.EventHandler(this.buttonPoslji_Click);
            // 
            // richTextBoxVsebina
            // 
            this.richTextBoxVsebina.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxVsebina.Location = new System.Drawing.Point(12, 48);
            this.richTextBoxVsebina.Name = "richTextBoxVsebina";
            this.richTextBoxVsebina.ReadOnly = true;
            this.richTextBoxVsebina.Size = new System.Drawing.Size(476, 368);
            this.richTextBoxVsebina.TabIndex = 7;
            this.richTextBoxVsebina.Text = "";
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            // 
            // Form1
            // 
            this.AcceptButton = this.buttonConnect;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 450);
            this.Controls.Add(this.richTextBoxVsebina);
            this.Controls.Add(this.buttonPoslji);
            this.Controls.Add(this.textBoxSporocilo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonPrekini);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.textBoxUsername);
            this.Controls.Add(this.label1);
            this.MinimumSize = new System.Drawing.Size(515, 489);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private TextBox textBoxUsername;
        private Button buttonConnect;
        private Button buttonPrekini;
        private Label label2;
        private TextBox textBoxSporocilo;
        private Button buttonPoslji;
        private RichTextBox richTextBoxVsebina;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}