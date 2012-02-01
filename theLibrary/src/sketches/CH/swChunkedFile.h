#pragma once
#include "file.h"

//#pragma pack(push, 8)
typedef struct SswChunkInfo
{
	BYTE rgbType[3];		// ��������� �����
	BYTE rgfFlags;			// ��������� ����� �����
	DWORD cbLength;			// ����� ����� �����
	DWORD cbDataLen;		// ����� ���������� ������ � �����
	DWORD dwNext;			// ��������� ����� ���������
	
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
	CHF_DEAD		= 0x01,		// ���� ����� ����� (����)
	CHF_CONTINUE	= 0x02		// ���� ����� �������� ������������ ������� (�� ������)
};

class CswChunkedFile : public  CswFile
{
public:
	CswChunkedFile(void);
	virtual ~CswChunkedFile(void);

	// ��������� ������ � ���������� �� ������ �����
	BOOL InitChunked (BOOL fInitIfNew = TRUE);
	
	// �������� ���� � ����� �����
	BOOL GetChunkInfoAny (OUT LPSWCHUNKINFO lpInfo);

	// �������� ���� � �����, ������������ ������������ ������� � �����
	BOOL GetChunkInfo (OUT LPSWCHUNKINFO lpInfo);

	// �������� ���� � �����
	BOOL WriteChunkInfo (IN LPSWCHUNKINFO lpInfo);
	
	// �������� ������� ������, �������� �����������������
	DWORD WriteChain (
		IN LPVOID pvBuff,				// �������� ��� ������
		IN DWORD cbLength,				// ������� ���� ����������
		IN DWORD cbMinFragLen,			// ����������� ������ ��������� ������
		IN LPSWCHUNKINFO pInfo,			// ����� �������� ������ ��� �����, ��������� ���� ������������
		OUT PDWORD pcFragments			// ����� ���������� (����� �������� NULL)
	);

	// not impl
	DWORD GetChainLength (
		BOOL fReadInfo = TRUE,			// ������ ���� ��� ��� ��� �������
		LPSWCHUNKINFO lpInfo = NULL,	// ���������� ����, ���� ������� "������" - ��� ����� ���� NULL 
		OUT PDWORD pcFragments = NULL	// ����� ���������� (����� �������� NULL)
		);

	// not impl
	DWORD ReadChain (
		IN LPVOID pvBuff,				// ������� ��� ������ ���������� ��������
		IN BOOL fReadInfo = TRUE, 
		LPSWCHUNKINFO lpInfo = NULL,
		OUT PDWORD pcFragments = NULL	// ����� ���������� (����� �������� NULL)
	);
	
	// �������� ������ �����
	//   ���� fReadInfo == TRUE, �� ���� � ����� ��� �� ��������. lpInfo �����������.
	//   ����� ���� ������ ��� ���������� lpInfo.
	BOOL ReadChunk (OUT LPVOID pvBuff, IN BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);
	
	// �������� ����� � ������� �������
	DWORD WriteChunk (IN LPSWCHUNKINFO lpInfo, IN LPVOID pvBuff);

	// ������� � ���������� �����; ��������� ��. ����
	BOOL ChunkAdvance (BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);
	
	// ������� � ���������� ��������� �������; ��������� ��. ����
	BOOL ChainedChunkAdvance (BOOL fReadInfo = TRUE, LPSWCHUNKINFO lpInfo = NULL);

	// ������� � ������� �����
	DWORD SeekToFirstChunk ();

	// �������� �������� ������� ����� ������ ������� (dwLength) ����;
	//   ����, ������� � ������� �������. �� �������� �������, �� ������, ���� � �������.
	BOOL FindDiscarded (IN DWORD dwLength, OUT PDWORD pdwOffset, OUT PDWORD pdwLength);


	// �������� �� ����� lpInfo ������?
	virtual BOOL IsChunkDiscardable (LPSWCHUNKINFO lpInfo);

	// �������� ����� ��� �������� ��� ����
	virtual BOOL MarkChunkDiscarded (LPSWCHUNKINFO lpInfo);

	// FIXME - ������� ����������� ���������� ��� ��� ����������
	// �������� ����� 
	//   ���� fDecrease == TRUE, �� ��������� ���� �� ������ �����
	//     cMaxRealloc � ���� ������ - ����������� ���������� ����� �����������.
	//   ���� fDecrease == FALSE, �� ����� ������ ������� ��� ��������
	BOOL DiscardChunk (IN BOOL fDecrease = TRUE, IN DWORD cMaxRealloc = 0);

private:
	DWORD m_dw1stChunkOffset;
};

typedef CswChunkedFile SWCHFILE, *LPSWCHFILE;