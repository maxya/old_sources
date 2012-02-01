using System;
using System.Drawing;
//using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace ImageViewer
{
	public class Form1 : System.Windows.Forms.Form
	{		
		public	string	name;
		public	Image	img, newBitmap;
		public	bool	Resized		= false;
		public	bool	test		= true;
		private System.Windows.Forms.StatusBar statusbar;
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem File;
		private System.Windows.Forms.MenuItem Exit;
		private System.Windows.Forms.MenuItem Open;
		private System.Windows.Forms.MenuItem View;
		private System.Windows.Forms.MenuItem Fit;
		private System.Windows.Forms.MenuItem Original;
		private System.Windows.Forms.Label label;
		private System.ComponentModel.IContainer components;

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
			this.statusbar = new System.Windows.Forms.StatusBar();
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.File = new System.Windows.Forms.MenuItem();
			this.Open = new System.Windows.Forms.MenuItem();
			this.Exit = new System.Windows.Forms.MenuItem();
			this.View = new System.Windows.Forms.MenuItem();
			this.Fit = new System.Windows.Forms.MenuItem();
			this.Original = new System.Windows.Forms.MenuItem();
			this.label = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// statusbar
			// 
			this.statusbar.Location = new System.Drawing.Point(0, 419);
			this.statusbar.Name = "statusbar";
			this.statusbar.Size = new System.Drawing.Size(634, 16);
			this.statusbar.TabIndex = 3;
			this.statusbar.Text = "Info";
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.File,
																					 this.View});
			// 
			// File
			// 
			this.File.Index = 0;
			this.File.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				 this.Open,
																				 this.Exit});
			this.File.Text = "File";
			// 
			// Open
			// 
			this.Open.Index = 0;
			this.Open.Text = "Open Image...";
			this.Open.Click += new System.EventHandler(this.Open_Click);
			// 
			// Exit
			// 
			this.Exit.Index = 1;
			this.Exit.Text = "Exit";
			this.Exit.Click += new System.EventHandler(this.Exit_Click);
			// 
			// View
			// 
			this.View.Index = 1;
			this.View.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				 this.Fit,
																				 this.Original});
			this.View.Text = "View";
			// 
			// Fit
			// 
			this.Fit.Index = 0;
			this.Fit.Text = "Fit to Window(With Deformation)";
			// 
			// Original
			// 
			this.Original.Index = 1;
			this.Original.Text = "Original Size";
			// 
			// label
			// 
			this.label.BackColor = System.Drawing.SystemColors.HighlightText;
			this.label.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.label.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
			this.label.Location = new System.Drawing.Point(32, 24);
			this.label.Name = "label";
			this.label.Size = new System.Drawing.Size(312, 368);
			this.label.TabIndex = 4;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(634, 435);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.label,
																		  this.statusbar});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Menu = this.mainMenu;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Image Viewer";
			this.ResumeLayout(false);

		}
		#endregion

		static void Main() 
		{			
			Application.Run(new Form1());
		}


		protected override void OnPaint(PaintEventArgs pe)
		{
			
//			if(img != null)
//			{
//				Graphics g = pe.Graphics;
//				if(!Resized)
//					g.DrawImage(img,AutoScrollPosition.X,AutoScrollPosition.Y,
//						img.Width,img.Height);
//				else
//					g.DrawImage(img,ClientRectangle);
//				statusbar.Text = name;				
//			}
//			if(img !=null)
//			{
//				Graphics lgr = label.CreateGraphics();
//				lgr.DrawImage(img,0,0,img.Width,img.Height);				
//			}
		}		

		private void Open_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog	fd	=	new OpenFileDialog();
			fd.Title			=	"Open File..";
			fd.Filter	=	"Image Files (*.bmp;*.jpg;*.gif;*.tiff)|" +
				"*.jpg;*.jpeg;*.bmp;*.gif;*.tif;*.tiff;*.png|" +
				"All Files (*.*)|*.*";				
			
			if(fd.ShowDialog() == DialogResult.OK)
			{					
				img = Image.FromFile(fd.FileName);
				name = fd.FileName;				
				//aditional bitmap Drawning... none yet				
				label.Image = img;
			}
			
			//Invalidate(true);
		}

		private void Exit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}
	}
}
