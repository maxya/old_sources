// Pman.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "Pman.h"

// Global Variables:
HINSTANCE hInst;								// current instance
HBITMAP  bmps[16];
int xpos=0,ypos=0,bmid =1;

void DrawBmp(HDC hDC, int xpos, int ypos,int nbmp);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	for(int i=0;i<6;i++)
	{
		bmps[i]=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BMP_1+i));
	}
	// TODO: Place code here.
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PMAN);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_PMAN;
	wcex.lpszClassName	= "Main";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	RegisterClassEx(&wcex);
	
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow("Main", "PackMan v 0.1", WS_OVERLAPPED |
		WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, 320, 240, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;
	if(!SetTimer(hWnd,1,200,NULL))
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
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
		//for(int i=0;i<10;i++)
		//	DrawBmp(hdc,i*32,0,i);
		DrawBmp(hdc,xpos*32,ypos*32,bmid);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:			
			if(bmid==4)
				bmid=0;
			else
				bmid++;
			InvalidateRect(hWnd,NULL,NULL);
		break;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void DrawBmp(HDC hDC, int xpos, int ypos,int nbmp)
{
	HDC memDC = CreateCompatibleDC(hDC);
	SelectObject(memDC,bmps[nbmp]);
	BitBlt(hDC,xpos,ypos,32,32,memDC,0,0,SRCCOPY);
	DeleteDC(memDC);	
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
