// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"


#define ID_MAIN_TIMER	12

char BitmapPath[MAX_PATH];
CswUTArray FileNames;
CswRegKey regRoot, regMy;
UTEXT CurSelItem;
//GlobalSettings
UTEXT DefPath;
CswNamedUTPairs arINI;
//EOFGlobalSettings
extern HINSTANCE hglobeInst;


LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	
	LoadSettings();
	CenterWindow();
	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON1), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON1), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);
	InitTray();

	FindBitmaps(DefPath);
	SendMessage(GetDlgItem(IDC_BMP_LIST), LB_SETCURSEL,0,0);	
	
	return TRUE;
}
void CMainDlg::LoadSettings()
{
	CswFile iniFile,listFile;

	if(iniFile.OpenHDD("config.ini", GENERIC_READ, 0))
	{
		swParseINIFile(iniFile, arINI);		
		DefPath = arINI["Core"]["Path"];
		if(_tcscmp(arINI["Settings"]["Style"],
			 _T("Center")) == 0)//Center or Tile
			SendMessage(GetDlgItem(IDC_RADIO_CENTER), BM_SETCHECK, (WPARAM)BST_CHECKED,0);
		else
			SendMessage(GetDlgItem(IDC_RADIO_TILE), BM_SETCHECK, (WPARAM)BST_CHECKED,0);
		if(_tcscmp(arINI["Settings"]["Stretch"],
			_T("true")) == 0)//Stretch ?
			SendMessage(GetDlgItem(IDC_CHECK_STRETCH), BM_SETCHECK, (WPARAM)BST_CHECKED,0);
		
		SetDlgItemText(IDC_EDIT_SECONDS, arINI["Settings"]["Interval"]);

		if(_tcscmp(arINI["Settings"]["UseTimer"],
			_T("true")) == 0) //Use Timer ?
		{
			SendMessage(GetDlgItem(IDC_CHECK_TIMER), BM_SETCHECK, (WPARAM)BST_CHECKED,0);
			StartTimer((UINT)GetDlgItemInt(IDC_EDIT_SECONDS, NULL, FALSE)*1000);
		}
		iniFile.Close();
	}
	//if(listFile.OpenHDD("dmList.ini", GENERIC_READ, 0))
	//{
	//	//TODO:
	//	// Make this fucken list work!!!
	//	UTEXT utTemp,utRBuff;
	//	//listFile.Read(&utRBuff, (DWORD)listFile.GetFileSize());		
	//	//MessageBox(utRBuff,"buffer");
	//	//SendMessage(GetDlgItem(IDC_BMP_LIST), LB_ADDSTRING, 0,(LPARAM)(LPSTR)utTemp);
	//	//FileNames.Push(utTemp);
	//	
	//}
}
void CMainDlg::SaveSettings()
{
	CswFile iniFile;	
	UTEXT utemp;	
	//DefPath = arINI["Core"]["Path"];
	if(iniFile.OpenHDD("config.ini", GENERIC_WRITE, 0))
	{
		utemp = DefPath;
		arINI["Core"]["Path"] = utemp;
		if(SendMessage(GetDlgItem(IDC_RADIO_CENTER), BM_GETCHECK, 0,0)==BST_CHECKED)
			utemp="Center";
		else
			utemp="Tile";
		arINI["Settings"]["Style"] = utemp;
		if(SendMessage(GetDlgItem(IDC_CHECK_STRETCH), BM_GETCHECK, 0,0)==BST_CHECKED)
			utemp="true";
		else
			utemp="false";
		arINI["Settings"]["Stretch"] = utemp;
		utemp.Empty();
		GetDlgItemTextUT(m_hWnd, IDC_EDIT_SECONDS, utemp);
		arINI["Settings"]["Interval"] = utemp;
		
		if(SendMessage(GetDlgItem(IDC_CHECK_TIMER), BM_GETCHECK, 0,0)==BST_CHECKED)
			utemp="true";
		else
			utemp="false";
		arINI["Settings"]["UseTimer"] = utemp;
		swWriteINIFile(iniFile, arINI);
		iniFile.Close();
	}
}

LRESULT CMainDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{	
	OnDestroyNotifyIcon();
	SaveSettings();
	PostQuitMessage(WM_CLOSE);
	return 0;
}

