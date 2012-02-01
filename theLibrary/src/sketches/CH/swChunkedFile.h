#pragma once
#include "file.h"

//#pragma pack(push, 8)
typedef struct SswChunkInfo
{
	BYTE rgbType[3];		// Сигнатура куска
	BYTE rgfFlags;			// Служебные флаги куска
	DWORD cbLength;			// Длина этого куска
	DWORD cbDataLen;		// Длина записанных данных в куске
	DWORD dwNext;			// Следующей кусок фрагмента
	
	void SetType (LPVOID pvType)
	{
		memcpy (rgbType, pvType, sizeof (rgbType)); 
	}

	BOOL IsTypeOf (LPVOID pvType)
	{
		return (memcmp (rgbType, pvType, sizeof (rgbType)) == 0); 
	}
} SWCHUNKINFO, *LPSWCHUNKINFO;
//#pragma pack(pop)

enum SWCHUNK_FLAGS
{
	CHF_DEAD		= 0x01,		// Этот кусок удалён (труп)
	CHF_CONTINUE	= 0x02		// Этот кусок является продолжением цепочки (не первый)
};

class CswChunkedFile : public  CswFile
{
public:
	CswChunkedFile(void);
	virtual ~CswChunkedFile(void);

	// проверить формат и сдвинуться на первый кусок
	BOOL InitChunked (BOOL fInitIfNew = TRUE);
	
	// вычитать инфу о любом куске
	BOOL GetChunkInfoAny (OUT LPSWCHUNKINFO lpInfo);

	// вычитать инфу о куске, пропускаются составляющие цепочек и трупы
	BOOL GetChunkInfo (OUT LPSWCHUNKINFO lpInfo);

	// положить инфу о куске
	BOOL WriteChunkInfo (IN LPSWCHUNKINFO lpInfo);
	
	// записать цепочку данных, возможно фрагментированную
	DWORD WriteChain (
		IN LPVOID pvBuff,				// источник для записи
		IN DWORD cbLength,				// сколько байт записывать
		IN DWORD cbMinFragLen,			// минимальный размер фрагмента данных
		IN LPSWCHUNKINFO pInfo,			// имеет значение только тип куска, остальные поля игнорируются
		OUT PDWORD pcFragments			// число фрагментов (можно оставить NULL)
	);

	// not impl
	DWORD GetChainLength (
		BOOL fReadInfo = TRUE,			// читать инфу или это уже сделано
		LPSWCHUNKINFO lpInfo = NULL,	// вычитанная инфа, если сказано "читать" - это может быть NULL 
		OUT PDWORD pcFragments = NULL	// число фрагментов (можно оставить NULL)
		);

	// not impl
	DWORD ReadChain (
		IN LPVOID pvBuff,				// приёмник для чтения достатоных размеров
		IN BOOL fReadInfo = TRUE, 
		LPSWCHUNKINFO lpInfo = NULL,
		OUT PDWORD pcFragments = NULL	// число фрагментов (можно оставить NULL)
	);
	
	// вычитать данные куска
	//   Если fReadInfo == TRUE, то инфа о куске ещё не вычитана. lpInfo опционально.
	//   Иначе надо давать уже вычитанную lpInfo.
	BOOL ReadChunk (OUT LPVOID pvBuff, IN BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);
	
	// записать кусок в текущую позицию
	DWORD WriteChunk (IN LPSWCHUNKINFO lpInfo, IN LPVOID pvBuff);

	// переход к следующему куску; параметры см. выше
	BOOL ChunkAdvance (BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);
	
	// переход к следующему фрагменту цепочки; параметры см. выше
	BOOL ChainedChunkAdvance (BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);

	// переход к первому куску
	DWORD SeekToFirstChunk ();

	// получить смещение мёртвого куска длиной минимум (dwLength) байт;
	//   ищет, начиная с текущей позиции. Не изменяет позицию, но читает, хоть и немного.
	BOOL FindDiscarded (IN DWORD dwLength, OUT PDWORD pdwOffset, OUT PDWORD pdwLength);


	// является ли кусок lpInfo трупом?
	virtual BOOL IsChunkDiscardable (LPSWCHUNKINFO lpInfo);

	// пометить кусок под курсором как труп
	virtual BOOL MarkChunkDiscarded (LPSWCHUNKINFO lpInfo);

	// FIXME - никаких специфичных механизмов ещё нет механизмов
	// замочить кусок 
	//   если fDecrease == TRUE, то уменишить файл на размер куска
	//     cMaxRealloc в этом случае - максимально допустимое число перемещений.
	//   если fDecrease == FALSE, то кусок просто метится как удалённый
	BOOL DiscardChunk (IN BOOL fDecrease = TRUE, IN DWORD cMaxRealloc = 0);

private:
	DWORD m_dw1stChunkOffset;
};

typedef CswChunkedFile SWCHFILE, *LPSWCHFILE;