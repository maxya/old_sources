// Lab 4.2.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "Lab 4.2.h"
#include "data.h"
//#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
char TempString[32] = "";
Data Base[50];
//int  DataIndex = 0;
int  DataIndex;
int TempIndex;
LPDWORD FWBytes;
// Forward declarations of functions included in this code module:
LRESULT CALLBACK	MainProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	NewProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ViewProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	AboutProc(HWND, UINT, WPARAM, LPARAM);
void SaveFile();
void LoadFile();
void SortData(int Index);
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	HWND hWnd;
	MSG msg;

	hInst = hInstance; // Store instance handle in our global variable     
	hWnd = CreateDialog(hInst,MAKEINTRESOURCE(IDD_MAIN),NULL,(DLGPROC)MainProc);   
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}



LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
	case WM_INITDIALOG:		
		LoadFile();
		DataIndex = (int)Base[0].GrobalIndex;
		SetDlgItemText(hWnd,IDC_VERSION,"Version 0.50");
		PostMessage(hWnd,WM_ENABLE,TRUE,0);
		return TRUE;
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
			{				
			case IDC_NEW:
				DialogBox(hInst,(LPSTR)IDD_NEW,hWnd,(DLGPROC)NewProc);
				return TRUE;
				break;
			case IDC_VIEW:
				DialogBox(hInst,(LPSTR)IDD_VIEW,hWnd,(DLGPROC)ViewProc);
				return TRUE;
				break;
			case IDM_EDIT_SORTDATA:
				SortData(DataIndex);
				return TRUE;
				break;
			case IDM_HELP_ABOUT:
				DialogBox(hInst,(LPSTR)IDD_ABOUT,hWnd,(DLGPROC)AboutProc);
				return TRUE;
				break;
			case IDM_FILE_EXIT:
			case IDOK:				
				EndDialog(hWnd,	LOWORD(wParam));
				PostQuitMessage(0);
				return TRUE;
				break;		
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}		
		break;		
	}
	return FALSE;
}


LRESULT CALLBACK NewProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
	case WM_INITDIALOG:		
		PostMessage(hWnd,WM_ENABLE,TRUE,0);		
		return TRUE;

	case WM_COMMAND:		
		switch (LOWORD(wParam))
			{
			case IDOK:				
				DataIndex++;
				GetDlgItemText(hWnd,IDC_NEW_AUTHOR,TempString,32);				
                memcpy(Base[DataIndex].BookAuthor, TempString,32);				

				GetDlgItemText(hWnd,IDC_NEW_NAME,TempString,32);				
				memcpy(Base[DataIndex].BookName, TempString,32);

				GetDlgItemText(hWnd,IDC_NEW_NUM,TempString,32);				
				memcpy(Base[DataIndex].BookNum, TempString,32);

				GetDlgItemText(hWnd,IDC_NEW_INDEX,TempString,32);				
				memcpy(Base[DataIndex].BookIndex, TempString,32);
				Base[0].GrobalIndex = DataIndex;
				SaveFile();
				EndDialog(hWnd, LOWORD(wParam));
				
				return TRUE;
				break;
			case IDCANCEL:
				EndDialog(hWnd, LOWORD(wParam));				
				return TRUE;
				break;
			}		
		break;		
	}
	return FALSE;
}

LRESULT CALLBACK ViewProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
	case WM_INITDIALOG:		
		TempIndex = 1;
		SetDlgItemText(hWnd,IDC_VIEW_AUTHOR,(LPSTR)Base[TempIndex].BookAuthor);
		SetDlgItemText(hWnd,IDC_VIEW_NAME,(LPSTR)Base[TempIndex].BookName);
		SetDlgItemText(hWnd,IDC_VIEW_NUM,(LPSTR)Base[TempIndex].BookNum);
		SetDlgItemText(hWnd,IDC_VIEW_INDEX,(LPSTR)Base[TempIndex].BookIndex);		
		PostMessage(hWnd,WM_ENABLE,TRUE,0);		
		return TRUE;

	case WM_COMMAND:		
		switch (LOWORD(wParam))
			{
			case IDOK:					
				EndDialog(hWnd, LOWORD(wParam));				
				return TRUE;
				break;
			case IDC_PREV:
				if(TempIndex > 1)				
				{	TempIndex--;
					SetDlgItemText(hWnd,IDC_VIEW_AUTHOR,(LPSTR)Base[TempIndex].BookAuthor);
					SetDlgItemText(hWnd,IDC_VIEW_NAME,(LPSTR)Base[TempIndex].BookName);
					SetDlgItemText(hWnd,IDC_VIEW_NUM,(LPSTR)Base[TempIndex].BookNum);
					SetDlgItemText(hWnd,IDC_VIEW_INDEX,(LPSTR)Base[TempIndex].BookIndex);	
				};
				return TRUE;
				break;
			case IDC_NEXT:
				if(TempIndex < DataIndex )				
				{	TempIndex++;
					SetDlgItemText(hWnd,IDC_VIEW_AUTHOR,(LPSTR)Base[TempIndex].BookAuthor);
					SetDlgItemText(hWnd,IDC_VIEW_NAME,(LPSTR)Base[TempIndex].BookName);
					SetDlgItemText(hWnd,IDC_VIEW_NUM,(LPSTR)Base[TempIndex].BookNum);
					SetDlgItemText(hWnd,IDC_VIEW_INDEX,(LPSTR)Base[TempIndex].BookIndex);
				};
				return TRUE;
				break;			
			}		
		break;		
	}
	return FALSE;
}
LRESULT CALLBACK	AboutProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{case IDOK: EndDialog(hWnd,LOWORD(wParam));return TRUE;}
	}
	return FALSE;
}
void SaveFile()
{
	DWORD NumWritten;	
	HANDLE hFile = CreateFile("Data.dat",GENERIC_WRITE,
		0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);	
	WriteFile(hFile,&Base,sizeof(Base),&NumWritten,NULL);		
	CloseHandle(hFile);		
}
void LoadFile()
{
	DWORD NumRead;
	HANDLE hFile = CreateFile("Data.dat",GENERIC_READ,
		0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	ReadFile(hFile,&Base,sizeof(Base),&NumRead,NULL);
	CloseHandle(hFile);

}
void SortData(int Index)
{
	//Sort by Author//
	//char Temp[32];
	for(int i=1; i< Index; i++)
	{
		if(Base[i].BookAuthor < Base[i+1].BookAuthor)
		{			
			//memcpy(Temp,Base[i],32);
			//memcpy(Base[i],Base[i+1],32);
			//memcpy(Base[i+1],Temp,32);
		}
	}
	
}