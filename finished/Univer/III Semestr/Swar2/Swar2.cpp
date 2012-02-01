/////////////////////////// Sea War v 2.25//////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#define MAX_LOADSTRING 100
#define CELL_SIZE		23
// Глобальные Переменные :
HINSTANCE hInst;								// Current Instance
TCHAR szWindowClass[MAX_LOADSTRING];			// Имя класса Главного Окна
HBITMAP mphBitmap[10];							// Массив Битмапов
POINT CellNum;									// Номер Клетки
BOOL NewGame    = FALSE;							// Флаг "начата ли игра"
BOOL PInitDone  = FALSE;						// Флаг "Завершения ин. игрока"
BOOL AIInitDone = FALSE;						// Флаг "Завершения ин. компа"
BOOL AllDone	= FALSE;						//Полное завершение инита.
BOOL Engaged	= FALSE;						//Занята ли клетка
BOOL PTurn		= TRUE;							//Ход игрока
int Direction	= 0;							//Направление корабля
int Size		= 4;							// Размер корабля
int ShipNum		= 0;							//Кол-во Кораблей
int AIShipNum   = 0;							//Кол-во Кораблей противника
int PPole    [12][12];							//Масив поля игрока	
int AIPole   [12][12];							//Массив поля компа

// Описания Функций..
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void DrawPole(HWND hWnd,int Bitmap,int xPoz,int yPoz,int XSize,int YSize);
void DrawShip(HWND hWnd,int ShipID,int xcord, int ycord);
void HitTest(int Cellx,int Celly);
void AIHit();
void ResetGame();
void InitPole(BOOL InitAll);
void InitShip(int Cellx, int Celly);
void InitAIShip(int Cellx, int Celly);

