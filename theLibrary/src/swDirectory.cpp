#include "stdafx.h"
#include "Macros.h"
#include "swdirectory.h"

CswDirectory::CswDirectory(void)
{
	Init ();
}

CswDirectory::CswDirectory(CswDirectory& swDir)
{
	Init ();
	*this = swDir;
}

CswDirectory::CswDirectory(IStorage* pStorage)
{
	Init ();
	*this = pStorage;
}

CswDirectory::~CswDirectory(void)
{
	CleanUp ();
}

CswDirectory& CswDirectory::operator = (CswDirectory& swDir)
{
	AttachStorage ((IStorage*) swDir);
	return *this;
}

CswDirectory& CswDirectory::operator = (IStorage* pStorage)
{
	AttachStorage (pStorage);
	return *this;
}

void CswDirectory::Init()
{
	m_pStorage = NULL;
	//m_pUnkParent = NULL;
	m_utMapFile = ".vnmfw"; // virtual names map file (wide strings)
}

void CswDirectory::CleanUp ()
{
	ReleaseParent();
	if (m_pStorage)
	{
		PreDetach ();
		m_pStorage->Release ();
		m_pStorage = NULL;
	}
	m_mpR2V.Clear ();
}

BOOL CswDirectory::OpenHDD (CUniversalText utName,	/* файл хранилища */
	DWORD grfMode,						/* (STGM_READ + STGM_SHARE_DENY_NONE) || 
											(STGM_WRITE + STGM_SHARE_EXCLUSIVE) || 
											(STGM_READWRITE + STGM_SHARE_EXCLUSIVE)
											STGM_CREATE -- создать, иначе открыть */
	DWORD dwImplType					/* IT_COMSTG (биллгэйтсовая) || IT_SSF (наша) */
	)
{
	if (utName.IsEmpty ())
		return FALSE;
	HRESULT hr;
	switch (dwImplType)
	{
	case IT_COMSTG:
		if (grfMode & STGM_CREATE)
		{
			if (FAILED(hr =	StgCreateDocfile (
					utName, 
					grfMode, 
					0,
					&m_pStorage
				)))
				return FALSE;
		}
		else
		{
			if (FAILED(hr =	StgOpenStorage (
				utName, 
				NULL,
				grfMode, 
				NULL,
				0,
				&m_pStorage
				)))
				return FALSE;
		}
/*
		if (grfMode & STGM_CREATE)
		{
			if (FAILED(hr =	StgCreateStorageEx (
					utName, 
					grfMode, 
					STGFMT_STORAGE,
					0,
					NULL, //&stgOpt,
					NULL,
					IID_IStorage,
					(void**) &m_pStorage
				)))
				return FALSE;
		}
		else
		{
			if (FAILED(hr =	StgOpenStorageEx (
					utName, 
					grfMode, 
					STGFMT_STORAGE,
					0,
					NULL, //&stgOpt,
					NULL,
					IID_IStorage,
					(void**) &m_pStorage
				)))
				return FALSE;
		}
*/
		break;
	case IT_SSF:
		/* not implemented yet */		
	default:
		return FALSE;
	}
	PostAttach ();
	return TRUE;
}

BOOL CswDirectory::Close ()
{
	CleanUp();
	return TRUE;
}

BOOL CswDirectory::AttachStorage (IN IStorage* pStorage)
{
	if (!pStorage || IsBadReadPtr (pStorage, sizeof(*pStorage)))
		return FALSE;
	CleanUp ();
	m_pStorage = pStorage;
	m_pStorage->AddRef ();
	PostAttach ();
	return TRUE;
}

BOOL CswDirectory::DetachStorage (OUT IStorage** ppStorage)
{
	if (!m_pStorage)
		return FALSE;
	if (!ppStorage || IsBadWritePtr (ppStorage, sizeof(*ppStorage)))
		return FALSE;
	*ppStorage = m_pStorage;
	m_pStorage->AddRef ();
	CleanUp();
	return TRUE;
}

BOOL CswDirectory::BindToParent (IN IUnknown* pUnkParent)
{
	//ReleaseParent ();
	//m_pUnkParent = pUnkParent;
	//m_pUnkParent->AddRef();
	m_arBound.Push (pUnkParent);
	return TRUE;
}

BOOL CswDirectory::ReleaseParent ()
{
	//if (m_pUnkParent)
	//	m_pUnkParent->Release();
	//m_pUnkParent = NULL;
	m_arBound.Clear ();
	return TRUE;
}

