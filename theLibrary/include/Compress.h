// Compress.h: interface for the CSWCompress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined SW_COMPRESS_H__C600B8EA_3A1C_42B1_8C3D_7E8148ECC448__INCLUDED_
#define SW_COMPRESS_H__C600B8EA_3A1C_42B1_8C3D_7E8148ECC448__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <objidl.h>	// IStream declaration

#define N                4096   /* size of ring buffer */
#define F                  60   /* upper limit for match_length */
#define THRESHOLD       2   /* encode string into position and length
                                                   if match_length is greater than this */
#define NIL                     N       /* index for root of binary search trees */


#define M   15

/*      Q1 (= 2 to the M) must be sufficiently large, but not so
        large as the unsigned long 4 * Q1 * (Q1 - 1) overflows.  */

#define Q1  (1UL << M)
#define Q2  (2 * Q1)
#define Q3  (3 * Q1)
#define Q4  (4 * Q1)
#define MAX_CUM (Q1 - 1)

#define N_CHAR  (256 - THRESHOLD + F)
        /* character code = 0, 1, ..., N_CHAR - 1 */

#define WM_CODE WM_USER+1

class CswFile;
class CSWCompress 
{
public:
	CSWCompress ();
	virtual ~CSWCompress();

	// Encode
	DWORD Encode(CswFile *input,CswFile *out);
	// Decode
	void Decode(CswFile *input,CswFile *out);

	// Encode
	DWORD Encode(IStream* pInput,IStream* pOutput);
	// Decode
	void Decode(IStream* pInput, IStream* pOutput);

	// Enable notifications
	BOOL EnableNotify (IN HWND hWnd, IN UINT uMsg);
	// Disable notifications
	BOOL DisableNotify ();

	// Enable CRC calculations output. Call every Encode, if needed.
	BOOL SetCRCOutput (IN PDWORD pdwCRC_Before, PDWORD pdwCRC_After);
	
private:
	DWORD	CRC_after;
	DWORD	CRC_before;
	PDWORD m_pdwCRC_Before;
	PDWORD m_pdwCRC_After;
	
	HWND m_hwndNotify;
	UINT m_uMsg;
	IStream* m_pInput;
	IStream* m_pOutput;
	struct _SWCOMPRESS_STRUCT_28A10D6B_552C_42ad_8D1E_C57231F3F140
	{
		unsigned fNotify		: 1;
		unsigned fCRC_OutputSet	: 1;
	}m_bfFlags;
	
	void Init ();
	int mgetc();
	int mputc(int c);

	DWORD	inputcurrentPos;
	DWORD	inputmemsize;
	DWORD	outputcurrentPos;
	DWORD	outputmemsize;

	unsigned int  bufferp , maskp;
	unsigned int  bufferg, maskg;
	
	unsigned char  text_buf[N + F - 1];  
	
	int match_position, match_length,lson[N + 1], rson[N + 257], dad[N + 1];

	unsigned long int  textsize, codesize , printcount;
	void PutBit(int bit);
	void FlushBitBuffer(void);
	int GetBit(void);
	void InitTree(void);
	void InsertNode(int r);
	void DeleteNode(int p);

	unsigned long int  low, high, value ;
	int  char_to_sym[N_CHAR], sym_to_char[N_CHAR + 1];
	unsigned int
        sym_freq[N_CHAR + 1],  /* frequency for symbols */
        sym_cum[N_CHAR + 1],   /* cumulative freq for symbols */
        position_cum[N + 1];   /* cumulative freq for positions */

	int  shifts ; 

	void StartModel(void);  /* Initialize model */
	void UpdateModel(int sym);
	void Output(int bit);  /* Output 1 bit, followed by its complements */
	void EncodeChar(int ch);
	void EncodePosition(int position);
	void EncodeEnd(void);
	int BinarySearchSym(unsigned int x);
	int BinarySearchPos(unsigned int x);
	void StartDecode(void);
	int DecodeChar(void);
	int DecodePosition(void);
};

typedef CSWCompress SWCOMPRESS, *LPSWCOMPRESS;

#endif //!defined SW_COMPRESS_H__C600B8EA_3A1C_42B1_8C3D_7E8148ECC448__INCLUDED_