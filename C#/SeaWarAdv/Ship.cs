using System;

namespace SeaWarAdv
{	
	/// <summary>
	/// Summary description for Ship.
	/// </summary>
	public class Ship
	{
		private int xpos,ypos;
		public int Xpos
		{
			get{return xpos;}
			set{xpos = value;}
		}
		public int Ypos
		{
			get{return ypos;}
			set{ypos = value;}
		}

		private int size;
		public int Size
		{
			get{return size;}
			set{size = value;}
		}
		private int dir; // 1- vertical 0 - horisontal	
		public	int Direction
		{
			get{return dir;}
			set{dir = value;}
		}
		public Ship()
		{
			//
			// TODO: Add constructor logic here
			//
		}
		public void InitShip(int xpos, int ypos, int size,int dir)
		{
			this.xpos	= xpos;
			this.ypos	= ypos;
			this.size	= size;
			this.dir	= dir;
		}
		public void Rotate()
		{
			if(dir==1)
			{this.dir=0;}
			else
			{this.dir=1;}
		}
	}
}
