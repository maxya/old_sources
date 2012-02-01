// Compress.cpp: implementation of the CSWCompress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TheLibrary.h"
#include "Compress.h"
#include "File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSWCompress::CSWCompress()
{
	m_pInput = m_pOutput  = NULL;
	inputcurrentPos = outputcurrentPos = 0;
	m_bfFlags.fCRC_OutputSet = false;
	m_bfFlags.fNotify = false;
	Init ();	
}

void CSWCompress::Init ()
{
	textsize = 0; codesize = 0; printcount = 0;
	outputmemsize = inputmemsize = 0;
	shifts = 0; 
	low = 0;
	high = Q4;
	value = 0;
	bufferp = 0;
	bufferg = 0;
	maskp = 128;
	maskg = 0;
	CRC_after = CRC_before = 0;
}

CSWCompress::~CSWCompress()
{
	m_pInput = m_pOutput  = NULL;
	inputcurrentPos = outputcurrentPos = 0;
	textsize = 0; codesize = 0; printcount = 0;
	outputmemsize = inputmemsize = 0;
	
	shifts = 0; 

	low = 0;
	high = Q4;
	value = 0;
	
}

//////////////////////////////////////////////////////////////////////

BOOL CSWCompress::EnableNotify (IN HWND hWnd, IN UINT uMsg)
{
	m_hwndNotify = hWnd;
	m_uMsg = uMsg;
	m_bfFlags.fNotify = true;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL CSWCompress::DisableNotify ()
{
	m_bfFlags.fNotify = FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CSWCompress::SetCRCOutput (IN PDWORD pdwCRC_Before, PDWORD pdwCRC_After)
{
	m_pdwCRC_Before = pdwCRC_Before;
	m_pdwCRC_After = pdwCRC_After;
	m_bfFlags.fCRC_OutputSet = true;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::PutBit(int bit)  /* Output one bit (bit = 0,1) */
{
	
	
	if (bit) bufferp |= maskp;
	if ((maskp >>= 1) == 0)
	{
		mputc(bufferp);
		bufferp = 0;  maskp = 128;  codesize++;
	}
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::FlushBitBuffer(void)  /* Send remaining bits */
{
	int  i;
	for (i = 0; i < 7; i++) PutBit(0);
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::GetBit(void)  /* Get one bit (0 or 1) */
{
	
	if ((maskg >>= 1) == 0) {
		bufferg = mgetc();  maskg = 128;
	}
	return ((bufferg & maskg) != 0);
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::mputc(int c)
{
	unsigned char pTemp = (unsigned char)c;
	ULONG uWritten;
	m_pOutput->Write(&pTemp, sizeof(pTemp), &uWritten);
	CRC_after+=pTemp;
	return 0;
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::mgetc()
{
	unsigned char  ret;
	ULONG uRead;
	HRESULT hr = m_pInput->Read(&ret,sizeof(ret), &uRead);
	if (hr != S_OK)
		return EOF;
	CRC_before += ret;
	return (int)ret;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::InitTree(void)  /* Initialize trees */
{
        int  i;

        /* For i = 0 to N - 1, rson[i] and lson[i] will be the right and
           left children of node i.  These nodes need not be initialized.
           Also, dad[i] is the parent of node i.  These are initialized to
           NIL (= N), which stands for 'not used.'
           For i = 0 to 255, rson[N + i + 1] is the root of the tree
           for strings that begin with character i.  These are initialized
           to NIL.  Note there are 256 trees. */

        for (i = N + 1; i <= N + 256; i++) rson[i] = NIL;       /* root */
        for (i = 0; i < N; i++) dad[i] = NIL;   /* node */
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::InsertNode(int r)
        /* Inserts string of length F, text_buf[r..r+F-1], into one of the
           trees (text_buf[r]'th tree) and returns the longest-match position
           and length via the global variables match_position and match_length.
           If match_length = F, then removes the old node in favor of the new
           one, because the old one will be deleted sooner.
           Note r plays double role, as tree node and position in buffer. */
{
        int  i, p, cmp, temp;
        unsigned char  *key;

        cmp = 1;  key = &text_buf[r];  p = N + 1 + key[0];
        rson[r] = lson[r] = NIL;  match_length = 0;
        for ( ; ; ) {
                if (cmp >= 0) {
                        if (rson[p] != NIL) p = rson[p];
                        else {  rson[p] = r;  dad[r] = p;  return;  }
                } else {
                        if (lson[p] != NIL) p = lson[p];
                        else {  lson[p] = r;  dad[r] = p;  return;  }
                }
                for (i = 1; i < F; i++)
                        if ((cmp = key[i] - text_buf[p + i]) != 0)  break;
                if (i > THRESHOLD) {
                        if (i > match_length) {
                                match_position = (r - p) & (N - 1);
                                if ((match_length = i) >= F) break;
                        } else if (i == match_length) {
                                if ((temp = (r - p) & (N - 1)) < match_position)
                                        match_position = temp;
                        }
                }
        }
        dad[r] = dad[p];  lson[r] = lson[p];  rson[r] = rson[p];
        dad[lson[p]] = r;  dad[rson[p]] = r;
        if (rson[dad[p]] == p) rson[dad[p]] = r;
        else                   lson[dad[p]] = r;
        dad[p] = NIL;  /* remove p */
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::DeleteNode(int p)  /* Delete node p from tree */
{
        int  q;

        if (dad[p] == NIL) return;  /* not in tree */
        if (rson[p] == NIL) q = lson[p];
        else if (lson[p] == NIL) q = rson[p];
        else {
                q = lson[p];
                if (rson[q] != NIL) {
                        do {  q = rson[q];  } while (rson[q] != NIL);
                        rson[dad[q]] = lson[q];  dad[lson[q]] = dad[q];
                        lson[q] = lson[p];  dad[lson[p]] = q;
                }
                rson[q] = rson[p];  dad[rson[p]] = q;
        }
        dad[q] = dad[p];
        if (rson[dad[p]] == p) rson[dad[p]] = q;
        else                   lson[dad[p]] = q;
        dad[p] = NIL;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::StartModel(void)  /* Initialize model */
{
        int ch, sym, i;

        sym_cum[N_CHAR] = 0;
        for (sym = N_CHAR; sym >= 1; sym--) {
                ch = sym - 1;
                char_to_sym[ch] = sym;  sym_to_char[sym] = ch;
                sym_freq[sym] = 1;
                sym_cum[sym - 1] = sym_cum[sym] + sym_freq[sym];
        }
        sym_freq[0] = 0;  /* sentinel (!= sym_freq[1]) */
        position_cum[N] = 0;
        for (i = N; i >= 1; i--)
                position_cum[i - 1] = position_cum[i] + 10000 / (i + 200);
                        /* empirical distribution function (quite tentative) */
                        /* Please devise a better mechanism! */
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::UpdateModel(int sym)
{
        int i, c, ch_i, ch_sym;

        if (sym_cum[0] >= MAX_CUM) {
                c = 0;
                for (i = N_CHAR; i > 0; i--) {
                        sym_cum[i] = c;
                        c += (sym_freq[i] = (sym_freq[i] + 1) >> 1);
                }
                sym_cum[0] = c;
        }
        for (i = sym; sym_freq[i] == sym_freq[i - 1]; i--) ;
        if (i < sym) {
                ch_i = sym_to_char[i];    ch_sym = sym_to_char[sym];
                sym_to_char[i] = ch_sym;  sym_to_char[sym] = ch_i;
                char_to_sym[ch_i] = sym;  char_to_sym[ch_sym] = i;
        }
        sym_freq[i]++;
        while (--i >= 0) sym_cum[i]++;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::Output(int bit)  /* Output 1 bit, followed by its complements */
{
        PutBit(bit);
        for ( ; shifts > 0; shifts--) PutBit(! bit);
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::EncodeChar(int ch)
{
        int  sym;
        unsigned long int  range;

        sym = char_to_sym[ch];
        range = high - low;
        high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
        low +=       (range * sym_cum[sym    ]) / sym_cum[0];
        for ( ; ; ) {
                if (high <= Q2) Output(0);
                else if (low >= Q2) {
                        Output(1);  low -= Q2;  high -= Q2;
                } else if (low >= Q1 && high <= Q3) {
                        shifts++;  low -= Q1;  high -= Q1;
                } else break;
                low += low;  high += high;
        }
        UpdateModel(sym);
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::EncodePosition(int position)
{
        unsigned long int  range;

        range = high - low;
        high = low + (range * position_cum[position    ]) / position_cum[0];
        low +=       (range * position_cum[position + 1]) / position_cum[0];
        for ( ; ; ) {
                if (high <= Q2) Output(0);
                else if (low >= Q2) {
                        Output(1);  low -= Q2;  high -= Q2;
                } else if (low >= Q1 && high <= Q3) {
                        shifts++;  low -= Q1;  high -= Q1;
                } else break;
                low += low;  high += high;
        }
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::EncodeEnd(void)
{
        shifts++;
        if (low < Q1) Output(0);  else Output(1);
        FlushBitBuffer();  /* flush bits remaining in buffer */
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::BinarySearchSym(unsigned int x)
        /* 1      if x >= sym_cum[1],
           N_CHAR if sym_cum[N_CHAR] > x,
           i such that sym_cum[i - 1] > x >= sym_cum[i] otherwise */
{
        int i, j, k;

        i = 1;  j = N_CHAR;
        while (i < j) {
                k = (i + j) / 2;
                if (sym_cum[k] > x) i = k + 1;  else j = k;
        }
        return i;
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::BinarySearchPos(unsigned int x)
        /* 0 if x >= position_cum[1],
           N - 1 if position_cum[N] > x,
           i such that position_cum[i] > x >= position_cum[i + 1] otherwise */
{
        int i, j, k;

        i = 1;  j = N;
        while (i < j) {
                k = (i + j) / 2;
                if (position_cum[k] > x) i = k + 1;  else j = k;
        }
        return i - 1;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::StartDecode(void)
{
        int i;

        for (i = 0; i < M + 2; i++)
                value = 2 * value + GetBit();
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::DecodeChar(void)
{
        int      sym, ch;
        unsigned long int  range;

        range = high - low;
        sym = BinarySearchSym((unsigned int)
                (((value - low + 1) * sym_cum[0] - 1) / range));
        high = low + (range * sym_cum[sym - 1]) / sym_cum[0];
        low +=       (range * sym_cum[sym    ]) / sym_cum[0];
        for ( ; ; ) {
                if (low >= Q2) {
                        value -= Q2;  low -= Q2;  high -= Q2;
                } else if (low >= Q1 && high <= Q3) {
                        value -= Q1;  low -= Q1;  high -= Q1;
                } else if (high > Q2) break;
                low += low;  high += high;
                value = 2 * value + GetBit();
        }
        ch = sym_to_char[sym];
        UpdateModel(sym);
        return ch;
}

//////////////////////////////////////////////////////////////////////

int CSWCompress::DecodePosition(void)
{
        int position;
        unsigned long int  range;

        range = high - low;
        position = BinarySearchPos((unsigned int)
                (((value - low + 1) * position_cum[0] - 1) / range));
        high = low + (range * position_cum[position    ]) / position_cum[0];
        low +=       (range * position_cum[position + 1]) / position_cum[0];
        for ( ; ; ) {
                if (low >= Q2) {
                        value -= Q2;  low -= Q2;  high -= Q2;
                } else if (low >= Q1 && high <= Q3) {
                        value -= Q1;  low -= Q1;  high -= Q1;
                } else if (high > Q2) break;
                low += low;  high += high;
                value = 2 * value + GetBit();
        }
        return position;
}

//////////////////////////////////////////////////////////////////////

DWORD CSWCompress::Encode(IStream* pInput,IStream* pOutput)
{
	Init ();
    m_pInput = pInput;
	STATSTG state;
	pInput->Stat (&state, STATFLAG_NONAME);

	inputmemsize = state.cbSize.LowPart;
    m_pOutput = pOutput;
	
	int  i, c, len, r, s, last_match_length;

    textsize = state.cbSize.LowPart;
	BYTE bFormatID = 0;
	ULONG uWritten;
	pOutput->Write (&bFormatID, sizeof(bFormatID), &uWritten);
	pOutput->Write (&textsize,sizeof(textsize), &uWritten);
	codesize += sizeof textsize + sizeof bFormatID;
    if (textsize == 0) return 0;
    textsize = 0;
    StartModel();  InitTree();
    s = 0;  r = N - F;
    for (i = s; i < r; i++) text_buf[i] = ' ';
    for (len = 0; len < F && (c = mgetc()) != -1; len++)
            text_buf[r + len] = c;
    textsize = len;
    for (i = 1; i <= F; i++) InsertNode(r - i);
    InsertNode(r);
    do {
            if (match_length > len) match_length = len;
            if (match_length <= THRESHOLD) {
                    match_length = 1;  EncodeChar(text_buf[r]);
            } else {
                    EncodeChar(255 - THRESHOLD + match_length);
                    EncodePosition(match_position - 1);
            }
            last_match_length = match_length;
            for (i = 0; i < last_match_length &&
                            (c = mgetc()) != -1; i++) {
                    DeleteNode(s);  text_buf[s] = c;
                    if (s < F - 1) text_buf[s + N] = c;
                    s = (s + 1) & (N - 1);
                    r = (r + 1) & (N - 1);
                    InsertNode(r);
            }
			if ((textsize += i) > printcount)
			{
				if (m_bfFlags.fNotify)
					SendMessage(m_hwndNotify, m_uMsg,textsize,0);
                printcount += 1024;
            }
			
            while (i++ < last_match_length) {
                    DeleteNode(s);
                    s = (s + 1) & (N - 1);
                    r = (r + 1) & (N - 1);
                    if (--len) InsertNode(r);
            }
    } while (len > 0);
    EncodeEnd();
	if (m_bfFlags.fCRC_OutputSet)
	{
		*m_pdwCRC_Before = CRC_before;
		*m_pdwCRC_After = CRC_after;
		m_bfFlags.fCRC_OutputSet = false;
	}
	return codesize;
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::Decode(IStream* pInput,IStream* pOutput)
{
	Init ();
    m_pInput = pInput;

	STATSTG state;
	pInput->Stat (&state, STATFLAG_NONAME);

	inputmemsize = state.cbSize.LowPart;
    m_pOutput= pOutput;    
	int  i, j, k, r, c;
	unsigned long int  count;
	BYTE bFormatID;
	ULONG uRead;
	m_pInput->Read (&bFormatID, sizeof(bFormatID), &uRead);
	m_pInput->Read(&textsize,sizeof textsize, &uRead);
	StartDecode();  StartModel();
	for (i = 0; i < N - F; i++) text_buf[i] = ' ';
	r = N - F;
	for (count = 0; count < textsize; ) {
		c = DecodeChar();
		if (c < 256) {
			mputc(c);  text_buf[r++] = c;
			r &= (N - 1);  count++;
		} else {
			i = (r - DecodePosition() - 1) & (N - 1);
			j = c - 255 + THRESHOLD;
			for (k = 0; k < j; k++) {
				c = text_buf[(i + k) & (N - 1)];
				mputc(c);  text_buf[r++] = c;
				r &= (N - 1);  count++;
			}
		}
        if (count > printcount)
		{
			if (m_bfFlags.fNotify)
				SendMessage(m_hwndNotify, m_uMsg,count,0);
			printcount += 1024;
		}
	}
}

//////////////////////////////////////////////////////////////////////

DWORD CSWCompress::Encode(CswFile *input,CswFile *out)
{
	return Encode (*input, *out);
}

//////////////////////////////////////////////////////////////////////

void CSWCompress::Decode(CswFile *input,CswFile *out)
{
	/*return*/ Decode (*input, *out);
}