//WinMain :)
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{ 	
	MSG msg;	
	HACCEL hAccelTable;	
	// Загрузка Строк
	LoadString(hInstance, IDC_SWAR2, szWindowClass, MAX_LOADSTRING);	
	MyRegisterClass(hInstance);	
	for (int i = 0; i <7; i++) //Загрузка Битмэпов 
	{
		mphBitmap[i] = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_Pole+i));		
	}
	InitPole(TRUE);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SWAR2);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SWAR2);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_SWAR2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   
   hInst = hInstance; // Store instance handle in our global variable
   hWnd = CreateWindow(szWindowClass, "Sea War v2.26", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 535, 400, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);   
   UpdateWindow(hWnd);
   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hDC;
	PAINTSTRUCT ps;
	
	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Меню
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_NEWGAME:
			if(NewGame == TRUE)
				{// Если повторно выбрана новая игра - сброс всех переменных.
					void ResetGame();					
				}
			else
				NewGame = TRUE;			
			InvalidateRect (hWnd, NULL, TRUE) ;			
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:				
		hDC = BeginPaint(hWnd, &ps);
		if (NewGame == FALSE){DrawPole(hWnd,5,0,0,535,429);EndPaint(hWnd, &ps);break;}	
		DrawPole(hWnd,0,23,23,238,238);
		DrawPole(hWnd,0,276,23,238,238);		
		for (int i=1;i<11;i++)//12
			{for(int j=1; j<11; j++)
			{
				if(PPole[i][j] == 1)
					{DrawShip(hWnd,3,i*23,j*23);}
				if(PPole[i][j] == 2)
					{DrawShip(hWnd,4,i*23,j*23);}
				if(PPole[i][j] == 4)
					{DrawShip(hWnd,1,i*23,j*23);}
				if(PPole[i][j] == 5)
					{DrawShip(hWnd,2,i*23,j*23);}				
				//if(AIPole[i][j] == 1)//Draw AI ships
				//	{DrawShip(hWnd,3,i*23+253,j*23);}
				if(AIPole[i][j] == 2)//Draw Missed
					{DrawShip(hWnd,4,i*23+253,j*23);}
				if(AIPole[i][j] == 4)// Ranev
					{DrawShip(hWnd,1,i*23+253,j*23);}
				if(AIPole[i][j] == 5)// Dead
					{DrawShip(hWnd,2,i*23+253,j*23);}	
			}
			}
		EndPaint(hWnd, &ps);						
		break;
	case WM_LBUTTONDOWN:
		{
			if(NewGame == FALSE){break;}//Проверка: Начата ли игра...
			POINT pt;
			GetCursorPos (&pt);
			ScreenToClient (hWnd, &pt);			
			if(AllDone == TRUE)
				{
					if(AIShipNum == 0)
						{
						MessageBox(hWnd,"Вы Выиграли !","Поздравляю :)", NULL );ResetGame();
						break;
						}
					if(ShipNum == 0)
						{
						MessageBox(hWnd,"Вы Проиграли !","Поздравляю :)", NULL );ResetGame();
						break;
						}
					CellNum.x	= ((int)pt.x-253)/23; //Определение номера клетки X
					CellNum.y	= ((int)pt.y)/23;//... Y				
					HitTest(CellNum.x,CellNum.y);
					AIHit();
				}
			else
				{					
					if(PInitDone != TRUE)//Проверка завершения Иницализации Кораблей		
						{
							CellNum.x	= ((int)pt.x)/23; //Определение номера клетки X
							CellNum.y	= ((int)pt.y)/23;//... Y				
							InitShip(CellNum.x,CellNum.y);
							InvalidateRect (hWnd, NULL, TRUE) ;				
						}
					else
						{
						if(AIInitDone != TRUE)
							{
								do{
									int x1=rand(); int y1=rand();
									x1%=10; y1%=10;
									InitAIShip(x1,y1);
									}
								while(AIShipNum<20);
							}			
						MessageBeep(1);						
						}
				}
			InvalidateRect(hWnd,NULL,TRUE);
          return 0;
		}
	
	case WM_RBUTTONDOWN:
		{  //Изменение положений корабля : Горизонтальное - Вертикальное
          if(Direction == 1)
			  {Direction = 0;}
		  else {Direction = 1;}
			InvalidateRect (hWnd, NULL, FALSE) ;
          return 0 ;
		}
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void DrawPole(HWND hWnd,int Bitmap,int xPoz,int yPoz,int XSize, int YSize)
{
	HDC hDC = GetDC (hWnd);
	HDC hSrc = CreateCompatibleDC(hDC);
	SelectObject (hSrc, mphBitmap[Bitmap]);
	BitBlt (hDC, xPoz, yPoz, XSize, YSize, hSrc, 0, 0, SRCCOPY);	
	ValidateRect (hWnd, NULL);
	DeleteDC (hSrc);
	ReleaseDC (hWnd, hDC);
	ValidateRect(hWnd, NULL);
}
void DrawShip(HWND hWnd,int ShipID,int xcord, int ycord)
{
		HDC hDC = GetDC (hWnd);
		HDC hSrc = CreateCompatibleDC(hDC);
		SelectObject (hSrc, mphBitmap[ShipID]);
		BitBlt (hDC, xcord, ycord, 23, 23, hSrc, 0, 0, SRCCOPY);	
		ValidateRect (hWnd, NULL);
		DeleteDC (hSrc);
		ReleaseDC (hWnd, hDC);
		ValidateRect(hWnd, NULL);
}


void InitPole(BOOL InitAll)
	{
		//Иницализация поля игрока
	for(int i = 1 ; i < 11; i++)
		{for (int j=1; j < 11; j++)
		{
		if(InitAll != FALSE)
			{PPole[i][j] = 0;}
			//Заполняю границы поля...
			PPole[i][0] = 6;
			PPole[i][11] = 6;
			PPole[0][i] = 6;
			PPole[11][i] = 6;

		}
		}
	// Иницализация поля компа
	for(int i = 1 ; i < 11; i++)
		{for (int j=1; j < 11; j++)
		{
			if(InitAll != FALSE)
				{AIPole[i][j] = 0;}
			//Заполняю границы поля...
			AIPole[i][0] = 6;
			AIPole[i][11] = 6;
			AIPole[0][i] = 6;
			AIPole[11][i] = 6;

		}
		}
	}
