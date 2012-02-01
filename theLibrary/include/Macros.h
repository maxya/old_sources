// Macros.h :	Defines common used expressions and macros.
//
//////////////////////////////////////////////////////////////////////

#if !defined SW_MACROS_H__A6FED42F_4D5B_4909_B1CF_9BE5006F35DD__INCLUDED
#define SW_MACROS_H__A6FED42F_4D5B_4909_B1CF_9BE5006F35DD__INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifdef _INC_COMMCTRL
#define SNDMSGA ::SendMessageA
#define SNDMSGW ::SendMessageW

//////////////////////////////////////////////////////////////////////
// List View Controls
//////////////////////////////////////////////////////////////////////

#define ListView_SetItemA(hwnd, pitem) \
    (BOOL)SNDMSGA((hwnd), LVM_SETITEMA, 0, (LPARAM)(const LV_ITEMA FAR*)(pitem))
#define ListView_SetItemW(hwnd, pitem) \
    (BOOL)SNDMSGW((hwnd), LVM_SETITEMW, 0, (LPARAM)(const LV_ITEMW FAR*)(pitem))
//////////////////////////////////////////////////////////////////////
#define ListView_InsertColumnA(hwnd, iCol, pcol) \
    (int)SNDMSGA((hwnd), LVM_INSERTCOLUMNA, (WPARAM)(int)(iCol), (LPARAM)(const LV_COLUMNA FAR*)(pcol))
#define ListView_InsertColumnW(hwnd, iCol, pcol) \
    (int)SNDMSGW((hwnd), LVM_INSERTCOLUMNW, (WPARAM)(int)(iCol), (LPARAM)(const LV_COLUMNW FAR*)(pcol))
//////////////////////////////////////////////////////////////////////
#define ListView_InsertItemA(hwnd, pitem)   \
    (int)SNDMSGA((hwnd), LVM_INSERTITEMA, 0, (LPARAM)(const LV_ITEMA FAR*)(pitem))
#define ListView_InsertItemW(hwnd, pitem)   \
    (int)SNDMSGW((hwnd), LVM_INSERTITEMW, 0, (LPARAM)(const LV_ITEMW FAR*)(pitem))
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Windows Extension
//////////////////////////////////////////////////////////////////////

#define     SubclassWindowA(hwnd, lpfn)       \
              ((WNDPROC)SetWindowLongPtrA((hwnd), GWLP_WNDPROC, (LPARAM)(WNDPROC)(lpfn)))
#define     SubclassWindowW(hwnd, lpfn)       \
              ((WNDPROC)SetWindowLongPtrW((hwnd), GWLP_WNDPROC, (LPARAM)(WNDPROC)(lpfn)))
#define _SubclassWindow(hwnd, lpfn)	\
			IsWindowUnicode (hwnd) ? SubclassWindowW(hwnd, lpfn) : SubclassWindowA(hwnd, lpfn)
//////////////////////////////////////////////////////////////////////
#define _Window_Disable(hWhatWnd)			EnableWindow	(hWhatWnd, false)
#define _Window_Enable(hWhatWnd)			EnableWindow	(hWhatWnd, true)
#define _DlgItem_Disable(hWhatDlg, nIDC)	EnableWindow	(GetDlgItem (hWhatDlg, nIDC), false)
#define _DlgItem_Enable(hWhatDlg, nIDC)		EnableWindow	(GetDlgItem (hWhatDlg, nIDC), true)
//////////////////////////////////////////////////////////////////////
// ListBox controls
//////////////////////////////////////////////////////////////////////

#define ListBox_AddStringA(hwndCtl, lpsz)		\
    ((int)(DWORD)SNDMSGA((hwndCtl), LB_ADDSTRING, 0L, (LPARAM)(LPCSTR)(lpsz)))
#define ListBox_AddStringW(hwndCtl, lpsz)		\
	((int)(DWORD)SNDMSGW((hwndCtl), LB_ADDSTRING, 0L, (LPARAM)(LPCWSTR)(lpsz)))
#define _ListBox_AddString(hwndCtl, lpsz)		\
	IsWindowUnicode(hwndCtl) ?					\
	ListBox_AddStringW(hwndCtl, lpsz) :			\
	ListBox_AddStringA(hwndCtl, lpsz)
