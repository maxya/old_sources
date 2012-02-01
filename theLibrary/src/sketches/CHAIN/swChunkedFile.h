#pragma once
#include "file.h"
#include "swMap.h"

#pragma pack(push, 2)
typedef struct SWBRIEFCHAININFO
{
	BYTE rgbType[3];		// Сигнатура цепочки
	BYTE rgfFlags;			// Служебные флаги цепочки
	DWORD dwNextChain;		// Смещение следующей цепочки
	DWORD cbUsed;			// Число байт данных всей цепочки
	
	// Возвращает тип цепочки в формате CUniversalText
	inline CUniversalText GetType ()
	{
		CHAR szType[] = { rgbType[0], rgbType[1], rgbType[2], 0 };
		return szType;
	}
	
	// Устанавливает тип цепочки в формате CUniversalText
	inline void SetType (CUniversalText utType)
	{
		memcpy (rgbType, (LPSTR)utType, sizeof (rgbType));
	}
	
	// Проверяет тип цепочки в формате CUniversalText
	inline BOOL IsTypeOf (CUniversalText utType)
	{
		return (memcmp (rgbType, (LPSTR)utType, sizeof (rgbType)) == 0);
	}
} SWBRIEFCHAININFO;

typedef struct SWCHNODEINFO
{
	DWORD cbNodeLength;		// Длина фрагмента цепочки
	DWORD dwNextNode;		// Смещение следующего фрагмента цепочки
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
	CHF_DEAD		= 0x01		// Этота цепочка удалёна (труп)
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

	// добавить тип цепочки к фильтру
	void AddChainTypeFilter (CUniversalText utType, DWORD dwCookie = 0);	
	// удалить тип цепочки к фильтру
	void RemoveChainTypeFilter (CUniversalText utType);
	// очистить фильтр цепочек
	void ClearChainFilter ();


	// проверить формат и сдвинуть курсор на первую цепочку
	//   если fUseFilter == TRUE, то сдвиг будет осуществляться, 
	//     пока не будет найдена цепочка с типом, который есть в фильтре
	BOOL StartChainsWalker (BOOL fUseFilter = TRUE, BOOL fInitIfNew = TRUE);

	// гарантирует, что тип цепочки под курсором соответствует заданному.
	// сдвингает курсор на первую цепочку такого типа, если это условие не выполняется.
	//   если заданый тип utType пустой, то используется фильтр типов
	//   результат негативный, если достигнут конец файла
	BOOL AssertCurChainType (CUniversalText utType = NULLSTRING);
	
	// перемещает курсор на следующую цепочку заданного типа (или из фильтра типов)
	//   результат негативный, если достигнут конец файла
	BOOL WalkChain (CUniversalText utType = NULLSTRING);

	// возвращает тип цепочки под курсором
	//   результат пуст, если курсор достиг конца файла
	CUniversalText GetCurChainType ();

	// проверяет, является ли тип текущей цепочки одним из заданных в фильтре
	inline BOOL IsCurChainFiltered ();

	// возвращает длину цепочки под курсором
	//   результат 0, если курсор достиг конца файла
	DWORD GetCurChainLength ();

	// открыть текущую цепочку для чтения/записи (смотря как был открыт файл)
	BOOL OpenCurrentChain ();
	// закрыть открытую цепочку
	void CloseCurrenChain ();

	//Читать из цепочки
	DWORD ChainRead (LPVOID pvBuff, DWORD cbToRead);
	//Запись в цепочку
	DWORD ChainWrite (LPVOID pvBuff, DWORD cbToRead);

protected:
	DWORD m_dw1stChunkOffset;		// смещение первой цепочки
	SWCHAINFILTER* m_pswFilter;		// таблица фильтров цепочек
private:
	SWCHAININFO* m_pInfoCache;		// кэш вычитанной информации о цепочке/фрагменте
	enum SWCHAININFOTYPE m_enInfoCacheType;	// тип вычитанной информации в кэше
	DWORD m_dwCachedChainOffset;	// смещение начала (перед заголовком) цепочки, информация о которой находится в кэше
	DWORD m_dwCachedNodeOffset;		// смещение начала (перед заголовком) фрагмента, информация о котором находится в кэше
	
	// очистка кэша вычитанной информации о цепочке/фрагменте
	inline void ClearInfoCache ();
	// чтение информации о цепочке в кэш
	inline BOOL ReadInfoToCache (enum SWCHAININFOTYPE enType);
	// запись информации о цепочке в кэш
	inline BOOL WriteInfoToCache (enum SWCHAININFOTYPE enType);
protected:
	SWCHNODELIST m_lsNodes;			// список фрагментов текущей открытой цепочки
	UINT m_uNode;					// текущий фрагмент цепочки
	DWORD m_dwNodeOffset;			// позиция внутри текущего фрагмента

	// переместиться на следующий фрагмент
	BOOL WalkNode (); 
	// преместиться на следующую цепочку (без проверки типа)
	BOOL WalkChain_noTypeCheck ();
};

typedef CswTaggedChainsFile SWCHFILE, *LPSWCHFILE;