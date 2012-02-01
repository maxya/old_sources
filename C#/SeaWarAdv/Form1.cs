using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace SeaWarAdv
{
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem menuFile;
		private System.Windows.Forms.MenuItem menuFileExit;
		private System.ComponentModel.Container components = null;
		public Image Circle,Cross,Square,Logo,Pole,Tochka;
		
		public Form1()
		{
			//Load Images from files
			Circle	= Image.FromFile("Circle.bmp");
			Cross	= Image.FromFile("Cross.bmp");
			Square	= Image.FromFile("Kvadrat.bmp");
			Logo	= Image.FromFile("Logo.bmp");
			Pole	= Image.FromFile("Pole.bmp");
			Tochka	= Image.FromFile("Tochka.bmp");
			//End Loading Bitmaps
			
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
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.menuFile = new System.Windows.Forms.MenuItem();
			this.menuFileExit = new System.Windows.Forms.MenuItem();
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.menuFile});
			// 
			// menuFile
			// 
			this.menuFile.Index = 0;
			this.menuFile.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.menuFileExit});
			this.menuFile.Text = "File";
			// 
			// menuFileExit
			// 
			this.menuFileExit.Index = 0;
			this.menuFileExit.Text = "Exit";
			this.menuFileExit.Click += new System.EventHandler(this.menuFileExit_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(528, 325);
			this.MaximizeBox = false;
			this.Menu = this.mainMenu;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Sea War Advanced";

		}
		#endregion

		static void Main() 
		{				
			Ship Korabl	= new Ship();			
			Korabl.InitShip(10,10,4,1);
			Korabl.Rotate();				
			Console.WriteLine("Position {0} {1}, Size {2}, Direction {3}",Korabl.Xpos,Korabl.Ypos,
				Korabl.Size,Korabl.Direction);
			//MessageBox.Show(Korabl.Direction.ToString());
			//Application.Run(new Form1());			
		}

		protected override void OnPaint(PaintEventArgs pe)
		{
			Graphics g = pe.Graphics;			
			g.FillRectangle(new SolidBrush(Color.FromArgb(180, Color.White)), ClientRectangle);
			g.DrawImage(Pole,5,5,Pole.Width,Pole.Height);
			g.DrawImage(Circle,5,5,Circle.Width,Circle.Height);
			
		}
		private void menuFileExit_Click(object sender, System.EventArgs e)		
		{			
			Application.Exit();
		}
	}	
}
