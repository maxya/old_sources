using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace PMan
{
	// Summary description for Form1.
	public class Form1 : System.Windows.Forms.Form
	{
		private Point position = new Point(1,1);
		private	Image pMan,gold,wall,steel,ground;
		private	int[,] Pole = new int[20,20];
		private int xCur,yCur,Index =0, pPosX = 1,pPosY =1;

		private System.Windows.Forms.StatusBar statusBar1;
		private System.Windows.Forms.StatusBarPanel pnl1;
		private System.Windows.Forms.StatusBarPanel pnl2;
		private System.Windows.Forms.StatusBarPanel pnl3;
		private System.Windows.Forms.StatusBarPanel pnl4;
		private System.Windows.Forms.StatusBarPanel pnl5;
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem File;
		private System.Windows.Forms.MenuItem File_Exit;
		private System.Windows.Forms.MenuItem Edit;
		private System.Windows.Forms.MenuItem Edit_Save;
		private System.Windows.Forms.MenuItem Edit_Load;
		private System.Windows.Forms.MenuItem File_New;
		private System.Windows.Forms.MenuItem Options;
		
		// Required designer variable.
		private System.ComponentModel.Container components = null;

		public Form1()
		{
			//Bitmap Load...
			pMan	= Image.FromFile("pman.png");
			gold	= Image.FromFile("gold32.bmp");
			wall	= Image.FromFile("wall32.bmp");
			steel	= Image.FromFile("steel32.bmp");
			ground	= Image.FromFile("ground32.bmp");

			//Settup DoubleBuffering for current Window
			this.SetStyle(ControlStyles.UserPaint,true);
			this.SetStyle(ControlStyles.AllPaintingInWmPaint,true);
			this.SetStyle(ControlStyles.DoubleBuffer,true);
			InitializeComponent();
			Init();
			// TODO: Add any constructor code after InitializeComponent call
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
			this.statusBar1 = new System.Windows.Forms.StatusBar();
			this.pnl1 = new System.Windows.Forms.StatusBarPanel();
			this.pnl2 = new System.Windows.Forms.StatusBarPanel();
			this.pnl3 = new System.Windows.Forms.StatusBarPanel();
			this.pnl4 = new System.Windows.Forms.StatusBarPanel();
			this.pnl5 = new System.Windows.Forms.StatusBarPanel();
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.File = new System.Windows.Forms.MenuItem();
			this.File_New = new System.Windows.Forms.MenuItem();
			this.File_Exit = new System.Windows.Forms.MenuItem();
			this.Edit = new System.Windows.Forms.MenuItem();
			this.Edit_Save = new System.Windows.Forms.MenuItem();
			this.Edit_Load = new System.Windows.Forms.MenuItem();
			this.Options = new System.Windows.Forms.MenuItem();
			((System.ComponentModel.ISupportInitialize)(this.pnl1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl4)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl5)).BeginInit();
			this.SuspendLayout();
			// 
			// statusBar1
			// 
			this.statusBar1.Location = new System.Drawing.Point(0, 359);
			this.statusBar1.Name = "statusBar1";
			this.statusBar1.Panels.AddRange(new System.Windows.Forms.StatusBarPanel[] {
																						  this.pnl1,
																						  this.pnl2,
																						  this.pnl3,
																						  this.pnl4,
																						  this.pnl5});
			this.statusBar1.ShowPanels = true;
			this.statusBar1.Size = new System.Drawing.Size(640, 22);
			this.statusBar1.TabIndex = 0;
			this.statusBar1.Text = "statusBar1";
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.File,
																					 this.Edit,
																					 this.Options});
			// 
			// File
			// 
			this.File.Index = 0;
			this.File.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				 this.File_New,
																				 this.File_Exit});
			this.File.Text = "File";
			// 
			// File_New
			// 
			this.File_New.Index = 0;
			this.File_New.Shortcut = System.Windows.Forms.Shortcut.CtrlN;
			this.File_New.Text = "New Game";
			this.File_New.Click += new System.EventHandler(this.File_New_Click);
			// 
			// File_Exit
			// 
			this.File_Exit.Index = 1;
			this.File_Exit.Shortcut = System.Windows.Forms.Shortcut.CtrlShiftQ;
			this.File_Exit.Text = "Exit";
			this.File_Exit.Click += new System.EventHandler(this.File_Exit_Click);
			// 
			// Edit
			// 
			this.Edit.Index = 1;
			this.Edit.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				 this.Edit_Save,
																				 this.Edit_Load});
			this.Edit.Text = "Edit";
			// 
			// Edit_Save
			// 
			this.Edit_Save.Index = 0;
			this.Edit_Save.Text = "Save Map...";
			this.Edit_Save.Click += new System.EventHandler(this.Edit_Save_Click);
			// 
			// Edit_Load
			// 
			this.Edit_Load.Index = 1;
			this.Edit_Load.Text = "Load Map...";
			this.Edit_Load.Click += new System.EventHandler(this.Edit_Load_Click);
			// 
			// Options
			// 
			this.Options.Index = 2;
			this.Options.Text = "Options";
			this.Options.Click += new System.EventHandler(this.Options_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(640, 401);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.statusBar1});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Menu = this.mainMenu;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Pack Man";
			((System.ComponentModel.ISupportInitialize)(this.pnl1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl4)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl5)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		static void Main() 
		{			
			Application.Run(new Form1());			
			
		}

		protected override void OnPaint(PaintEventArgs pe)
		{
			Graphics g = pe.Graphics;
			//g.DrawImage(pMan,100,100,pMan.Width,pMan.Height);			
			for(int i=0;i<20;i++)
				for(int j=0;j<12;j++)
					switch(Pole[i,j])
					{
						case 0:
							g.DrawImage(pMan,i*32,j*32,pMan.Width,pMan.Height);
							break;
						case 1:
							g.DrawImage(gold,i*32,j*32,gold.Width,gold.Height);
							break;
						case 2:
							g.DrawImage(wall,i*32,j*32,wall.Width,wall.Height);
							break;
						case 3:
							g.DrawImage(steel,i*32,j*32,steel.Width,steel.Height);
							break;
						case 4:
							g.DrawImage(ground,i*32,j*32,ground.Width,ground.Height);
							break;
					}
			g.DrawImage(pMan,pPosX*32,pPosY*32,pMan.Width,pMan.Height);
		}
		protected override void OnMouseMove(MouseEventArgs me)
		{
			xCur = me.X/32;
			yCur = me.Y/32;	
			//this.pnl1.Text = "X Position " + me.X.ToString();
			//this.pnl2.Text = "Y Position " + me.Y.ToString();
			this.pnl3.Text = "xCord " + xCur.ToString();
			this.pnl4.Text = "yCord " + yCur.ToString();
			xCur = me.X;
			yCur = me.Y;
			switch(Index)
			{
				case 0:
					pnl5.Text = "Pack Man bmp";
					break;
				case 1:
					pnl5.Text = "Gold bmp";
					break;
				case 2:
					pnl5.Text = "Wall bmp";
					break;
				case 3:
					pnl5.Text = "Steel bmp";
					break;
				case 4:
					pnl5.Text = "Ground bmp";
					break;
			}
			
		}
		protected override void OnMouseDown(MouseEventArgs me)
		{			
			xCur = me.X/32;
			yCur = me.Y/32;

			switch(me.Button)
			{
				case MouseButtons.Left:
					Pole[xCur,yCur] = Index;
					break;
				case MouseButtons.Right:
					if(Index<4)
						Index++;
					else
						Index=0;					
					break;				
			}
			Invalidate();
		}
		
		protected override void OnKeyPress(System.Windows.Forms.KeyPressEventArgs e)
		{
			switch((int)(byte)e.KeyChar)
			{
				case (int)Keys.Right:
					if(pPosX<19 && Pole[pPosX+1,pPosY] == 3)
						pPosX++;
					break;
			}
		}
