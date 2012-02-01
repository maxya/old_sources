#pragma once
#include <atlbase.h>
#include "UniversalText.h"
#include "File.h"

enum IMPL_TYPE
{
	IT_COMSTG,
	IT_SSF
};

#define STGM_WANNAREAD		STGM_READ | STGM_SHARE_DENY_WRITE
#define STGM_WANNAWRITE		STGM_WRITE | STGM_SHARE_EXCLUSIVE
#define STGM_WANNAALL		STGM_READWRITE | STGM_SHARE_EXCLUSIVE

class CswDirectory
{
public:
	CswDirectory(void);
	CswDirectory(CswDirectory& swDir);
	CswDirectory(IStorage* pStorage);
	virtual ~CswDirectory(void);
	CswDirectory& operator = (CswDirectory& swDir);
	CswDirectory& operator = (IStorage* pStorage);

	// �������/������� ���� ���������
	BOOL OpenHDD (IN CUniversalText utName,	/* ���� ��������� */
		IN DWORD grfMode,						/* (STGM_READ + STGM_SHARE_DENY_NONE) || 
											 (STGM_WRITE + STGM_SHARE_EXCLUSIVE) || 
											 (STGM_READWRITE + STGM_SHARE_EXCLUSIVE)
											 STGM_CREATE -- �������, ����� ������� */
		IN DWORD dwImplType					/* IT_COMSTG (�������������) || IT_SSF (����) */
		);
	
	// ������� ���� ������ (���� Release)
	BOOL Close ();

	// �������/������� ��������� ������� (��������� ����� ��, ��� ��� OpenHDD)
	//   ��� �������� ���� �������� grfMode = STGM_SHARE_EXCLUSIVE
	BOOL OpenDir (IN CUniversalText utName, IN DWORD grfMode, OUT CswDirectory& swDir);	
	// �������/������� ��������� ������� � ����������� ������ 
	//   ��� �������� ���� �������� grfMode = STGM_SHARE_EXCLUSIVE
	BOOL OpenDirVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswDirectory& swDir);

	// �������/������� ��������� ���� (��������� ����� ��, ��� ��� OpenHDD)
	BOOL OpenFile (IN CUniversalText utName, IN DWORD grfMode, OUT CswFile& swFile);	
	// �������/������� ��������� ���� � ����������� ������ 
	BOOL OpenFileVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswFile& swFile);
	// �������, ��� �������� ��� ��� �������. (�������������, �� ����������)
	void ElementClosed (IN CUniversalText utName);
	void ElementClosedVN (IN CUniversalText utName);

	// �������� ����-�� ����������
	BOOL DestroyElement (IN CUniversalText utName);
	// �������� ����-�� ���������� � ����������� ������
	BOOL DestroyElementVN (IN CUniversalText utName);
	
	// ������������� ����-�� ����������
	BOOL RenameElement (IN CUniversalText utOldName, IN CUniversalText utNewName);
	// ������������� ����-�� ���������� � ����������� ������
	BOOL RenameElementVN (IN CUniversalText utOldName, IN CUniversalText utNewName);

	// ���������� �� ���������� ����� ������� ����-�� ���
	// ��������� ��� ��������� �����, ����� ����-�� �� ������������ ���������� �� �������.
	BOOL CopyTo (CswDirectory& swDirDest,			// ���� ����������
				 DWORD ciidExclude = 0,				//Number of elements in rgiidExclude
				 IID const *rgiidExclude = NULL,	//Array of interface identifiers (IIDs)
				 SNB snbExclude = NULL				//Pointer to a block of stream names in the storage object
		);
	
	// �����������/���������� ��� ����-�� ���. �� ���������� ��� �������� ��������������!
	BOOL MoveElementTo (IN CUniversalText utName,   // ��� ����
						IN CswDirectory& swDirDest,	// ���� ����������
						IN CUniversalText utNewName,// ��� ��� ����� ���������� �� ����� �����
						IN DWORD grfFlags           // ���������� (STGMOVE_COPY) ��� ��������� (STGMOVE_MOVE)
		);
	// �����������/���������� ��� � ����������� ������ ����-�� ���. �� ���������� ��� �������� ��������������!
	BOOL MoveElementToVN (IN CUniversalText utName,   // ��� ����
						IN CswDirectory& swDirDest,	// ���� ����������
						IN CUniversalText utNewName,// ��� ��� ����� ���������� �� ����� �����
						IN DWORD grfFlags           // ���������� (STGMOVE_COPY) ��� ��������� (STGMOVE_MOVE)
		);

	
	// �������� ���������-���������� ������
	BOOL EnumElements (OUT IEnumSTATSTG** pEnum);

	// ��������� ����� ������� CLSID (�� ������� - CLSID_NULL). �������� - �� Stat.
	BOOL SetID (REFCLSID clsid);

	// �������� ����� ��������/�������/����������� ����
	BOOL SetElementTimes(
		CUniversalText utName,   //Pointer to name of element to be changed
		FILETIME const *pctime,  //New creation time for element, or NULL
		FILETIME const *patime,  //New access time for element, or NULL
		FILETIME const *pmtime   //New modification time for element, or NULL
		);
	// �������� ����� ��������/�������/����������� ���� � ����������� ������
	BOOL SetElementTimesVN(
		CUniversalText utName,   //Pointer to name of element to be changed
		FILETIME const *pctime,  //New creation time for element, or NULL
		FILETIME const *patime,  //New access time for element, or NULL
		FILETIME const *pmtime   //New modification time for element, or NULL
		);
	
	// �������� ������������� ����� ������� (STATSTG-���������)
	BOOL Stat (STATSTG *pstatstg,	//Location for STATSTG structure
			   DWORD grfStatFlag = STATFLAG_DEFAULT //Values taken from the STATFLAG enumeration
		);


	// ������������ ���������
	BOOL AttachStorage (IN IStorage* pStorage);	
	// ����������� ���������
	BOOL DetachStorage (OUT IStorage** ppStorage);
	// ���� ������ ������ Release() �� ��������� ���������� ������ � Release'�� �����������
	BOOL BindToParent (IN IUnknown* pUnkParent);
	// ������������� ���������� ������������� �������
	BOOL ReleaseParent ();

	// �������� ��� �����, � ������� �������� ����� ��������/����������� ��� ������
	//  - ���������� ������ ��� ����� �����
	CUniversalText ChangeVirtualNamesMapFile (CUniversalText utReal);
	// �������� �������� ��� ����� �� ������������
	CUniversalText NameVirtualToReal (CUniversalText utVirt); 
	// �������� ����������� ��� ����� �� ���������
	//   - ���������� ������, ���� ������� ��� ����� � ������
	CUniversalText NameRealToVirtual (CUniversalText utReal); 
	// �������� ������ � ������� ����������� ���
	void AddVNMapping (CUniversalText utVirtual);
	// ������� ������ �� ������� ����������� ���
	void DeleteVNMapping (CUniversalText utVirtual);

	operator IStorage* ()	{ return m_pStorage; }