void InitShip(int Cellx, int Celly)
	{		
	if(ShipNum != 20)
		{	
		switch(ShipNum)
			{			
			  case 4:  Size = 3; break;
			  case 10: Size = 2; break;
			  case 16: Size = 1; break;
			}
			if(Direction == 0 )
			{			
				for(int i = Cellx; i< Cellx + Size; i++)
					{
					if(PPole[i][Celly] == 0)
						{
							Engaged = FALSE;
						}
					else 
						{
							Engaged = TRUE;
							break;
						}
					}
				if(Engaged == FALSE)//Ставлю Корабль на поле и заполняю соседн клетки
					{					
						for(int j = Cellx; j< Cellx + Size; j++)
						{	
							ShipNum++;
							PPole[j][Celly] = 1;
							PPole[j][Celly+1] = 3;
							PPole[j][Celly-1] = 3;
							if(j == Cellx)
								{
									PPole[j-1][Celly] = 3;
									PPole[j-1][Celly+1] = 3;
									PPole[j-1][Celly-1] = 3;
								}
							if(j == Cellx + Size-1)
								{
									PPole[j+1][Celly+1] = 3;
									PPole[j+1][Celly] = 3;
									PPole[j+1][Celly-1] = 3;
								}
						}						
					}		
			}
		else
			{
				for(int i = Celly; i<Celly + Size; i++)
					{
						if(PPole[Cellx][i] == 0)
							{
								Engaged = FALSE;
							}
						else
							{
								Engaged = TRUE;
								break;
							}
					}
				if(Engaged == FALSE)
					{
						for(int j = Celly; j< Celly + Size; j++)
							{
								ShipNum++;
								PPole[Cellx][j] = 1;
								PPole[Cellx+1][j] = 3;
								PPole[Cellx-1][j] = 3;
								if(j == Celly)
									{
										PPole[Cellx][j-1] = 3;
										PPole[Cellx+1][j-1] = 3;
										PPole[Cellx-1][j-1] = 3;
										
									}
								if(j == Celly + Size -1)
									{
										PPole[Cellx][j+1] = 3;
										PPole[Cellx+1][j+1] = 3;
										PPole[Cellx-1][j+1] = 3;
									}
							}
					}
			}
	}
	else 
	{PInitDone = TRUE; Size = 4;}
	}
void InitAIShip(int Cellx, int Celly)
{		
	if(AIShipNum != 20)
		{	
		switch(AIShipNum)
			{			
			  case 4:  Size = 3; break;
			  case 10: Size = 2; break;
			  case 16: Size = 1; break;
			}
			if(Direction == 0 )
			{			
				for(int i = Cellx; i< Cellx + Size; i++)
					{
					if(AIPole[i][Celly] == 0)
						{Engaged = FALSE;}
					else 
						{Engaged = TRUE;break;}
					}
				if(Engaged == FALSE)//Ставлю Корабль на поле и заполняю соседн клетки
					{					
						for(int j = Cellx; j< Cellx + Size; j++)
						{	
							AIShipNum++;
							AIPole[j][Celly] = 1;
							AIPole[j][Celly+1] = 3;
							AIPole[j][Celly-1] = 3;
							if(j == Cellx)
								{
									AIPole[j-1][Celly] = 3;
									AIPole[j-1][Celly+1] = 3;
									AIPole[j-1][Celly-1] = 3;
								}
							if(j == Cellx + Size-1)
								{
									AIPole[j+1][Celly+1] = 3;
									AIPole[j+1][Celly] = 3;
									AIPole[j+1][Celly-1] = 3;
								}
						}						
					}		
			}
		else
			{
				for(int i = Celly; i<Celly + Size; i++)
					{
						if(AIPole[Cellx][i] == 0)
							{Engaged = FALSE;}
						else
							{Engaged = TRUE; break;}
					}
				if(Engaged == FALSE)
					{
						for(int j = Celly; j< Celly + Size; j++)
							{
								AIShipNum++;
								AIPole[Cellx][j] = 1;
								AIPole[Cellx+1][j] = 3;
								AIPole[Cellx-1][j] = 3;
								if(j == Celly)
									{
										AIPole[Cellx][j-1] = 3;
										AIPole[Cellx+1][j-1] = 3;
										AIPole[Cellx-1][j-1] = 3;
										
									}
								if(j == Celly + Size -1)
									{
										AIPole[Cellx][j+1] = 3;
										AIPole[Cellx+1][j+1] = 3;
										AIPole[Cellx-1][j+1] = 3;
									}
							}
					}
			}
	}
	else 
	{AIInitDone = TRUE; AllDone = TRUE; InitPole(FALSE);}
	}
