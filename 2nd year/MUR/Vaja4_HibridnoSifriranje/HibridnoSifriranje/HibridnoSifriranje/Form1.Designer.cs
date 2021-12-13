namespace HibridnoSifriranje
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.Posiljanje = new System.Windows.Forms.Button();
            this.buttonPrejemanje = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(180, 103);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            // 
            // Posiljanje
            // 
            this.Posiljanje.Location = new System.Drawing.Point(63, 55);
            this.Posiljanje.Name = "Posiljanje";
            this.Posiljanje.Size = new System.Drawing.Size(75, 23);
            this.Posiljanje.TabIndex = 1;
            this.Posiljanje.Text = "Posiljanje";
            this.Posiljanje.UseVisualStyleBackColor = true;
            this.Posiljanje.Click += new System.EventHandler(this.buttonPosiljanje_click);
            // 
            // buttonPrejemanje
            // 
            this.buttonPrejemanje.Location = new System.Drawing.Point(233, 55);
            this.buttonPrejemanje.Name = "buttonPrejemanje";
            this.buttonPrejemanje.Size = new System.Drawing.Size(75, 23);
            this.buttonPrejemanje.TabIndex = 2;
            this.buttonPrejemanje.Text = "Prejemanje";
            this.buttonPrejemanje.UseVisualStyleBackColor = true;
            this.buttonPrejemanje.Click += new System.EventHandler(this.buttonPrejemanje_click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(395, 153);
            this.Controls.Add(this.buttonPrejemanje);
            this.Controls.Add(this.Posiljanje);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Posiljanje;
        private System.Windows.Forms.Button buttonPrejemanje;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
    }
}

