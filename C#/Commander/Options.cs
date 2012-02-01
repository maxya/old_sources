using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Commander
{
	// Summary description for Options.
	public class Options : System.Windows.Forms.Form
	{
		// Required designer variable.
		private System.ComponentModel.Container components = null;

		public Options()
		{
			// Required for Windows Form Designer support
			InitializeComponent();

			// TODO: Add any constructor code after InitializeComponent call
		}

		// Clean up any resources being used.
		protected override void Dispose( bool disposing )
		{
			if( disposing )
				if(components != null)
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
			// 
			// Options
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(352, 173);
			this.MaximizeBox = false;
			this.Name = "Options";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Options";

		}
		#endregion
	}
}