BOOL CswDirectory::OpenDir (CUniversalText utName, DWORD grfMode, OUT CswDirectory& swDir)
{
	IStorage* pNewStg;
	if (!m_pStorage)
		return FALSE;
	
	OPEN_INFO *info = m_mpOpened.Lookup(utName);
	if (info && info->m_pChild)
	{
		if (FAILED (info->m_pChild->QueryInterface(IID_IStorage, (void**) &pNewStg)))
			return FALSE;
	}
	else
	{
		if (grfMode & STGM_CREATE)
		{
			if (FAILED (m_pStorage->CreateStorage (utName, grfMode, 0, 0, &pNewStg)))
				return FALSE;
		}
		else
		{
			if (FAILED (m_pStorage->OpenStorage (utName, NULL, grfMode, 0, 0, &pNewStg)))
				return FALSE;
		}
	}
	info = &m_mpOpened[utName];
	swDir.AttachStorage (pNewStg);
	info->AttachChild(pNewStg);
	for (UINT i = 0; i < m_arBound.Count (); i++)
		swDir.BindToParent (m_arBound[i]);
	swDir.BindToParent(m_pStorage);
	swDir.BindToParent(info);

	pNewStg->Release ();
	return TRUE;
}

BOOL CswDirectory::OpenFile (CUniversalText utName, DWORD grfMode, OUT CswFile& swFile)
{
	IStream* pNewStream;
	if (!m_pStorage)
		return FALSE;
	OPEN_INFO *info = m_mpOpened.Lookup(utName);
	if (info && info->m_pChild)
	{
		if (FAILED (info->m_pChild->QueryInterface(IID_IStream, (void**) &pNewStream)))
			return FALSE;
	}
	else
	{
		if (grfMode & STGM_CREATE)
		{
			if (FAILED(m_pStorage->CreateStream (utName, grfMode, 0, 0, &pNewStream)))
				return FALSE;
		}
		else
		{
			if (FAILED(m_pStorage->OpenStream (utName, NULL, grfMode, 0, &pNewStream)))
				return FALSE;
		}
	}
	
	swFile.AttachStream (pNewStream);
	
	info = &m_mpOpened[utName];
	(*info).AttachChild(pNewStream);
	for (UINT i = 0; i < m_arBound.Count (); i++)
		swFile.BindToParent (m_arBound[i]);
	swFile.BindToParent(m_pStorage);
	swFile.BindToParent(info);

	pNewStream->Release ();
	return TRUE;
}

void CswDirectory::ElementClosed (IN CUniversalText utName)
{
	OPEN_INFO *info = m_mpOpened.Lookup(utName);
	if (info && !info->m_pChild)
	{
		m_mpOpened.UnSet (utName);
	}
}

void CswDirectory::ElementClosedVN (IN CUniversalText utName)
{
	ElementClosed (NameVirtualToReal (utName));
}

BOOL CswDirectory::DestroyElement (IN CUniversalText utName)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->DestroyElement (utName));
}

BOOL CswDirectory::RenameElement (IN CUniversalText utOldName, IN CUniversalText utNewName)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->RenameElement (utOldName, utNewName));
}

BOOL CswDirectory::CopyTo (CswDirectory& swDirDest, 
			 DWORD ciidExclude, 
			 IID const *rgiidExclude, 
			 SNB snbExclude)
{	
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->CopyTo (ciidExclude, rgiidExclude, snbExclude, swDirDest));
}

BOOL CswDirectory::MoveElementTo (IN CUniversalText utName,
								  IN CswDirectory& swDirDest,
								  IN CUniversalText utNewName,
								  IN DWORD grfFlags)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->MoveElementTo (utName, swDirDest, utNewName, grfFlags));
}

BOOL CswDirectory::EnumElements (OUT IEnumSTATSTG** pEnum)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->EnumElements (0, NULL, 0, pEnum));
}

BOOL CswDirectory::SetID (REFCLSID clsid)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->SetClass (clsid));
}

BOOL CswDirectory::SetElementTimes(
	CUniversalText utName,   //Pointer to name of element to be changed
	FILETIME const *pctime,  //New creation time for element, or NULL
	FILETIME const *patime,  //New access time for element, or NULL
	FILETIME const *pmtime   //New modification time for element, or NULL
	)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->SetElementTimes (utName, pctime, patime, pmtime));
}