protected:
	struct OPEN_INFO : public IUnknown
	{
		IUnknown* m_pChild;
		LONG m_cRefs;
		

		OPEN_INFO () : 
			m_pChild (NULL), m_cRefs (0)
		{ 
		}

		~OPEN_INFO ()	{ ReleaseChild (); }
		
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject)
		{
			if (iid == IID_IUnknown)
				*ppvObject = static_cast<IUnknown*>(this);
			else
			{
				*ppvObject = NULL;
				return E_NOINTERFACE;
			}
			AddRef ();
			return S_OK;
		}
		
		ULONG STDMETHODCALLTYPE AddRef(void)
		{
			return InterlockedIncrement (&m_cRefs);
		}
		
		ULONG STDMETHODCALLTYPE Release(void)
		{
			if (!InterlockedDecrement (&m_cRefs))
			{
				ReleaseChild ();
				return 0;
			}
			return m_cRefs;
		}

		OPEN_INFO& operator = (const OPEN_INFO& info)
		{
			ReleaseChild ();
			AttachChild(info.m_pChild);
			return (*this);
		}
		
		BOOL AttachChild (IUnknown* child) 
		{ 
			ReleaseChild ();
			if (!child)
				return FALSE;
			m_pChild = child;
			child->AddRef();
			return TRUE;
		}
		void ReleaseChild ()
		{
			if (m_pChild) 
				m_pChild->Release(); 
			m_pChild = NULL;
		}
	};

	IStorage* m_pStorage;
	//IUnknown* m_pUnkParent;
	CUniversalText m_utMapFile;
	CswMap<UINT, CUniversalText> m_mpR2V;
	CswMap<CUniversalText, OPEN_INFO> m_mpOpened;
	CswArray< CComPtr<IUnknown> > m_arBound;

	void Init ();
	void CleanUp ();
	virtual void PostAttach ();
	virtual void PreDetach ();
};

typedef CswDirectory CSWDirectory, CSWDir, CswDir, SWDIR, *LPSWDIR;