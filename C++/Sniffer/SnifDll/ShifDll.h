#define MYHOOKDLL_API __declspec(dllexport)

//#include <windows.h>

extern "C"
{
	MYHOOKDLL_API int SetHook(HWND, UINT);
	MYHOOKDLL_API int UnSetHook();
}