BOOL CswDirectory::Stat (STATSTG *pstatstg,	//Location for STATSTG structure
			DWORD grfStatFlag //Values taken from the STATFLAG enumeration
	)
{
	if (!m_pStorage)
		return FALSE;
	return SUCCEEDED(m_pStorage->Stat (pstatstg, grfStatFlag));
}


BOOL CswDirectory::OpenDirVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswDirectory& swDir)
{
	return OpenDir (NameVirtualToReal (utName), grfMode, swDir);
}

BOOL CswDirectory::OpenFileVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswFile& swFile)
{
	return OpenFile (NameVirtualToReal (utName), grfMode, swFile);
}

BOOL CswDirectory::DestroyElementVN (IN CUniversalText utName)
{
	BOOL fr;
	if (fr = DestroyElement (NameVirtualToReal (utName)))
		DeleteVNMapping (utName);
	return fr;
}

BOOL CswDirectory::RenameElementVN (IN CUniversalText utOldName, IN CUniversalText utNewName)
{
	BOOL fr;
	if (fr = RenameElement (NameVirtualToReal (utOldName), NameVirtualToReal (utNewName)))
		DeleteVNMapping (utOldName);
	else
		DeleteVNMapping (utNewName);
	return fr;
}

BOOL CswDirectory::MoveElementToVN (IN CUniversalText utName,  
									IN CswDirectory& swDirDest,	
									IN CUniversalText utNewName,
									IN DWORD grfFlags )
{
	BOOL fr;
	if (fr = MoveElementTo (NameVirtualToReal (utName), swDirDest, 
		swDirDest.NameVirtualToReal (utNewName), grfFlags))
		DeleteVNMapping (utName);
	else
		swDirDest.DeleteVNMapping (utNewName);
	return fr;
}

BOOL CswDirectory::SetElementTimesVN(
	CUniversalText utName, 
	FILETIME const *pctime,
	FILETIME const *patime,
	FILETIME const *pmtime 
	)
{
	return SetElementTimes (NameVirtualToReal (utName), pctime, patime, pmtime);
}

CUniversalText CswDirectory::ChangeVirtualNamesMapFile (CUniversalText utReal)
{
	CUniversalText utOld = m_utMapFile;
	m_utMapFile = utReal;
	return utOld;
}

CUniversalText CswDirectory::NameVirtualToReal (CUniversalText utVirt)
{
	CUniversalText utReal; 
	UINT uHashKey = utVirt.GetHashKey ();
	m_mpR2V[uHashKey] = utVirt;
	utReal.Format ("%#.8x", uHashKey);
	return utReal;
};

CUniversalText CswDirectory::NameRealToVirtual (CUniversalText utReal)
{
	UINT uHashKey;
	if (!sscanf (utReal, "0x%8x", &uHashKey))
		return NULLSTRING;
	// do lookup here
	CUniversalText *putVirt = m_mpR2V.Lookup (uHashKey);
	if (!putVirt)
		return NULLSTRING;
	return *putVirt;
}

void CswDirectory::AddVNMapping(CUniversalText utVirtual)
{
	UINT uHashKey = utVirtual.GetHashKey ();
	m_mpR2V[uHashKey] = utVirtual;
}

void CswDirectory::DeleteVNMapping(CUniversalText utVirtual)
{
	UINT uHashKey = utVirtual.GetHashKey ();
	m_mpR2V.UnSet (uHashKey);
}

void CswDirectory::PostAttach()
{
	SWFILE swMapFile;
	if (OpenFile (m_utMapFile, STGM_READ | STGM_SHARE_EXCLUSIVE, swMapFile))
	{
		//load map
		CUniversalText utMap;
		if (utMap.LoadAsPlain (swMapFile))
		{
			CswUTArray arutNames;
			utMap.Explode ("\n", arutNames, TRUE);
			CUniversalText utVN;
			while (arutNames.Pop (utVN))
				NameVirtualToReal (utVN);
		}
		swMapFile.Close ();
	}
}

void CswDirectory::PreDetach()
{
	SWFILE swMapFile;
	m_mpOpened.Clear(); // automatic releases
	if (m_mpR2V.Count () && 
		OpenFile (m_utMapFile, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 
		swMapFile))
	{
		//save map
		CswUTArray arutNames;
		for (CUniversalText* putVN = m_mpR2V.Reset (); putVN; putVN = m_mpR2V.Next ())
		{
			arutNames.Push (*putVN);
		}		
		CUniversalText utMap = arutNames.Implode ("\n", TRUE);
		utMap.SaveAsPlain (swMapFile);
		swMapFile.Close ();
	}
}