//		protected override void OnKeyDown(KeyEventArgs ke)
//		{	
//			switch(ke.KeyCode)
//			{
//				case Keys.Right:
//				case Keys.D:
//					if(pPosX<19 && Pole[pPosX+1,pPosY] == 3)
//						pPosX++;
//					break;
//				case Keys.Left:
//				case Keys.A:
//					if(pPosX>0 && Pole[pPosX-1,pPosY] == 3)
//						pPosX--;
//					break;
//				case Keys.Down:
//				case Keys.S:
//					if(pPosY<11 && Pole[pPosX,pPosY+1] == 3)
//						pPosY++;
//					break;
//				case Keys.Up:
//				case Keys.W:
//					if(pPosY>0 && Pole[pPosX,pPosY-1] == 3)	
//						pPosY--;
//					break;
//			}
//			this.pnl1.Text = "PmanX " +(pPosX+1);
//			this.pnl2.Text = "PmanY " +(pPosY+1);
//			this.pnl5.Text = "Keycod "+ke.KeyValue.ToString();			
//			base.OnKeyDown(ke);
//			Invalidate();
//		}
		

		private void Init()
		{			
			pPosX = 1; pPosY =1;			
			for(int i=0;i<20;i++)
				for(int j=0;j<12;j++)
					Pole[i,j] = 3;
			this.pnl1.Text = "PmanX 1";this.pnl2.Text ="PmanY 1";
		}

		private void File_Exit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}
		private void File_New_Click(object sender, System.EventArgs e)
		{
			Init();
			Invalidate();
		}
		private void Options_Click(object sender, System.EventArgs e)
		{
            Options dlg = new Options();
			dlg.ShowDialog();
		}	
		private void Edit_Save_Click(object sender, System.EventArgs e)
		{
            string Stream = "";
			FileStream wfs = new FileStream("data.dat",FileMode.OpenOrCreate,
				FileAccess.Write);
			StreamWriter w = new StreamWriter(wfs);
			//w.WriteLine("New Writing OK");
			for(int i=0;i<12;i++)
				for(int j=0;j<20;j++)
				{
					Stream = Stream + Pole[j,i].ToString();					
				}
			w.WriteLine(Stream);
			w.Flush();
			w.Close();
			//MessageBox.Show(Stream,"Save Complete");
		}

		private void Edit_Load_Click(object sender, System.EventArgs e)
		{
			string readres = "";
			int tempint =0;
			string tempstring = "";

			FileStream rfs = new FileStream("data.dat",FileMode.Open,
				FileAccess.Read);
			StreamReader r = new StreamReader(rfs);			
			readres = r.ReadLine();
			for(int j=0;j<12;j++)
			for(int i=0;i<20;i++)
				//for(int j=0;j<20;j++)
					{
						tempstring = Convert.ToString(readres[i+j*20]);
						tempint	= Convert.ToInt32(tempstring);
						Pole[i,j] = tempint;
					}
			//MessageBox.Show(readres,"String");
			r.Close();
			pPosX = 1; pPosY = 1;
			Invalidate();
		}			
	}
}