//////////////////////////////////////////////////////////////////////
#define ListBox_InsertStringA(hwndCtl, index, lpsz)	\
	((int)(DWORD)SNDMSGA((hwndCtl), LB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCSTR)(lpsz)))
#define ListBox_InsertStringW(hwndCtl, index, lpsz)	\
	((int)(DWORD)SNDMSGW((hwndCtl), LB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCWSTR)(lpsz)))
#define _ListBox_InsertString(hwndCtl, index, lpsz)		\
	IsWindowUnicode(hwndCtl) ?							\
	ListBox_InsertStringW(hwndCtl, index, lpsz) :		\
	ListBox_InsertStringA(hwndCtl, index, lpsz)

//////////////////////////////////////////////////////////////////////
// Combo box controls
//////////////////////////////////////////////////////////////////////

#define ComboBox_AddStringA(hwndCtl, lpsz)				\
	((int)(DWORD)SNDMSGA((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(LPCSTR)(lpsz)))
#define ComboBox_AddStringW(hwndCtl, lpsz)				\
	((int)(DWORD)SNDMSGW((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(LPCWSTR)(lpsz)))
#define _ComboBox_AddString(hwndCtl, lpsz)		\
	IsWindowUnicode(hwndCtl) ?								\
	ComboBox_AddStringW(hwndCtl, lpsz) :			\
	ComboBox_AddStringA(hwndCtl, lpsz)
//////////////////////////////////////////////////////////////////////
#define ComboBox_InsertStringA(hwndCtl, index, lpsz)		\
	SNDMSGA((hwndCtl), CB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCSTR)(lpsz))
#define ComboBox_InsertStringW(hwndCtl, index, lpsz)		\
	SNDMSGW((hwndCtl), CB_INSERTSTRING, (WPARAM)(int)(index), (LPARAM)(LPCWSTR)(lpsz))
#define _ComboBox_InsertString(hwndCtl, index, lpsz)		\
	IsWindowUnicode(hwndCtl) ?								\
	ComboBox_InsertStringW(hwndCtl, index, lpsz) :			\
	ComboBox_InsertStringA(hwndCtl, index, lpsz)
//////////////////////////////////////////////////////////////////////
#define ComboBox_SetHorizontalExtent(hwndCtl, cxExtent)     SNDMSG (hwndCtl, CB_SETHORIZONTALEXTENT, (WPARAM)(int)(cxExtent), 0L)

//////////////////////////////////////////////////////////////////////
// Tab controls
//////////////////////////////////////////////////////////////////////

#define TabCtrl_InsertItemA(hwnd, iItem, pitem)   \
    (int)SNDMSGA((hwnd), TCM_INSERTITEMA, (WPARAM)(int)(iItem), (LPARAM)(const TC_ITEMA FAR*)(pitem))
#define TabCtrl_InsertItemW(hwnd, iItem, pitem)   \
    (int)SNDMSGW((hwnd), TCM_INSERTITEMW, (WPARAM)(int)(iItem), (LPARAM)(const TC_ITEMW FAR*)(pitem))
//////////////////////////////////////////////////////////////////////
#define TabCtrl_SetItemA(hwnd, iItem, pitem) \
    (BOOL)SNDMSGA((hwnd), TCM_SETITEMA, (WPARAM)(int)(iItem), (LPARAM)(TC_ITEMA FAR*)(pitem))
#define TabCtrl_SetItemW(hwnd, iItem, pitem) \
    (BOOL)SNDMSGW((hwnd), TCM_SETITEMW, (WPARAM)(int)(iItem), (LPARAM)(TC_ITEMW FAR*)(pitem))

//#define IsWindowVisible(_hwnd)			(GetWindowLong (_hwnd, GWL_STYLE) & WS_VISIBLE)

#define LODWORD(l)           ((DWORD)((ULONGLONG)(l) & 0xffffffff))
#define HIDWORD(l)           ((DWORD)((ULONGLONG)(l) >> 32))

#define IsBetween(lo, hi, val)		(val >= lo && val <= hi)
#define countof(_x) sizeof(_x) / sizeof(_x[0])

#ifndef SWASSERT
#define SWASSERT(expr) _ASSERTE(expr)
#endif

#define NULLSTRING	(LPTSTR)NULL

#endif //!defined SW_MACROS_H__A6FED42F_4D5B_4909_B1CF_9BE5006F35DD__INCLUDED