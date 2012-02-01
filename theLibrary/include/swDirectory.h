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

	// открыть/создать файл хранилища
	BOOL OpenHDD (IN CUniversalText utName,	/* файл хранилища */
		IN DWORD grfMode,						/* (STGM_READ + STGM_SHARE_DENY_NONE) || 
											 (STGM_WRITE + STGM_SHARE_EXCLUSIVE) || 
											 (STGM_READWRITE + STGM_SHARE_EXCLUSIVE)
											 STGM_CREATE -- создать, иначе открыть */
		IN DWORD dwImplType					/* IT_COMSTG (биллгэйтсовая) || IT_SSF (наша) */
		);
	
	// закрыть этот объект (типа Release)
	BOOL Close ();

	// открыть/создать вложенный каталог (параметры такие же, как для OpenHDD)
	//   для открытия надо говорить grfMode = STGM_SHARE_EXCLUSIVE
	BOOL OpenDir (IN CUniversalText utName, IN DWORD grfMode, OUT CswDirectory& swDir);	
	// открыть/создать вложенный каталог с виртуальным именем 
	//   для открытия надо говорить grfMode = STGM_SHARE_EXCLUSIVE
	BOOL OpenDirVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswDirectory& swDir);

	// открыть/создать вложенный файл (параметры такие же, как для OpenHDD)
	BOOL OpenFile (IN CUniversalText utName, IN DWORD grfMode, OUT CswFile& swFile);	
	// открыть/создать вложенный файл с виртуальным именем 
	BOOL OpenFileVN (IN CUniversalText utName, IN DWORD grfMode, OUT CswFile& swFile);
	// сказать, что открытое дитё уже закрыто. (необязательно, но желательно)
	void ElementClosed (IN CUniversalText utName);
	void ElementClosedVN (IN CUniversalText utName);

	// замочить кого-то вложенного
	BOOL DestroyElement (IN CUniversalText utName);
	// замочить кого-то вложенного с виртуальным именем
	BOOL DestroyElementVN (IN CUniversalText utName);
	
	// переименовать кого-то вложенного
	BOOL RenameElement (IN CUniversalText utOldName, IN CUniversalText utNewName);
	// переименовать кого-то вложенного с виртуальным именем
	BOOL RenameElementVN (IN CUniversalText utOldName, IN CUniversalText utNewName);

	// копировать всё содержимое этого объекта куда-то ещё
	// последние три параметра нужны, когда кого-то из вложенностей копировать не хочется.
	BOOL CopyTo (CswDirectory& swDirDest,			// Куда копировать
				 DWORD ciidExclude = 0,				//Number of elements in rgiidExclude
				 IID const *rgiidExclude = NULL,	//Array of interface identifiers (IIDs)
				 SNB snbExclude = NULL				//Pointer to a block of stream names in the storage object
		);
	
	// переместить/копировать дитё куда-то ещё. Не пользовать для простого переименования!
	BOOL MoveElementTo (IN CUniversalText utName,   // Имя дитя
						IN CswDirectory& swDirDest,	// Куда копировать
						IN CUniversalText utNewName,// Как оно будет называться на новом месте
						IN DWORD grfFlags           // Копировать (STGMOVE_COPY) или перенести (STGMOVE_MOVE)
		);
	// переместить/копировать дитё с виртуальным именем куда-то ещё. Не пользовать для простого переименования!
	BOOL MoveElementToVN (IN CUniversalText utName,   // Имя дитя
						IN CswDirectory& swDirDest,	// Куда копировать
						IN CUniversalText utNewName,// Как оно будет называться на новом месте
						IN DWORD grfFlags           // Копировать (STGMOVE_COPY) или перенести (STGMOVE_MOVE)
		);

	
	// получить интерфейс-енумератор чилдов
	BOOL EnumElements (OUT IEnumSTATSTG** pEnum);

	// присвоить этому объекту CLSID (по дефолту - CLSID_NULL). Получить - по Stat.
	BOOL SetID (REFCLSID clsid);

	// изменить время создания/доступа/модификации дитя
	BOOL SetElementTimes(
		CUniversalText utName,   //Pointer to name of element to be changed
		FILETIME const *pctime,  //New creation time for element, or NULL
		FILETIME const *patime,  //New access time for element, or NULL
		FILETIME const *pmtime   //New modification time for element, or NULL
		);
	// изменить время создания/доступа/модификации дитя с виртуальным именем
	BOOL SetElementTimesVN(
		CUniversalText utName,   //Pointer to name of element to be changed
		FILETIME const *pctime,  //New creation time for element, or NULL
		FILETIME const *patime,  //New access time for element, or NULL
		FILETIME const *pmtime   //New modification time for element, or NULL
		);
	
	// Получить характеритики этого объекта (STATSTG-структуру)
	BOOL Stat (STATSTG *pstatstg,	//Location for STATSTG structure
			   DWORD grfStatFlag = STATFLAG_DEFAULT //Values taken from the STATFLAG enumeration
		);


	// Присоединить хранилище
	BOOL AttachStorage (IN IStorage* pStorage);	
	// Отсоединить хранилище
	BOOL DetachStorage (OUT IStorage** ppStorage);
	// Этот объект позовёт Release() на указанном интерфейсе вместе с Release'ом внутреннего
	BOOL BindToParent (IN IUnknown* pUnkParent);
	// Принудительно освободить прибинденного парента
	BOOL ReleaseParent ();

	// Изменить имя файла, в котором хранится карта реальных/виртуальных имён файлов
	//  - возвращает старое имя этого файла
	CUniversalText ChangeVirtualNamesMapFile (CUniversalText utReal);
	// Получить реальное имя файла из виртуального
	CUniversalText NameVirtualToReal (CUniversalText utVirt); 
	// Получить виртуальное имя файла из реального
	//   - возвращает пустую, если указано имя файла с картой
	CUniversalText NameRealToVirtual (CUniversalText utReal); 
	// Добавить запись в таблицу виртуальных имён
	void AddVNMapping (CUniversalText utVirtual);
	// Удалить запись из таблицы виртуальных имён
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