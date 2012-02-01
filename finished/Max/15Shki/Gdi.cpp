// Gdi.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "Gdi.h"

// Global Variables:
HINSTANCE	hInst;								// current instance
HBITMAP		bamps[16];
int			Pole[4][4];
int			Check[17];
bool wongame = false;
POINT Pos;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void StartUp();
void WinCheck();
void SwapNum(int xpos,int ypos);
void OnPaint(HDC hDC,int xpos,int ypos,int bmp);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	for(int i=0;i<16;i++)
	{
		bamps[i] = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_Bmp01+i));
	}
	
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_GDI;
	wcex.lpszClassName	= "Main";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);
	RegisterClassEx(&wcex);

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow("Main", "Pyatnashki 15", WS_OVERLAPPED | WS_SYSMENU |WS_MINIMIZEBOX| WS_CAPTION,
		CW_USEDEFAULT, 0, 256, 300, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//RECT rect;
	int num=0;

	switch (message) 
	{
	case WM_CREATE:
		StartUp();
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_FILE_NEW:			
			StartUp();
			WinCheck();
			if(wongame==true)
				StartUp();
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//GetClientRect(hWnd,&rect);		
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				OnPaint(hdc,j*64,i*64,Pole[i][j]);
		// TODO: Add any drawing code here...		
		EndPaint(hWnd, &ps);		
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd,&pt);
		SwapNum((int)pt.x/64,(int)pt.y/64);
		InvalidateRect(hWnd,NULL,FALSE);
		if(wongame == true)
			MessageBox(hWnd,"You Won The Game!","Congradulations !",NULL);
		break;
	case WM_WINDOWPOSCHANGED:
	//case WM_MOVE:
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void OnPaint(HDC hDC,int xpos,int ypos,int bmp)
{
	//RECT rcClipBox;
	//GetClipBox(hDC,&rcClipBox);	
	HDC memDC = CreateCompatibleDC(hDC);
	SelectObject(memDC,bamps[bmp-1]);
	BitBlt(hDC,xpos,ypos,64,64,memDC,0,0,SRCCOPY);
	DeleteDC(memDC);
}
void StartUp()
{
	//Standart feling pole with 1,2,3,4...
	int index = 1;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			Pole[i][j] = index;
			index++;
		}
	//Advanced felig pol e		
	int randomnum;
	int temp;
	while(1)
			{
				randomnum = rand();
				randomnum%=100;
				if(randomnum<=50)
					break;
			}		
	for (int num=0;num<randomnum;num++)
	{
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)				
			{
				temp = Pole[j][i];
				Pole[j][i] = Pole[j][i+1];
				Pole[j][i+1] = temp;				
					
			}
	}
}
void SwapNum(int xpos,int ypos)
{
	int temppos;
	bool swap = false;
	
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(Pole[i][j]== 16)
			{
                Pos.x=i;Pos.y=j;
			}
		}
//Check for infield, not nessesary, but...	
		if(xpos>=0 && xpos<4 && ypos>=0 && ypos <4)
		{
			if(xpos-1 == (int)Pos.y && ypos == (int)Pos.x)
				swap=true;
			if(xpos+1 == (int)Pos.y && ypos == (int)Pos.x)
				swap=true;
			if(ypos-1 == (int)Pos.x && xpos == (int)Pos.y)
				swap=true;
			if(ypos+1 == (int)Pos.x && xpos == (int)Pos.y)
				swap=true;
		}
//Swapping dots		
		if(swap == true)
		{
			temppos = Pole[ypos][xpos];
			Pole[ypos][xpos] = Pole[Pos.x][Pos.y];
			Pole[Pos.x][Pos.y] = temppos;
			Pos.x = ypos; Pos.y = xpos;
			//Beep(50,100);			
		}
//Checking! for wining game :)
		WinCheck();


}
void WinCheck()
{
		wongame = true;
		int chIndex =0;
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
			{
				Check[chIndex] = Pole[i][j];
				chIndex++;
			}
		for(int i =0;i<15;i++)
			if(Check[i+1]-Check[i] != 1)
				wongame = false;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
