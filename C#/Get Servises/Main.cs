using System;
using System.ServiceProcess;
using System.IO;
class MainClass
{
	public static void Main(string[] args)
	{
		
		ServiceController [] controllers = ServiceController.GetDevices();
		int n = controllers.Length;
		if (args.Length == 0)
			Console.WriteLine("Use -h for help");
		switch(args.ToString())
		{
			case "-h":
				Console.WriteLine("Get Servises Version 1.0");
				Console.WriteLine("");
				Console.WriteLine("");
				Console.WriteLine("Use parameters: ");
				Console.WriteLine(" -h help, -s write to screen, -f write to file");
				Console.WriteLine("");
				break;
			case "s":
				for(int i=0; i<n; i++)
				{
					Console.WriteLine(controllers[i].DisplayName);
				}
				break;
			case "-f":
				break;

		}
		
	}
}