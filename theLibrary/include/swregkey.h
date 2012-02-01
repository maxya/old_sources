// swRegKey.h: interface for the CswRegKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWREGKEY_H__E1887D9E_E238_40D4_9A66_A783ABF26F45__INCLUDED_)
#define AFX_SWREGKEY_H__E1887D9E_E238_40D4_9A66_A783ABF26F45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CswRegKey


/*
	CswRegKey	m_reg;
	LONG res = m_reg.Open(HKEY_CURRENT_USER,"Software\\SeekWood");

	CswRegKey	m_regTo;
	LONG res1 = m_regTo.Open(HKEY_CURRENT_USER,"Software");
	HKEY hKeyTo = m_regTo.Create("Igor Vershynin");
	if (hKeyTo)
	{
		m_reg.RecurseCopyKeyTo(hKeyTo);
	}
	m_reg.Close();
	m_reg.Open(HKEY_CURRENT_USER,"Software");
	m_reg.RecurseDeleteKey("SeekWood");


*/
class CswRegKey
{
public:
	CswRegKey::CswRegKey()
	{m_hKey = NULL;}
	
	CswRegKey::~CswRegKey()
	{Close();}


// Attributes
public:
	operator HKEY() const;
	HKEY m_hKey;

// Operations
public:
	LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName);
	LONG SetValue(DWORD dwType, LPCTSTR lpszValueName, LPBYTE lpData, DWORD dwDataSize);
	LONG QueryValue(DWORD& dwValue, LPCTSTR lpszValueName);
	LONG QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount);
	LONG QueryValue(CUniversalText &utValue, LPCTSTR lpszValueName);
	
	LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	LONG Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		REGSAM samDesired = KEY_ALL_ACCESS,
		LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		LPDWORD lpdwDisposition = NULL);
	HKEY Create(LPCTSTR lpszKeyName,
		LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		REGSAM samDesired = KEY_ALL_ACCESS,
		LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		LPDWORD lpdwDisposition = NULL);
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,
		REGSAM samDesired = KEY_ALL_ACCESS);
	LONG Close();
	HKEY Detach();
	void Attach(HKEY hKey);
	LONG DeleteSubKey(LPCTSTR lpszSubKey);
	LONG RecurseDeleteKey(LPCTSTR lpszKey);
	LONG RecurseCopyKeyTo(HKEY hKeyTo,LPCTSTR lpszKey=NULL);
	LONG DeleteValue(LPCTSTR lpszValue);
};

inline CswRegKey::operator HKEY() const
{return m_hKey;}

inline HKEY CswRegKey::Detach()
{
	HKEY hKey = m_hKey;
	m_hKey = NULL;
	return hKey;
}

inline void CswRegKey::Attach(HKEY hKey)
{
	ATLASSERT(m_hKey == NULL);
	m_hKey = hKey;
}


inline LONG CswRegKey::DeleteValue(LPCTSTR lpszValue)
{
	ATLASSERT(m_hKey != NULL);
	return RegDeleteValue(m_hKey, (LPTSTR)lpszValue);
}

inline LONG CswRegKey::DeleteSubKey(LPCTSTR lpszSubKey)
{
	ATLASSERT(m_hKey != NULL);
	return RegDeleteKey(m_hKey, lpszSubKey);
}

inline LONG CswRegKey::Close()
{
	LONG lRes = ERROR_SUCCESS;
	if (m_hKey != NULL)
	{
		lRes = RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
	return lRes;
}

inline LONG CswRegKey::Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
	LPTSTR lpszClass, DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecAttr, LPDWORD lpdwDisposition)
{
	ATLASSERT(hKeyParent != NULL);
	DWORD dw;
	HKEY hKey = NULL;
	LONG lRes = RegCreateKeyEx(hKeyParent, lpszKeyName, 0,
		lpszClass, dwOptions, samDesired, lpSecAttr, &hKey, &dw);
	if (lpdwDisposition != NULL)
		*lpdwDisposition = dw;
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		m_hKey = hKey;
	}
	return lRes;
}

inline HKEY CswRegKey::Create(LPCTSTR lpszKeyName,
	LPTSTR lpszClass, DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecAttr, LPDWORD lpdwDisposition)
{
	ATLASSERT(m_hKey != NULL);
	if (m_hKey == NULL) return NULL;
	DWORD dw;
	HKEY hKey = NULL;
	LONG lRes = RegCreateKeyEx(m_hKey, lpszKeyName, 0,
		lpszClass, dwOptions, samDesired, lpSecAttr, &hKey, &dw);
	if (lpdwDisposition != NULL)
		*lpdwDisposition = dw;
	if (lRes == ERROR_SUCCESS)
	{
		return hKey;
	}
	return NULL;
	
}


