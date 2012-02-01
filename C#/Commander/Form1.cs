using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

namespace Commander
{	
	public class Form : System.Windows.Forms.Form
	{
		public	string CurDir = "D:\\";
		public	int	dirnum	= 0;
		public	string CurItem	= "";
		private System.Windows.Forms.ListBox LPanelLB;
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem File;
		private System.Windows.Forms.MenuItem FileExit;
		private System.Windows.Forms.MenuItem Options;
		private System.Windows.Forms.MenuItem Options_Opt;
		private System.ComponentModel.IContainer components;

		public Form()
		{
			// Required for Windows Form Designer support
			InitializeComponent();		
			GetItemList();

			// TODO: Add any constructor code after InitializeComponent call
		}
		// Clean up any resources being used.
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
			this.LPanelLB = new System.Windows.Forms.ListBox();
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.File = new System.Windows.Forms.MenuItem();
			this.FileExit = new System.Windows.Forms.MenuItem();
			this.Options = new System.Windows.Forms.MenuItem();
			this.Options_Opt = new System.Windows.Forms.MenuItem();
			this.SuspendLayout();
			// 
			// LPanelLB
			// 
			this.LPanelLB.Location = new System.Drawing.Point(8, 8);
			this.LPanelLB.Name = "LPanelLB";
			this.LPanelLB.Size = new System.Drawing.Size(200, 303);
			this.LPanelLB.TabIndex = 0;
			this.LPanelLB.SelectedIndexChanged += new System.EventHandler(this.LPanelLB_SelectedIndexChanged);
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.File,
																					 this.Options});
			// 
			// File
			// 
			this.File.Index = 0;
			this.File.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				 this.FileExit});
			this.File.Text = "File";
			// 
			// FileExit
			// 
			this.FileExit.Index = 0;
			this.FileExit.Text = "Exit";
			this.FileExit.Click += new System.EventHandler(this.FileExit_Click);
			// 
			// Options
			// 
			this.Options.Index = 1;
			this.Options.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					this.Options_Opt});
			this.Options.Text = "Options";
			// 
			// Options_Opt
			// 
			this.Options_Opt.Index = 0;
			this.Options_Opt.Text = "Options";
			this.Options_Opt.Click += new System.EventHandler(this.Options_Opt_Click);
			// 
			// Form
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(552, 333);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.LPanelLB});
			this.MaximizeBox = false;
			this.Menu = this.mainMenu;
			this.Name = "Form";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Windows Commander";
			this.ResumeLayout(false);

		}
		#endregion
		
		static void Main() 
		{
			Application.Run(new Form());
		}
		//Menu Parising
		private void FileExit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}
		private void Options_Opt_Click(object sender, System.EventArgs e)
		{
			Options dlg = new Options();
			dlg.ShowDialog();
		
		}		
		private void GetItemList()
		{			
            LPanelLB.Items.Clear();					
			LPanelLB.Items.Add("up");			
			DirectoryInfo Dinf = new DirectoryInfo(CurDir);//("D:\\");
			DirectoryInfo[] dirs = Dinf.GetDirectories();			
			foreach(DirectoryInfo dir in dirs)
			{
				LPanelLB.Items.Add(dir);
				dirnum++;
			}
			FileInfo[] files = Dinf.GetFiles();
			foreach(FileInfo file in files)
			{
				LPanelLB.Items.Add(file);
			}
		}

		private void LPanelLB_SelectedIndexChanged(object sender, System.EventArgs e)
		{			
			
			if(LPanelLB.SelectedIndex > dirnum)			
				MessageBox.Show("File");			
			else 
			if(LPanelLB.SelectedIndex == 0)
			{
				if(CurDir.Length > 4)
				CurDir = CurDir.Remove(CurDir.Length-CurItem.Length-1,CurItem.Length);
			}
			else
			{
				CurItem = LPanelLB.SelectedItem.ToString();
				CurDir = CurDir+(CurItem+"\\");
			}
			dirnum=0;
			GetItemList();
		}

		
	
		
	
	}
}
