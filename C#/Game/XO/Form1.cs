using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace XO
{	
	public class Form1 : System.Windows.Forms.Form
	{
		
		private int Psize = 10;
		private byte	xstart = 10, ystart = 10, nToWin = 3;
		private int		xCur,yCur;
		private int[,] Pole = new int[11,11];
		private Image Circle, Cross, EMT;		
		private StatusBarPanel pnl1,pnl2,pnl3;
		private System.Windows.Forms.StatusBar statusBar;
		private System.Windows.Forms.Button NewGame;
		private System.Windows.Forms.ComboBox comboBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox checkBox1;
		private System.ComponentModel.Container components = null;

		public Form1()
		{
			//Image Loading...
			Circle	= Image.FromFile("Circle.bmp");
			Cross	= Image.FromFile("Cross.bmp");
			EMT		= Image.FromFile("Empty.bmp");
			this.SetStyle(ControlStyles.UserPaint, true);
			this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
			this.SetStyle(ControlStyles.DoubleBuffer, true);

			InitializeComponent();
			InitPole();
			pnl3.Text = " (c)Nightmare 2002";
			comboBox1.Items.Add("Eazy");
			comboBox1.Items.Add("Normal");
			comboBox1.Items.Add("Hard");

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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.statusBar = new System.Windows.Forms.StatusBar();
			this.pnl1 = new System.Windows.Forms.StatusBarPanel();
			this.pnl2 = new System.Windows.Forms.StatusBarPanel();
			this.pnl3 = new System.Windows.Forms.StatusBarPanel();
			this.NewGame = new System.Windows.Forms.Button();
			this.comboBox1 = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.checkBox1 = new System.Windows.Forms.CheckBox();
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
			// comboBox1
			// 
			this.comboBox1.Location = new System.Drawing.Point(320, 96);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new System.Drawing.Size(80, 21);
			this.comboBox1.TabIndex = 2;
			this.comboBox1.Text = "Hard";
			this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(304, 72);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(80, 16);
			this.label1.TabIndex = 3;
			this.label1.Text = "Select One :";
			// 
			// checkBox1
			// 
			this.checkBox1.Location = new System.Drawing.Point(312, 136);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new System.Drawing.Size(88, 24);
			this.checkBox1.TabIndex = 5;
			this.checkBox1.Text = "Wining Check";
			this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
			// 
			// Form1
			// 
			this.AutoScale = false;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(408, 301);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.checkBox1,
																		  this.label1,
																		  this.comboBox1,
																		  this.NewGame,
																		  this.statusBar});
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(416, 328);
			this.MinimumSize = new System.Drawing.Size(416, 328);
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Kross & Zero";
			((System.ComponentModel.ISupportInitialize)(this.pnl1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pnl3)).EndInit();
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
			
			for(int i=0;i<Psize;i++)
				for(int j=0; j<Psize;j++)				
					switch (Pole[i,j])
					{
						case 0:
						g.DrawImage(EMT,(i*23)+xstart,(j*23)+ystart,EMT.Width,EMT.Height);
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
			//pnl1.Text = me.X.ToString();
			//pnl2.Text = me.Y.ToString();
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
						break;
					case "Right":
						Pole[xCur,yCur] = 2;
						break;
					case "Middle":
						Pole[xCur,yCur] = 0;
						break;
				}
				Invalidate();
				if(checkBox1.Checked == true)
					WinCheck();
			}
		}
		private void InitPole()
		{
			for(int i=0; i<Psize+1; i++)			
				for(int j=0; j<Psize+1; j++)
				{Pole[i,j] = 0;}
			Invalidate();
		}

		private void WinCheck()
		{			
			byte chPass = 0;
			byte xmax  = 0, ymax = 0,diagmax = 0;			

			for(int i=0;i<Psize;i++)	//Horizontal Check
				if(Pole[i,yCur] == 1)
					{chPass++;if(chPass>xmax){xmax=chPass;}}
				else chPass=0;
			chPass =0;
			for(int i=0;i<Psize;i++)	//Vertical Check
				if(Pole[xCur,i] == 1)
				{chPass++;if(chPass>ymax){ymax=chPass;}}
				else chPass =0;
			chPass =0;
			//DiagonalWinCheck();

			if(xmax>=nToWin || ymax>=nToWin || diagmax>=nToWin)
			{MessageBox.Show("You Won", "8)"); InitPole();}
		}
		private void DiagonalWinCheck()
		{
			int newx = xCur,newy = yCur;
			bool uplch =true, dnrch =true, uprch =true,dnlch =true;
			int upleft=0, dnright=0, upright=0, dnleft =0;
            //check In Pole.. <^
			for(int i=0;i<nToWin;i++)
			{
				if(xCur-i > 1 && yCur-i > 1)
					upleft++;
				else
					uplch = false;					
				if(xCur+i < 10 && yCur+i < 10)
					dnright++;
				else
					dnrch =false;					
				if(xCur+i < 10 && yCur-i > 1)
					upright++;					
				else
					uprch = false;				
				if(xCur-i >1 && yCur+i<10)
					dnleft++;					
				else
					dnlch = false;
			}			
		}
		private void NewGame_Click(object sender, System.EventArgs e)
		{
			InitPole();
		}

		private void comboBox1_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			switch(comboBox1.SelectedIndex)
			{
				case 0:
					Psize = 4;
					break;
				case 1:
					Psize = 6;
					break;
				case 2:
					Psize = 10;
					break;
			}			
			for(int i=0;i<10;i++)
				for(int j=0;j<10;j++)
				{Pole[i,j] = 10;}
			InitPole();
		}

		private void checkBox1_CheckedChanged(object sender, System.EventArgs e)
		{
			InitPole();
			if(checkBox1.Checked == true)
				pnl3.Text = "Win Check ON";
			else
				pnl3.Text = "Win Check OFF";		
		}		
	}
}
