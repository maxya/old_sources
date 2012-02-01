using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace XO
{
	public struct Ship
	{
		public int xpos;
		public int ypos;
		public int	Size;
		public byte	Dir;
		public int	Life;
		public bool	Alive;
	}
	public class Form1 : System.Windows.Forms.Form
	{
		
		public  Ship[] Korabl = new Ship[10];
		private const	int Psize = 10;
		private byte	xstart = 10, ystart = 10, nToWin = 3;
		private int		xCur,yCur;
		private int		sSize,sDir,sIndex;
		private int[,] Pole = new int[11,11];
		private Image Circle, Cross, EMPT;		
		private StatusBarPanel pnl1,pnl2,pnl3;
		private System.Windows.Forms.StatusBar statusBar;
		private System.Windows.Forms.Button NewGame;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.ComponentModel.Container components = null;

		public Form1()
		{
			Korabl[1].Size = 1;
			//Image Loading...			
			Circle	= Image.FromFile("Circle.bmp");
			Cross	= Image.FromFile("Cross.bmp");
			EMPT	= Image.FromFile("Empty.bmp");
			//Initializing DoubleBuffering Support 8)
			this.SetStyle(ControlStyles.UserPaint, true);
			this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
			this.SetStyle(ControlStyles.DoubleBuffer, true);

			InitializeComponent();
			InitPole();
			pnl3.Text = " (c)Nightmare 2002";
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
			this.statusBar = new System.Windows.Forms.StatusBar();
			this.pnl1 = new System.Windows.Forms.StatusBarPanel();
			this.pnl2 = new System.Windows.Forms.StatusBarPanel();
			this.pnl3 = new System.Windows.Forms.StatusBarPanel();
			this.NewGame = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.pnl1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl3)).BeginInit();
			this.SuspendLayout();
			// 
			// statusBar
			// 
			this.statusBar.Location = new System.Drawing.Point(0, 279);
			this.statusBar.Name = "statusBar";
			this.statusBar.Panels.AddRange(new System.Windows.Forms.StatusBarPanel[] {
																						 this.pnl1,
																						 this.pnl2,
																						 this.pnl3});
			this.statusBar.ShowPanels = true;
			this.statusBar.Size = new System.Drawing.Size(408, 22);
			this.statusBar.TabIndex = 0;
			this.statusBar.Text = "Infa";
			// 
			// NewGame
			// 
			this.NewGame.Location = new System.Drawing.Point(320, 16);
			this.NewGame.Name = "NewGame";
			this.NewGame.Size = new System.Drawing.Size(80, 32);
			this.NewGame.TabIndex = 1;
			this.NewGame.Text = "New Game";
			this.NewGame.Click += new System.EventHandler(this.NewGame_Click);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(304, 56);
			this.label1.Name = "label1";
			this.label1.TabIndex = 2;
			this.label1.Text = "label1";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(304, 80);
			this.label2.Name = "label2";
			this.label2.TabIndex = 2;
			this.label2.Text = "label2";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(304, 104);
			this.label3.Name = "label3";
			this.label3.TabIndex = 2;
			this.label3.Text = "label3";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(304, 128);
			this.label4.Name = "label4";
			this.label4.TabIndex = 5;
			this.label4.Text = "label4";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(304, 152);
			this.label5.Name = "label5";
			this.label5.TabIndex = 4;
			this.label5.Text = "label5";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(304, 176);
			this.label6.Name = "label6";
			this.label6.TabIndex = 3;
			this.label6.Text = "label6";
			// 
			// Form1
			// 
			this.AutoScale = false;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(408, 301);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.label4,
																		  this.label5,
																		  this.label6,
																		  this.label1,
																		  this.NewGame,
																		  this.statusBar,
																		  this.label2,
																		  this.label3});
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(416, 328);
			this.MinimumSize = new System.Drawing.Size(416, 328);
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Sea War Adv v1.0";
			((System.ComponentModel.ISupportInitialize)(this.pnl1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl3)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		// The main entry point for the application.
		static void Main() 
		{			
			Application.Run(new Form1());			
		}

		protected override void OnPaint(PaintEventArgs pe)
		{
			Graphics g = pe.Graphics;		
			
			for(int i=0;i<Psize;i++)
				for(int j=0; j<Psize;j++)				
					switch (Pole[i,j])
					{
						case 0:
						g.DrawImage(EMPT,(i*23)+xstart,(j*23)+ystart,EMPT.Width,EMPT.Height);
						break;
						case 1:
						g.DrawImage(Circle,(i*23)+xstart,(j*23)+ystart,Circle.Width,Circle.Height);
						break;
						case 2:
						g.DrawImage(Cross,(i*23)+xstart,(j*23)+ystart,Cross.Width,Cross.Height);
						break;
					}
		}
		protected override void OnMouseMove(MouseEventArgs me)
		{
			int xpos = me.X+xstart; xpos = xpos/23;
			int ypos = me.Y+ystart; ypos = ypos/23;
			if(xpos>0 && xpos<Psize+1)
				pnl1.Text = "x Coordinate " + xpos.ToString();
			else
				pnl1.Text = "Out of Field";
			if(ypos>0 && ypos<Psize+1)
				pnl2.Text = "y Coordinate " + ypos.ToString();
			else
				pnl2.Text = "Out of Field";
		}
		protected override void OnMouseDown(MouseEventArgs me)
		{
			xCur = me.X+xstart; xCur = xCur/23-1;
			yCur = me.Y+ystart; yCur = yCur/23-1;
			if(xCur>-1 && xCur<11 && yCur>-1 && yCur<11)
			{				
				switch(me.Button.ToString())
				{
					case "Left":
						Pole[xCur,yCur] = 1;					
						PutShip();
						break;
					case "Right":
						Pole[xCur,yCur] = 2;
						//if(sdir==0)
						//	{sdir=1;pnl3.Text = "Vertical";}
						//else
						//	{sdir=0;pnl3.Text = "Horizontal";}
						break;
					case "Middle":
						Pole[xCur,yCur] = 0;
						break;
				}
				Invalidate(); 				
			}
		}
		
		private void PutShip()
		{			
			for(int i=0;i<sSize;i++)
			{
				if(sDir == 0)
					Pole[xCur+i,yCur]=1;
				else
					Pole[xCur,yCur+i]=1;
			}
			Korabl[sIndex].xpos	= xCur;	
			Korabl[sIndex].ypos = yCur;	
			Korabl[sIndex].Size	= 4;	
			Korabl[sIndex].Dir	= 0;	
			Korabl[sIndex].Life	= 4;	
			Korabl[sIndex].Alive = true;
			StatShip();

		}
		private void InitPole()
		{
			sIndex = 0;sDir=0;sSize=4;
			for(int i=0; i<Psize+1; i++)			
				for(int j=0; j<Psize+1; j++)
				{Pole[i,j] = 0;}
			Invalidate();
		}
		private void StatShip()
		{
			label1.Text = "XPosition "+Korabl[sIndex].xpos.ToString();
			label2.Text = "YPosition "+Korabl[sIndex].ypos.ToString();
			label3.Text = "Size " + Korabl[sIndex].Size.ToString();
			label4.Text = "Direction "+Korabl[sIndex].Dir.ToString();
			label5.Text = "Life Points "+Korabl[sIndex].Life.ToString();
			label6.Text = "Still Alive "+ Korabl[sIndex].Life.ToString();
		}
		
		private void NewGame_Click(object sender, System.EventArgs e)
		{
			InitPole();
		}		
	}
}