void CMainDlg::InitTray()
{
	m_ctrlMenu.CreatePopupMenu();
	MENUITEMINFO mii;
	ZeroMemory (&mii, sizeof (mii));
	mii.cbSize = sizeof (mii);
	mii.fMask = MIIM_STATE | MIIM_ID | 0x00000040;
	//mii.fMask =  MIIM_STATE | MIIM_ID | MIIM_STRING;
	
	mii.dwTypeData = TEXT("About");
	mii.fState = MFS_ENABLED | MFS_DEFAULT;
	mii.wID = ID_APP_ABOUT;
	m_ctrlMenu.InsertMenuItem (0, TRUE, &mii);	
	mii.dwTypeData = TEXT("Exit");	
	mii.fState = MFS_ENABLED;
	mii.wID = IDOK;
	m_ctrlMenu.InsertMenuItem (1, TRUE, &mii);

	// Tray icon init
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof (nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDNI_MAINICON;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hIcon = hIconSmall;
	nid.uCallbackMessage = WM_NOTIFYICON;
	::StrCpy(nid.szTip, "Descktop Manager");
	::Shell_NotifyIcon (NIM_ADD, &nid);

}
LRESULT CMainDlg::OnNotifyIcon(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	switch(lParam)
	{
	case WM_RBUTTONUP:
	case WM_CONTEXTMENU:
		{
			::SetForegroundWindow( m_hWnd );
			POINT pt; ::GetCursorPos( &pt );
			m_ctrlMenu.TrackPopupMenu( 0, pt.x, pt.y, m_hWnd );
		}
		break;
	case WM_LBUTTONUP:
		ShowWindow(TRUE);
		//TODO: Add command for left mouse button click here, if needed 
		break;
	}
	return 0;
}
void CMainDlg::OnDestroyNotifyIcon()
{
	//Destroys Notify Icon (TrayIcon);
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDNI_MAINICON;
	nid.uCallbackMessage = WM_NOTIFYICON;
	::Shell_NotifyIcon(NIM_DELETE, &nid);
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	
	return 0;
}
LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SaveSettings();
	OnDestroyNotifyIcon();
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnBnClickedBsetWall(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetWallpaper();
	return 0;
}
void CMainDlg::SetWallpaper()
{
	CxImage cxImg;
	UTEXT WinDir = getenv("SystemRoot");
	int curSelIndex = SendMessage(GetDlgItem(IDC_BMP_LIST), LB_GETCURSEL,0,0);
	CurSelItem = FileNames[curSelIndex];	
	if(cxImg.Load(static_cast<LPCWSTR>(CurSelItem),GetXImageType(CurSelItem)))
	{
		CurSelItem = WinDir + "\\" + "dm_wallpaper.bmp";
		cxImg.Save(static_cast<LPCWSTR>(CurSelItem),CXIMAGE_FORMAT_BMP);
		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (LPSTR)CurSelItem, 0);
		SetRegData();
	}	

}
void CMainDlg::SetRegData()
{	
	regRoot.Attach(HKEY_CURRENT_USER);
	
	if(ERROR_SUCCESS == regMy.Open(regRoot, "Control Panel\\Desktop\\"))
	{//regMy.QueryValue(ProgramPath, TEXT("path"));
		regMy.SetValue((LPSTR)CurSelItem,"Wallpaper");
		if(SendMessage(GetDlgItem(IDC_RADIO_TILE), BM_GETCHECK, 0,0)==BST_CHECKED)
			regMy.SetValue("1", "TileWallpaper");
		if(SendMessage(GetDlgItem(IDC_RADIO_CENTER), BM_GETCHECK, 0,0)==BST_CHECKED)
			regMy.SetValue("0", "TileWallpaper");
		

		if(SendMessage(GetDlgItem(IDC_CHECK_STRETCH), BM_GETCHECK, 0,0)==BST_CHECKED)
			regMy.SetValue("2", "WallpaperStyle");
		else
			regMy.SetValue("0", "WallpaperStyle");
	}
	regRoot.Detach();	
}
LRESULT CMainDlg::OnBnClickedButtonAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.iImage = NULL;
	bi.lParam = NULL;
	bi.lpfn = NULL;
	bi.lpszTitle = "Select bitmap directory";
	bi.pidlRoot = NULL;
	bi.pszDisplayName = BitmapPath;	
	bi.ulFlags = BIF_VALIDATE |  BIF_STATUSTEXT | BIF_EDITBOX | BIF_RETURNONLYFSDIRS | BIF_DONTGOBELOWDOMAIN;

	LPCITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if(SHGetPathFromIDList(pidl, BitmapPath) == TRUE)		
	{		
		FindBitmaps((UTEXT)BitmapPath);
		SetRegData();
		DefPath = BitmapPath;
	}
	
	if(SendMessage(GetDlgItem(IDC_BMP_LIST), LB_GETCOUNT,0,0)!=0)
		SendMessage(GetDlgItem(IDC_BMP_LIST), LB_SETCURSEL,0,0);

	return 0;
}
LRESULT CMainDlg::OnBnClickedButtonAddfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	char szFileTitle[260];		
	UTEXT utTemp;

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = this->m_hWnd;
	ofn.hInstance = hglobeInst;
	ofn.lpstrFile = szFile;			
	ofn.nMaxFile = sizeof(szFile);	
	ofn.lpstrFilter = "All\0*.*\0Image Files\0*.bmp;*.jpg;*.gif;*jpeg;";
	ofn.nFilterIndex = 1;	
	/*ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = sizeof(szFileTitle);*/
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Add File...";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	if (GetOpenFileName(&ofn)==TRUE) 
	{
		utTemp = szFile;
		FileNames.Push(utTemp);
		//utTemp = szFileTitle;
		SendMessage(GetDlgItem(IDC_BMP_LIST), LB_ADDSTRING, 0,(LPARAM)(LPSTR)utTemp);
	}
	
	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SendMessage(GetDlgItem(IDC_BMP_LIST), LB_SETCOUNT, (WPARAM)0,0);
	SendMessage(GetDlgItem(IDC_BMP_LIST), LB_RESETCONTENT,0,0);
	return 0;
}
LRESULT CMainDlg::OnBnClickedButtonRemfile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	UTEXT utTemp;
	int iCurItem = SendMessage(GetDlgItem(IDC_BMP_LIST), LB_GETCURSEL, 0,0);
	SendMessage(GetDlgItem(IDC_BMP_LIST), LB_DELETESTRING, (WPARAM)iCurItem,0);	
	//MessageBox(FileNames[iCurItem],"Curent File Name");
	//FileNames[iCurItem].Delete();
	FileNames.PopAt(iCurItem, utTemp);	
	SendMessage(GetDlgItem(IDC_BMP_LIST), LB_SETCURSEL, (WPARAM)iCurItem,0);
	return 0;
}

