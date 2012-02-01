// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define IDNI_MAINICON					0x0001
#define WM_NOTIFYICON                   WM_USER + 0x0200

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_NOTIFYICON, OnNotifyIcon);
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)		
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnClose)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		//COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_BSET_WALL, BN_CLICKED, OnBnClickedBsetWall)
		COMMAND_HANDLER(IDC_BUTTON_ADD, BN_CLICKED, OnBnClickedButtonAdd)
		COMMAND_HANDLER(IDC_RADIO_TILE, BN_CLICKED, StyleChanged)
		COMMAND_HANDLER(IDC_RADIO_CENTER, BN_CLICKED, StyleChanged)
		COMMAND_HANDLER(IDC_CHECK_STRETCH, BN_CLICKED, StyleChanged)				
		COMMAND_HANDLER(IDC_CHECK_TIMER, BN_CLICKED, OnBnClickedCheckTimer)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_BUTTON_HIDE, BN_CLICKED, OnBnClickedButtonHide)
		COMMAND_HANDLER(IDC_EDIT_SECONDS, EN_CHANGE, OnBnClickedCheckTimer)
		COMMAND_HANDLER(IDC_BUTTON_CLEAR, BN_CLICKED, OnBnClickedButtonClear)
		COMMAND_HANDLER(IDC_BUTTON_ADDFILE, BN_CLICKED, OnBnClickedButtonAddfile)
		COMMAND_HANDLER(IDC_BUTTON_REMFILE, BN_CLICKED, OnBnClickedButtonRemfile)
	END_MSG_MAP()
	CMenu m_ctrlMenu;
	HICON hIconSmall;

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBsetWall(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT StyleChanged(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNotifyIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void OnDestroyNotifyIcon();
	void FindBitmaps(UTEXT pathToScan);	
	void SetRegData();
	void StartTimer(UINT uSeconds);
	void SetWallpaper();
	void InitTray();
	void SaveSettings();
	void LoadSettings();
	DWORD GetXImageType(const UTEXT& uFileName);
	LRESULT OnBnClickedCheckTimer(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
	LRESULT OnBnClickedButtonHide(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);	
	LRESULT OnBnClickedButtonClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonAddfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonRemfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