void HitTest(int Cellx, int Celly)
	{
		BOOL Ranen = FALSE;
		if(AIPole[Cellx][Celly] == 1)
			{ 				
				if(AIPole[Cellx+1][Celly] == 1)
					{AIPole[Cellx][Celly] = 4; Ranen = TRUE;AIShipNum--;}
					
				if(AIPole[Cellx-1][Celly] == 1)
					{AIPole[Cellx][Celly] = 4; Ranen = TRUE;AIShipNum--;}
					
				if(AIPole[Cellx][Celly-1] == 1)
					{AIPole[Cellx][Celly] = 4; Ranen = TRUE;AIShipNum--;}
					
				if(AIPole[Cellx][Celly+1] == 1)
					{AIPole[Cellx][Celly] = 4; Ranen = TRUE;AIShipNum--;}	
		if(Ranen == FALSE)
			{
				AIPole[Cellx][Celly] = 5;
				AIShipNum--;
				////
				int x1 = Cellx; int y1 = Celly;
				do	
					{
					x1++; Ranen = FALSE;
					if(AIPole[x1][y1] == 4){AIPole[x1][y1] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x1 = Cellx; y1 = Celly;
				do	
					{
					x1--; Ranen = FALSE;
					if(AIPole[x1][y1] == 4){AIPole[x1][y1] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x1 = Cellx; y1 = Celly;
				do	
					{
					y1++; Ranen = FALSE;
					if(AIPole[x1][y1] == 4){AIPole[x1][y1] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x1 = Cellx; y1 = Celly;
				do	
					{
					y1--; Ranen = FALSE;
					if(AIPole[x1][y1] == 4){AIPole[x1][y1] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);		
				
			}
			}
		else
			{//Если игрок не попал , то ставится точка на пустую клетку
				if (AIPole[Cellx][Celly] == 0)
					{AIPole[Cellx][Celly] = 2;}
				else
					if(AIPole[Cellx][Celly] == 3)
						{AIPole[Cellx][Celly] = 2;}
				MessageBeep(1);
			}	
	}
void ResetGame()
	{
		InitPole(TRUE);					
		NewGame     = TRUE;
		PInitDone   = FALSE;
		AIInitDone  = FALSE;
		AllDone		= FALSE;
		Engaged		= FALSE;
		PTurn		= TRUE;	
		Direction	= 0;	
		Size		= 4;	
		ShipNum		= 0;	
		AIShipNum   = 0;	
	}
void AIHit()
	{
		int x1=rand(); int y1=rand();
		x1%=11; y1%=11;

				BOOL Ranen = FALSE;
		if(PPole[x1][y1] == 1)
			{ 
				//MessageBox(hWnd,"ЭЙ чувак , ты попал  !","Info",NULL);
				if(PPole[x1+1][y1] == 1)
					{PPole[x1][y1] = 4; Ranen = TRUE;ShipNum--;}
					
				if(PPole[x1-1][y1] == 1)
					{PPole[x1][y1] = 4; Ranen = TRUE;ShipNum--;}
					
				if(PPole[x1][y1-1] == 1)
					{PPole[x1][y1] = 4; Ranen = TRUE;ShipNum--;}
					
				if(PPole[x1][y1+1] == 1)
					{PPole[x1][y1] = 4; Ranen = TRUE;ShipNum--;}	
		if(Ranen == FALSE)
			{
				PPole[x1][y1] = 5;
				ShipNum--;
				////
				int x2 = x1; int y2 = y1;
				do	
					{
					x2++; Ranen = FALSE;
					if(PPole[x2][y2] == 4){PPole[x2][y2] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x2 = x1; y2 = y1;
				do	
					{
					x2--; Ranen = FALSE;
					if(PPole[x2][y2] == 4){PPole[x2][y2] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x2 = x1; y2 = y1;
				do	
					{
					y2++; Ranen = FALSE;
					if(PPole[x2][y2] == 4){PPole[x2][y2] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);
				x2 = x1; y2 = y1;
				do	
					{
					y2--; Ranen = FALSE;
					if(PPole[x2][y2] == 4){PPole[x2][y2] = 5; Ranen = TRUE;}
					}
				while(Ranen == TRUE);		
				
			}
			}
		else
			{//Если игрок не попал , то ставится точка на пустую клетку
				if (PPole[x1][y1] == 0)
					{PPole[x1][y1] = 2;}
				else
					if(PPole[x1][y1] == 3)
						{PPole[x1][y1] = 2;}
				MessageBeep(1);
			}	
	}
// Процедура Обработки Сообщений Для About Box
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
