#pragma once
#include "file.h"
#include "swMap.h"

#pragma pack(push, 2)
typedef struct SWBRIEFCHAININFO
{
	BYTE rgbType[3];		// ��������� �������
	BYTE rgfFlags;			// ��������� ����� �������
	DWORD dwNextChain;		// �������� ��������� �������
	DWORD cbUsed;			// ����� ���� ������ ���� �������
	
	// ���������� ��� ������� � ������� CUniversalText
	inline CUniversalText GetType ()
	{
		CHAR szType[] = { rgbType[0], rgbType[1], rgbType[2], 0 };
		return szType;
	}
	
	// ������������� ��� ������� � ������� CUniversalText
	inline void SetType (CUniversalText utType)
	{
		memcpy (rgbType, (LPSTR)utType, sizeof (rgbType));
	}
	
	// ��������� ��� ������� � ������� CUniversalText
	inline BOOL IsTypeOf (CUniversalText utType)
	{
		return (memcmp (rgbType, (LPSTR)utType, sizeof (rgbType)) == 0);
	}
} SWBRIEFCHAININFO;

typedef struct SWCHNODEINFO
{
	DWORD cbNodeLength;		// ����� ��������� �������
	DWORD dwNextNode;		// �������� ���������� ��������� �������
} SWCHNODEINFO;

typedef union SWCHAININFO
{
	SWBRIEFCHAININFO brief;
	struct FULLINFO
	{
		SWBRIEFCHAININFO brief;
		SWCHNODEINFO node;
	} full;
} SWFULLCHAININFO;
#pragma pack(pop)

enum SWCHAIN_FLAGS
{
	CHF_DEAD		= 0x01		// ����� ������� ������ (����)
};

class CswTaggedChainsFile : public  CswFile
{
protected:
	struct SWCNODELISTITEM { DWORD dwOffset; SWCHNODEINFO info; };
	typedef CswMap<CUniversalText, DWORD> SWCHAINFILTER;
	typedef CSWOneWayList< SWCNODELISTITEM > SWCHNODELIST;
	enum SWCHAININFOTYPE { CIT_NONE, CIT_BRIEF, CIT_NODE, CIT_FULL };
	
public:
	CswTaggedChainsFile(void);
	virtual ~CswTaggedChainsFile(void);

	// �������� ��� ������� � �������
	void AddChainTypeFilter (CUniversalText utType, DWORD dwCookie = 0);	
	// ������� ��� ������� � �������
	void RemoveChainTypeFilter (CUniversalText utType);
	// �������� ������ �������
	void ClearChainFilter ();


	// ��������� ������ � �������� ������ �� ������ �������
	//   ���� fUseFilter == TRUE, �� ����� ����� ��������������, 
	//     ���� �� ����� ������� ������� � �����, ������� ���� � �������
	BOOL StartChainsWalker (BOOL fUseFilter = TRUE, BOOL fInitIfNew = TRUE);

	// �����������, ��� ��� ������� ��� �������� ������������� ���������.
	// ��������� ������ �� ������ ������� ������ ����, ���� ��� ������� �� �����������.
	//   ���� ������� ��� utType ������, �� ������������ ������ �����
	//   ��������� ����������, ���� ��������� ����� �����
	BOOL AssertCurChainType (CUniversalText utType = NULLSTRING);
	
	// ���������� ������ �� ��������� ������� ��������� ���� (��� �� ������� �����)
	//   ��������� ����������, ���� ��������� ����� �����
	BOOL WalkChain (CUniversalText utType = NULLSTRING);

	// ���������� ��� ������� ��� ��������
	//   ��������� ����, ���� ������ ������ ����� �����
	CUniversalText GetCurChainType ();

	// ���������, �������� �� ��� ������� ������� ����� �� �������� � �������
	inline BOOL IsCurChainFiltered ();

	// ���������� ����� ������� ��� ��������
	//   ��������� 0, ���� ������ ������ ����� �����
	DWORD GetCurChainLength ();

	// ������� ������� ������� ��� ������/������ (������ ��� ��� ������ ����)
	BOOL OpenCurrentChain ();
	// ������� �������� �������
	void CloseCurrenChain ();

	//������ �� �������
	DWORD ChainRead (LPVOID pvBuff, DWORD cbToRead);
	//������ � �������
	DWORD ChainWrite (LPVOID pvBuff, DWORD cbToRead);

protected:
	DWORD m_dw1stChunkOffset;		// �������� ������ �������
	SWCHAINFILTER* m_pswFilter;		// ������� �������� �������
private:
	SWCHAININFO* m_pInfoCache;		// ��� ���������� ���������� � �������/���������
	enum SWCHAININFOTYPE m_enInfoCacheType;	// ��� ���������� ���������� � ����
	DWORD m_dwCachedChainOffset;	// �������� ������ (����� ����������) �������, ���������� � ������� ��������� � ����
	DWORD m_dwCachedNodeOffset;		// �������� ������ (����� ����������) ���������, ���������� � ������� ��������� � ����
	
	// ������� ���� ���������� ���������� � �������/���������
	inline void ClearInfoCache ();
	// ������ ���������� � ������� � ���
	inline BOOL ReadInfoToCache (enum SWCHAININFOTYPE enType);
	// ������ ���������� � ������� � ���
	inline BOOL WriteInfoToCache (enum SWCHAININFOTYPE enType);
protected:
	SWCHNODELIST m_lsNodes;			// ������ ���������� ������� �������� �������
	UINT m_uNode;					// ������� �������� �������
	DWORD m_dwNodeOffset;			// ������� ������ �������� ���������

	// ������������� �� ��������� ��������
	BOOL WalkNode (); 
	// ������������ �� ��������� ������� (��� �������� ����)
	BOOL WalkChain_noTypeCheck ();
};

typedef CswTaggedChainsFile SWCHFILE, *LPSWCHFILE;