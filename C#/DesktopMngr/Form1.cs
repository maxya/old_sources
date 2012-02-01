using System;
using System.Data;
using System.IO;
using System.Drawing;
using System.Collections;
//using System.ComponentModel;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace DesktopMngr
{
	public class Form1 : System.Windows.Forms.Form
	{
		#region Constants

		[DllImport("user32")]
		public static extern bool SystemParametersInfo( uint uiAction, uint uiParam, string pvParam, uint fWinIni);

		private string OFDFilter = "Bitmap Files(*.BMP)|*.BMP|All files (*.*)|*.*";
//"Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
		private int glTimerValue, glMaxTV;

		private System.ComponentModel.IContainer components;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private SaveFileDialog SFD = new SaveFileDialog();
		private string BackgrPath, FileName;
		private NotifyIcon notifyIcon1 = new NotifyIcon();
		private ContextMenu TrayMenu = new ContextMenu();
		private System.Windows.Forms.ListBox FileList;
		private System.Windows.Forms.Button SetWall;
		private System.Windows.Forms.NumericUpDown timeToChange;
		private System.Windows.Forms.RadioButton radioTile;
		private System.Windows.Forms.RadioButton radioCenter;
		private System.Windows.Forms.CheckBox checkStretch;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.StatusBar statusBar1;
		private System.Windows.Forms.CheckBox checkTimer;
		private System.Windows.Forms.Button RemoveWall;
		private System.Windows.Forms.Button bHide;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button SaveList;
		private System.Windows.Forms.Button ClearList;
		private System.Windows.Forms.Button AddWallButton;
		private System.Windows.Forms.GroupBox groupBox3;
		
		System.Timers.Timer aTimer = new System.Timers.Timer();	
		#endregion

		public Form1()
		{	
			InitializeComponent();			
			InitTray();
			GetRegData();
			LListOnInit();			
		}

		protected override void Dispose( bool disposing )
		{
			if( disposing )
				if (components != null) 
					components.Dispose();
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		
		private void InitializeComponent()
		{
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.AddWallButton = new System.Windows.Forms.Button();
			this.FileList = new System.Windows.Forms.ListBox();
			this.SetWall = new System.Windows.Forms.Button();
			this.timeToChange = new System.Windows.Forms.NumericUpDown();
			this.radioTile = new System.Windows.Forms.RadioButton();
			this.radioCenter = new System.Windows.Forms.RadioButton();
			this.checkStretch = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.statusBar1 = new System.Windows.Forms.StatusBar();
			this.checkTimer = new System.Windows.Forms.CheckBox();
			this.RemoveWall = new System.Windows.Forms.Button();
			this.bHide = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.SaveList = new System.Windows.Forms.Button();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.ClearList = new System.Windows.Forms.Button();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			((System.ComponentModel.ISupportInitialize)(this.timeToChange)).BeginInit();
			this.SuspendLayout();
			// 
			// openFileDialog
			// 
			this.openFileDialog.Multiselect = true;
			// 
			// AddWallButton
			// 
			this.AddWallButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.AddWallButton.Location = new System.Drawing.Point(520, 88);
			this.AddWallButton.Name = "AddWallButton";
			this.AddWallButton.Size = new System.Drawing.Size(80, 24);
			this.AddWallButton.TabIndex = 2;
			this.AddWallButton.Text = "Add";
			this.AddWallButton.Click += new System.EventHandler(this.AddWallButton_Click);
			// 
			// FileList
			// 
			this.FileList.HorizontalScrollbar = true;
			this.FileList.Location = new System.Drawing.Point(8, 48);
			this.FileList.Name = "FileList";
			this.FileList.Size = new System.Drawing.Size(376, 160);
			this.FileList.TabIndex = 7;
			this.FileList.UseTabStops = false;
			// 
			// SetWall
			// 
			this.SetWall.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.SetWall.Location = new System.Drawing.Point(480, 224);
			this.SetWall.Name = "SetWall";
			this.SetWall.Size = new System.Drawing.Size(136, 32);
			this.SetWall.TabIndex = 1;
			this.SetWall.Text = "Set Wallpaper";
			this.SetWall.Click += new System.EventHandler(this.SetWall_Click);
			// 
			// timeToChange
			// 
			this.timeToChange.Location = new System.Drawing.Point(96, 232);
			this.timeToChange.Name = "timeToChange";
			this.timeToChange.Size = new System.Drawing.Size(56, 20);
			this.timeToChange.TabIndex = 9;
			this.timeToChange.Value = new System.Decimal(new int[] {
																	   60,
																	   0,
																	   0,
																	   0});
			this.timeToChange.ValueChanged += new System.EventHandler(this.SetWall_Click);
			// 
			// radioTile
			// 
			this.radioTile.Location = new System.Drawing.Point(416, 80);
			this.radioTile.Name = "radioTile";
			this.radioTile.Size = new System.Drawing.Size(72, 16);
			this.radioTile.TabIndex = 10;
			this.radioTile.Text = "Tile";
			// 
			// radioCenter
			// 
			this.radioCenter.Checked = true;
			this.radioCenter.Location = new System.Drawing.Point(416, 104);
			this.radioCenter.Name = "radioCenter";
			this.radioCenter.Size = new System.Drawing.Size(72, 16);
			this.radioCenter.TabIndex = 10;
			this.radioCenter.TabStop = true;
			this.radioCenter.Text = "Center";
			// 
			// checkStretch
			// 
			this.checkStretch.Checked = true;
			this.checkStretch.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkStretch.Location = new System.Drawing.Point(416, 136);
			this.checkStretch.Name = "checkStretch";
			this.checkStretch.Size = new System.Drawing.Size(72, 16);
			this.checkStretch.TabIndex = 11;
			this.checkStretch.Text = "Stretch";
			// 
			// groupBox1
			// 
			this.groupBox1.Location = new System.Drawing.Point(400, 56);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(96, 112);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Style";
			// 
			// statusBar1
			// 
			this.statusBar1.Location = new System.Drawing.Point(0, 266);
			this.statusBar1.Name = "statusBar1";
			this.statusBar1.Size = new System.Drawing.Size(626, 22);
			this.statusBar1.TabIndex = 14;
			// 
			// checkTimer
			// 
			this.checkTimer.Checked = true;
			this.checkTimer.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkTimer.Location = new System.Drawing.Point(8, 232);
			this.checkTimer.Name = "checkTimer";
			this.checkTimer.Size = new System.Drawing.Size(80, 16);
			this.checkTimer.TabIndex = 15;
			this.checkTimer.Text = "Use Timer";
			this.checkTimer.CheckedChanged += new System.EventHandler(this.SetWall_Click);
			// 
			// RemoveWall
			// 
			this.RemoveWall.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.RemoveWall.Location = new System.Drawing.Point(520, 128);
			this.RemoveWall.Name = "RemoveWall";
			this.RemoveWall.Size = new System.Drawing.Size(80, 24);
			this.RemoveWall.TabIndex = 2;
			this.RemoveWall.Text = "Remove";
			this.RemoveWall.Click += new System.EventHandler(this.RemoveWall_Click);
			// 
			// bHide
			// 
			this.bHide.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.bHide.Location = new System.Drawing.Point(528, 8);
			this.bHide.Name = "bHide";
			this.bHide.Size = new System.Drawing.Size(88, 24);
			this.bHide.TabIndex = 8;
			this.bHide.Text = "HIDE";
			this.bHide.Click += new System.EventHandler(this.bHide_Click);
			// 
			// button2
			// 
			this.button2.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.button2.Location = new System.Drawing.Point(40, 16);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(72, 16);
			this.button2.TabIndex = 16;
			this.button2.Text = "Load";
			this.button2.Click += new System.EventHandler(this.LoadList_Click);
			// 
			// SaveList
			// 
			this.SaveList.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.SaveList.Location = new System.Drawing.Point(128, 16);
			this.SaveList.Name = "SaveList";
			this.SaveList.Size = new System.Drawing.Size(72, 16);
			this.SaveList.TabIndex = 16;
			this.SaveList.Text = "Save";
			this.SaveList.Click += new System.EventHandler(this.SaveList_Click);
			// 
			// groupBox2
			// 
			this.groupBox2.Location = new System.Drawing.Point(512, 56);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(96, 112);
			this.groupBox2.TabIndex = 17;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Wallpaper";
			// 
			// ClearList
			// 
			this.ClearList.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.ClearList.Location = new System.Drawing.Point(208, 16);
			this.ClearList.Name = "ClearList";
			this.ClearList.Size = new System.Drawing.Size(72, 16);
			this.ClearList.TabIndex = 16;
			this.ClearList.Text = "Clear";
			this.ClearList.Click += new System.EventHandler(this.ClearList_Click);
			// 
			// groupBox3
			// 
			this.groupBox3.Location = new System.Drawing.Point(8, 0);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(288, 40);
			this.groupBox3.TabIndex = 18;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "List";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(626, 288);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.button2,
																		  this.timeToChange,
																		  this.checkTimer,
																		  this.statusBar1,
																		  this.checkStretch,
																		  this.radioTile,
																		  this.SetWall,
																		  this.FileList,
																		  this.AddWallButton,
																		  this.radioCenter,
																		  this.groupBox1,
																		  this.RemoveWall,
																		  this.bHide,
																		  this.SaveList,
																		  this.groupBox2,
																		  this.ClearList,
																		  this.groupBox3});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Desktop Manager";
			this.Closed += new System.EventHandler(this.AppExit);
			((System.ComponentModel.ISupportInitialize)(this.timeToChange)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		static void Main() 
		{			
			Application.Run(new Form1());
		}

		private void LListOnInit()
		{
			FileList.Items.Clear();			
			FileStream fs = new FileStream("C:\\Program Files\\Desktop Manager\\deflist.dml", FileMode.Open,
				FileAccess.Read, FileShare.Read);
			if(fs.CanRead == true)
			{
				StreamReader sr = new StreamReader(fs);
				while(sr.Peek()>-1)
				{
					FileList.Items.Add(sr.ReadLine());
				}
				sr.Close();
				fs.Close();
				FileList.SelectedIndex = 0;
				//FileList.SelectedIndex = Random(FileList.Items.Count);
				//SetWallpaper();
			}
			this.Hide();
		}
		private void InitTray()
		{
			MenuItem exit = new MenuItem();
			MenuItem ops = new MenuItem();
			MenuItem tstart = new MenuItem();
			MenuItem tstop =new MenuItem();			
			exit.Text = "E&xit";
			ops.Text = "O&pen Main";
			tstart.Text = "Start Timer";
			tstop.Text = "Stop Timer";			
			TrayMenu.MenuItems.Add(ops);
			//TrayMenu.MenuItems.Add(tstart);
			//TrayMenu.MenuItems.Add(tstop);			
			TrayMenu.MenuItems.Add(exit);
			

			exit.Click  += new System.EventHandler(this.AppExit);
			ops.Click	+= new System.EventHandler(this.OpsClick);
			tstart.Click += new System.EventHandler(this.tStart);
			tstop.Click += new System.EventHandler(this.tStop);			
			
			notifyIcon1.Icon = new System.Drawing.Icon("ico.ico");
			notifyIcon1.Visible = true;
			notifyIcon1.Text = "Desktop Manager";
			//notifyIcon1.Click += new System.EventHandler(this.OpsClick);
			notifyIcon1.DoubleClick += new System.EventHandler(this.OpsClick);
			notifyIcon1.ContextMenu = TrayMenu;

			//Start Timer
			aTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimerEvent);			
			statusBar1.Text = "Init OK";			
		}
		
		private void bHide_Click(object sender, System.EventArgs e)
		{
			this.Hide();
		}
		

		private void AppExit(object sender, EventArgs e)
		{
			notifyIcon1.Visible = false;
			Application.Exit();
		}
		private void OpsClick(object sender, EventArgs e)
		{
			this.Show();
		}
		

#region Registry
		private void GetRegData()
		{
			RegistryKey BmpPath = Registry.CurrentUser;
			BmpPath = BmpPath.OpenSubKey("Control Panel\\Desktop\\");
			BackgrPath = BmpPath.GetValue("Wallpaper").ToString();
			BmpPath.Close();
		}
		private void SetRegData(string WName)
		{
			RegistryKey BmpPath = Registry.CurrentUser;
			BmpPath = BmpPath.OpenSubKey("Control Panel\\Desktop\\",true);
			object bmpName, Tile, Stretch;
			bmpName = WName;
			Tile = "0";
			Stretch = "0";
			
			if(radioTile.Checked == true)
				Tile = "1";
			if(radioCenter.Checked == true)
				Tile = "0";	
			if(checkStretch.Checked == true)
				Stretch = "2";
			
			BmpPath.SetValue("WallpaperStyle", Stretch);			
			BmpPath.SetValue("Wallpaper", bmpName);			
			BmpPath.SetValue("TileWallpaper", Tile);
			BmpPath.Close();
		}
		
#endregion
#region Timer
		public void InitTimer(double time)
		{
			if(aTimer.Enabled == true)
				aTimer.Enabled = false;
			aTimer.Interval = time*1000;
			if(checkTimer.Checked == true)
				aTimer.Enabled = true;
			glTimerValue = (int)time-1;
			glMaxTV = (int)time-1;
			
		}

		public void OnTimerEvent(object source, System.Timers.ElapsedEventArgs e)
		{
			string CurrItem;
			if(FileList.SelectedIndex == FileList.Items.Count-1)
				FileList.SelectedIndex = 0;
			else
				FileList.SelectedIndex++;
			CurrItem = FileList.SelectedItem.ToString();
			SetRegData(CurrItem);
			SystemParametersInfo(0x0014,0,CurrItem,0);
			statusBar1.Text = CurrItem;	
			glTimerValue = glMaxTV;
		}
		private void tStart(object sender, EventArgs e)
		{
			aTimer.Start();			

		}
		private void tStop(object sender, EventArgs e)
		{
			aTimer.Stop();			
		}
		
		private void onTickTimer(object sender, System.EventArgs e)
		{			
			glTimerValue--;			
		}		
#endregion
#region List
		private void SaveImgList()
		{
			SFD.DefaultExt = ".dml";
			SFD.Title = "Save your list file";
			SFD.Filter = "List Files(*.dml)|*.DML";

			if(SFD.ShowDialog() == DialogResult.OK)
			{
				FileStream fs = new FileStream(SFD.FileName,
					FileMode.Create, FileAccess.Write, FileShare.Write);
				StreamWriter sSattings = new StreamWriter(fs);
				for(int i = 0; i < FileList.Items.Count; i++)
				{
					sSattings.WriteLine(FileList.Items[i].ToString());
				}
				sSattings.Flush();
				sSattings.Close();
			}			
		}
		private void LoadList()
		{
			openFileDialog.Filter = "ListFiles(*.dml)|*.DML|All files (*.*)|*.*";
			if(openFileDialog.ShowDialog() == DialogResult.OK)
			{
				string InputName = openFileDialog.FileName;

				FileStream fs = new FileStream(InputName, FileMode.Open, FileAccess.Read, FileShare.Read);
				StreamReader rSatt = new StreamReader(fs);
				FileList.Items.Clear();
				while(rSatt.Peek()>-1)
				{
					FileList.Items.Add(rSatt.ReadLine());
				}
				rSatt.Close();
			}
		}
		private void SaveList_Click(object sender, System.EventArgs e)
		{
			SaveImgList();
		}

		private void LoadList_Click(object sender, System.EventArgs e)
		{			
			LoadList();			
		}

		private void ClearList_Click(object sender, System.EventArgs e)
		{
			aTimer.Stop();			
			FileList.Items.Clear();
		}
#endregion
#region Wallpaper

		private void AddWallButton_Click(object sender, System.EventArgs e)
		{			
			openFileDialog.Filter = OFDFilter;
			openFileDialog.ShowDialog();			
			if(openFileDialog.FileNames.Length != 0)
			{
				for(int i = 0; i<openFileDialog.FileNames.Length; i++)
				{
					FileName = openFileDialog.FileNames[i];					
					FileList.Items.Add(FileName);
					FileList.SelectedIndex = 0;
				}
			}
			else
				statusBar1.Text = "File wasn't selected";			
		}

		private void RemoveWall_Click(object sender, System.EventArgs e)
		{
			FileList.Items.Remove(FileList.SelectedItem);
			FileList.Invalidate();
		}

		private void SetWall_Click(object sender, System.EventArgs e)
		{
			SetWallpaper();		
		}
		private void SetWallpaper()
		{
			string CurrentItem;
			CurrentItem = FileList.SelectedItem.ToString();
			SetRegData(CurrentItem);
			SystemParametersInfo(0x0014,0,CurrentItem,0);
			statusBar1.Text = CurrentItem;
			InitTimer((double)timeToChange.Value);		
		}
		
		
#endregion		

		
		
		
		

		
	}
}