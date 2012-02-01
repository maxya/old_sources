using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace FileOper
{
	public class Form1 : System.Windows.Forms.Form
	{		
		private System.Windows.Forms.Button bStart;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.Button RefreshBox;
		private System.ComponentModel.Container components = null;

		public Form1()
		{			
			InitializeComponent();
		}

		protected override void Dispose( bool disposing )
		{
			if( disposing )
				if (components != null) 
					components.Dispose();
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.bStart = new System.Windows.Forms.Button();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.RefreshBox = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// bStart
			// 
			this.bStart.Location = new System.Drawing.Point(32, 80);
			this.bStart.Name = "bStart";
			this.bStart.Size = new System.Drawing.Size(144, 32);
			this.bStart.TabIndex = 1;
			this.bStart.Text = "Enter";
			this.bStart.Click += new System.EventHandler(this.bStart_Click);
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(16, 24);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(168, 20);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = "Input text";
			// 
			// listBox1
			// 
			this.listBox1.Location = new System.Drawing.Point(200, 8);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(272, 134);
			this.listBox1.TabIndex = 2;
			this.listBox1.TabStop = false;
			// 
			// RefreshBox
			// 
			this.RefreshBox.Location = new System.Drawing.Point(344, 160);
			this.RefreshBox.Name = "RefreshBox";
			this.RefreshBox.Size = new System.Drawing.Size(72, 40);
			this.RefreshBox.TabIndex = 3;
			this.RefreshBox.Text = "Refresh";
			this.RefreshBox.Click += new System.EventHandler(this.Refresh_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(488, 229);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.RefreshBox,
																		  this.listBox1,
																		  this.textBox1,
																		  this.bStart});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Basik Input & Output";
			this.ResumeLayout(false);

		}
		#endregion

		static void Main() 
		{
			Application.Run(new Form1());			
		}
		public void AddToFile()
		{			
			FileInfo file1 = new FileInfo("Test.txt");
			StreamWriter strw = file1.AppendText();

			strw.WriteLine(textBox1.Text.ToString());
			//strw.WriteLine("");
			strw.Flush();
			strw.Close();
			
			StreamReader stR = new StreamReader(file1.OpenRead());
			listBox1.Items.Clear();
			while(stR.Peek() != -1)
				listBox1.Items.Add(stR.ReadLine());
			stR.Close();
		}

		private void bStart_Click(object sender, System.EventArgs e)
		{
			AddToFile();
		}

		private void Refresh_Click(object sender, System.EventArgs e)
		{
			FileInfo file_r = new FileInfo("Test.txt");
			StreamReader stR = new StreamReader(file_r.OpenRead());
			listBox1.Items.Clear();
			while(stR.Peek() != -1)
				listBox1.Items.Add(stR.ReadLine());
			stR.Close();		
		}
	}
}
