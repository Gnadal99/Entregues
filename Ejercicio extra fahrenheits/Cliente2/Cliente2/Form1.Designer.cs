namespace Cliente2
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
            this.Celsius = new System.Windows.Forms.TextBox();
            this.Fahren = new System.Windows.Forms.TextBox();
            this.butFar = new System.Windows.Forms.Button();
            this.butCel = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Celsius
            // 
            this.Celsius.Location = new System.Drawing.Point(99, 53);
            this.Celsius.Name = "Celsius";
            this.Celsius.Size = new System.Drawing.Size(100, 22);
            this.Celsius.TabIndex = 0;
            // 
            // Fahren
            // 
            this.Fahren.Location = new System.Drawing.Point(99, 105);
            this.Fahren.Name = "Fahren";
            this.Fahren.Size = new System.Drawing.Size(100, 22);
            this.Fahren.TabIndex = 1;
            // 
            // butFar
            // 
            this.butFar.Location = new System.Drawing.Point(219, 105);
            this.butFar.Name = "butFar";
            this.butFar.Size = new System.Drawing.Size(161, 23);
            this.butFar.TabIndex = 2;
            this.butFar.Text = "Convertir a Celsius";
            this.butFar.UseVisualStyleBackColor = true;
            this.butFar.Click += new System.EventHandler(this.butFar_Click);
            // 
            // butCel
            // 
            this.butCel.Location = new System.Drawing.Point(219, 53);
            this.butCel.Name = "butCel";
            this.butCel.Size = new System.Drawing.Size(161, 23);
            this.butCel.TabIndex = 3;
            this.butCel.Text = "Convertir a Fahrenheit";
            this.butCel.UseVisualStyleBackColor = true;
            this.butCel.Click += new System.EventHandler(this.butCel_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 17);
            this.label1.TabIndex = 4;
            this.label1.Text = "Celsius:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 108);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 17);
            this.label2.TabIndex = 5;
            this.label2.Text = "Fahrenheit:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 6;
            this.button1.Text = "Conectar";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(399, 211);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.butCel);
            this.Controls.Add(this.butFar);
            this.Controls.Add(this.Fahren);
            this.Controls.Add(this.Celsius);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Celsius;
        private System.Windows.Forms.TextBox Fahren;
        private System.Windows.Forms.Button butFar;
        private System.Windows.Forms.Button butCel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
    }
}