inline LONG CswRegKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired)
{
	ATLASSERT(hKeyParent != NULL);
	HKEY hKey = NULL;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &hKey);
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		ATLASSERT(lRes == ERROR_SUCCESS);
		m_hKey = hKey;
	}
	return lRes;
}

inline LONG CswRegKey::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
{
	DWORD dwType = NULL;
	DWORD dwCount = sizeof(DWORD);
	LONG lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_DWORD));
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwCount == sizeof(DWORD)));
	return lRes;
}

inline LONG CswRegKey::QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount)
{
	ATLASSERT(pdwCount != NULL);
	DWORD dwType = NULL;
	LONG lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType,
		(LPBYTE)szValue, pdwCount);
	ATLASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_SZ) ||
			 (dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));
	return lRes;
}
inline LONG CswRegKey::QueryValue(CUniversalText &utValue, LPCTSTR lpszValueName)
{
	utValue.Empty();
	LONG lRes = 0;
	char buff[20480];
	DWORD dwCount = 20480;
	lRes = QueryValue(buff,lpszValueName,&dwCount);
	utValue = buff;
	return lRes;
}
inline LONG WINAPI CswRegKey::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ATLASSERT(lpszValue != NULL);
	CswRegKey key;
	LONG lRes = key.Create(hKeyParent, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetValue(lpszValue, lpszValueName);
	return lRes;
}

inline LONG CswRegKey::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ATLASSERT(lpszValue != NULL);
	CswRegKey key;
	LONG lRes = key.Create(m_hKey, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetValue(lpszValue, lpszValueName);
	return lRes;
}

inline LONG CswRegKey::SetValue(DWORD dwValue, LPCTSTR lpszValueName)
{
	ATLASSERT(m_hKey != NULL);
	return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_DWORD,
		(BYTE * const)&dwValue, sizeof(DWORD));
}

inline LONG CswRegKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ATLASSERT(lpszValue != NULL);
	ATLASSERT(m_hKey != NULL);
	return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ,
		(BYTE * const)lpszValue, (lstrlen(lpszValue)+1)*sizeof(TCHAR));
}

inline LONG CswRegKey::SetValue(DWORD dwType, LPCTSTR lpszValueName, LPBYTE lpData, DWORD dwDataSize)
{
	ATLASSERT(lpszValueName != NULL);
	ATLASSERT(m_hKey != NULL);
	return RegSetValueEx(m_hKey, lpszValueName, NULL, dwType,lpData,dwDataSize);
}

inline LONG CswRegKey::RecurseDeleteKey(LPCTSTR lpszKey)
{
	CswRegKey key;
	LONG lRes = key.Open(m_hKey, lpszKey, KEY_READ | KEY_WRITE);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	FILETIME time;
	DWORD dwSize = 256;
	TCHAR szBuffer[256];
	while (RegEnumKeyEx(key.m_hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
		&time)==ERROR_SUCCESS)
	{
		lRes = key.RecurseDeleteKey(szBuffer);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		dwSize = 256;
	}
	key.Close();
	return DeleteSubKey(lpszKey);
}

inline LONG CswRegKey::RecurseCopyKeyTo(HKEY hKeyTo,LPCTSTR lpszKey)
{
	CswRegKey key;
	LONG lRes;
	BOOL fAttach = TRUE;
	if (lpszKey)
	{
		lRes = key.Open(m_hKey, lpszKey, KEY_READ | KEY_WRITE);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		fAttach = FALSE;
	}
	else
		key.Attach(m_hKey);
	FILETIME time;
	DWORD dwSize = 256;
	TCHAR szBuffer[256];
	DWORD dwIndex=0;
	while (RegEnumKeyEx(key.m_hKey, dwIndex, szBuffer, &dwSize, NULL, NULL, NULL,&time)==ERROR_SUCCESS)
	{
		CswRegKey tempKey;
		tempKey.Create(hKeyTo,szBuffer);
		lRes = key.RecurseCopyKeyTo(tempKey,szBuffer);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		dwSize = 256;
		dwIndex++;
		tempKey.Close();
	}
	dwIndex=0;
	DWORD dwType=0;
	BYTE Byte[20480];
	DWORD dwDataSize=sizeof(Byte);
	while(RegEnumValue(key.m_hKey,dwIndex,szBuffer,&dwSize,NULL,&dwType,Byte,&dwDataSize)==ERROR_SUCCESS)
	{

		CswRegKey tempKey;
		tempKey.Attach(hKeyTo);
		tempKey.SetValue(dwType,szBuffer,Byte,dwDataSize);
		dwSize = 256;
		dwDataSize=256;
		dwIndex++;
		tempKey.Detach();
	}
	
	if (fAttach)key.Detach();
	return 0;
}




#endif // !defined(AFX_SWREGKEY_H__E1887D9E_E238_40D4_9A66_A783ABF26F45__INCLUDED_)