void CMainDlg::FindBitmaps(UTEXT pathToScan)
{	
	WIN32_FIND_DATA ffd;
	UTEXT FindPath = pathToScan;	
	FindPath += "\\*.*";	
	HANDLE hSerch = FindFirstFile(FindPath, &ffd);
	if(hSerch == INVALID_HANDLE_VALUE)
		return;	
	do {
		UTEXT FileName = ffd.cFileName;
		UTEXT RealName = pathToScan + "\\" + FileName;		
		
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(!FileName.CaseInsensitiveCompare(".") &&
				!FileName.CaseInsensitiveCompare("..") &&
				!FileName.CaseInsensitiveCompare("RECYCLED") &&
				!FileName.CaseInsensitiveCompare("RECYCLER"))
				FindBitmaps(RealName);				
		}
		else
		{
			if(GetXImageType(FileName))
			{
				SendMessage(GetDlgItem(IDC_BMP_LIST), LB_ADDSTRING, 0,(LPARAM)(LPSTR)FileName);//RealName);//FileName);		
				FileNames.Push(RealName);
			}
		}
		
	} while(FindNextFile(hSerch, &ffd));
	FindClose(hSerch);
}
LRESULT CMainDlg::StyleChanged(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//To Fix Some Bugs With Changing Style
	SetRegData();	
	return 0;
}
void CMainDlg::StartTimer(UINT uSeconds)
{	
	::SetTimer(m_hWnd, ID_MAIN_TIMER, uSeconds, (TIMERPROC) NULL);
    
}
LRESULT CMainDlg::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	//::KillTimer(m_hWnd,ID_MAIN_TIMER);
	UINT uCurSelItem = SendMessage(GetDlgItem(IDC_BMP_LIST), LB_GETCURSEL,0,0);
	UINT uTotalItems = SendMessage(GetDlgItem(IDC_BMP_LIST), LB_GETCOUNT,0,0);
	if(uCurSelItem != uTotalItems-1)
		uCurSelItem++;
	else
		uCurSelItem=0;
	SendMessage(GetDlgItem(IDC_BMP_LIST),LB_SETCURSEL, uCurSelItem,0); 
	SetWallpaper();
	
	return 0;
}
LRESULT CMainDlg::OnBnClickedCheckTimer(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(SendMessage(GetDlgItem(IDC_CHECK_TIMER), BM_GETCHECK, 0,0)==BST_CHECKED)
	{	
		UINT curSec =(UINT)GetDlgItemInt(IDC_EDIT_SECONDS, NULL, FALSE)*1000;
		if(curSec==0)
			curSec=1;		
		StartTimer(curSec);
	}
	else	
		::KillTimer(m_hWnd,ID_MAIN_TIMER);
	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonHide(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(FALSE);
	// TODO: Add your control notification handler code here
	return 0;
}

DWORD CMainDlg::GetXImageType(const UTEXT& uFileName)
{
        UTEXT uSuffix = uFileName.Right(4);
#if CXIMAGE_SUPPORT_BMP
        if( uSuffix.CaseInsensitiveCompare(".bmp") ||
                uSuffix.CaseInsensitiveCompare(".dib"))
                return CXIMAGE_FORMAT_BMP;
#endif
#if CXIMAGE_SUPPORT_GIF
        if( uSuffix.CaseInsensitiveCompare(".gif"))
                return CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_JPG
        if( uSuffix.CaseInsensitiveCompare(".jpeg") ||
                uSuffix.CaseInsensitiveCompare(".jpg"))
                return CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_PNG
        if( uSuffix.CaseInsensitiveCompare(".png"))
                return CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
        if( uSuffix.CaseInsensitiveCompare(".mng"))
                return CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
        if( uSuffix.CaseInsensitiveCompare(".ico"))
                return CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
        if( uSuffix.CaseInsensitiveCompare(".tiff") ||
                uSuffix.CaseInsensitiveCompare(".tif"))
                return CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
        if( uSuffix.CaseInsensitiveCompare(".targa") ||
                uSuffix.CaseInsensitiveCompare(".tga"))
                return CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
        if( uSuffix.CaseInsensitiveCompare(".ico"))
                return CXIMAGE_FORMAT_PCX;
#endif
        return 0;
}






