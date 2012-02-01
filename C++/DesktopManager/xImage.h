/*
 * File:	ximage.h
 * Purpose:	General Purpose Image Class 
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * CxImage (c)  07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * CxImage version 3.02 24/Jan/2002
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * original CImage and CImageIterator implementation are:
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 *
 * COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
 * THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
 * CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
 * THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
 * SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
 * PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.
 *
 * Use at your own risk!
 * ==========================================================
 */
#if !defined(__MYFXIMAGE_H)
#define __MYFXIMAGE_H

#if _MSC_VER > 1000
#pragma once
#endif 

//#include <afxwin.h>		// needed by the specific platform
#include <windows.h>
//#include <tchar.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CxImage supported features
#define CXIMAGE_SUPPORT_ALPHA          1
#define CXIMAGE_SUPPORT_SELECTION      1
#define CXIMAGE_SUPPORT_TRANSFORMATION 1 //needs SELECTION & ALPHA
#define CXIMAGE_SUPPORT_DSP            1 //needs TRANSFORMATION & SELECTION

/////////////////////////////////////////////////////////////////////////////
// CxImage supported formats
#define CXIMAGE_SUPPORT_BMP 1
#define CXIMAGE_SUPPORT_GIF 1
#define CXIMAGE_SUPPORT_JPG 1
#define CXIMAGE_SUPPORT_PNG 1
#define CXIMAGE_SUPPORT_MNG 0
#define CXIMAGE_SUPPORT_ICO 1
#define CXIMAGE_SUPPORT_TIF 1
#define CXIMAGE_SUPPORT_TGA 1
#define CXIMAGE_SUPPORT_PCX 1

/////////////////////////////////////////////////////////////////////////////
// CxImage formats enumerator
enum {
#if CXIMAGE_SUPPORT_BMP
CXIMAGE_FORMAT_BMP,
#endif
#if CXIMAGE_SUPPORT_GIF
CXIMAGE_FORMAT_GIF,
#endif
#if CXIMAGE_SUPPORT_JPG
CXIMAGE_FORMAT_JPG,
#endif
#if CXIMAGE_SUPPORT_PNG
CXIMAGE_FORMAT_PNG,
#endif
#if CXIMAGE_SUPPORT_MNG
CXIMAGE_FORMAT_MNG,
#endif
#if CXIMAGE_SUPPORT_ICO
CXIMAGE_FORMAT_ICO,
#endif
#if CXIMAGE_SUPPORT_TIF
CXIMAGE_FORMAT_TIF,
#endif
#if CXIMAGE_SUPPORT_TGA
CXIMAGE_FORMAT_TGA,
#endif
#if CXIMAGE_SUPPORT_PCX
CXIMAGE_FORMAT_PCX,
#endif
CMAX_IMAGE_FORMATS
};

// needed for png & gif
struct rgb_color_struct { BYTE r,g,b; };
// needed for png & mng
#define COLORTYPE_PALETTE	1
#define COLORTYPE_COLOR		2
#define COLORTYPE_ALPHA		4

#define RGB2GRAY(r,g,b) ((b*11 + g*59 + r*30)/100) //color to grey mapping

/////////////////////////////////////////////////////////////////////////////
// CxImage class
/////////////////////////////////////////////////////////////////////////////
class CxImage
{
//extensible information collector
typedef struct tagCxImageInfo {
	DWORD	dwEffWidth;			//DWORD aligned scan line width
	BYTE*	pImage;				//THE IMAGE BITS
	void*	pGhost;				//if this is a ghost, pGhost point to the body
	DWORD	dwType;				//original image format
	BYTE	bColorType;			//used for PNG, MNG
	char	szLastError[256];	//debugging
	long	nProgress;			//monitor
	long	nEscape;			//escape
	long	nBkgndIndex;		//used for GIF, PNG, MNG
	RGBQUAD nBkgndColor;		//used for RGB transparency
	BYTE	nQuality;			//used for JPEG
	long	nFrame;				//used for TIF, GIF, MNG : actual frame
	long	nNumFrames;			//used for TIF, GIF, MNG : total number of frames
	DWORD	dwFrameDelay;		//used for GIF, MNG
	long	xDPI;				//horizontal resolution
	long	yDPI;				//vertical resolution
	RECT	rSelectionBox;		//bounding rectangle
	BYTE	nAlphaMax;			//max opacity (fade)
	BYTE	bAlphaPaletteEnabled; //true if alpha values in the palette are enabled.
	BYTE	bEnabled;			//enables the painting functions
} CXIMAGEINFO;

public:
	//constructors
	CxImage(DWORD imagetype = 0);
	CxImage(DWORD dwWidth, DWORD dwHeight, long wBpp, long imagetype = 0);
	CxImage(const CxImage &src, bool copypixels = false, bool copyselection = false, bool copyalpha = false);
	CxImage(const char * filename, DWORD imagetype);
	CxImage(FILE * stream, DWORD imagetype);
	virtual ~CxImage();
	CxImage& operator = (CxImage);

	//initializzation
	void*	Create(DWORD dwWidth, DWORD dwHeight, long wBpp, long imagetype = 0);
	void	CreateFromHBITMAP(HBITMAP hbmp);	//Windows resource
	void	CreateFromHANDLE(HANDLE hMem);		//Windows objects (clipboard)
	void	Clear(BYTE bval=0);
	void	Copy(const CxImage &src, bool copypixels = true, bool copyselection = true, bool copyalpha = true);
	HANDLE	CopyToHandle();
	void	Transfer(CxImage &from);
	HBITMAP MakeBitmap(HDC hdc);

	//Attributes
	long	GetSize();
	BYTE*	GetBits();
	HANDLE	GetDIB()		const {return pDib;}
	DWORD	GetHeight()		const {return head.biHeight;}
	DWORD	GetWidth()		const {return head.biWidth;}
	DWORD	GetEffWidth()	const {return info.dwEffWidth;}
	DWORD	GetNumColors()	const {return head.biClrUsed;}
	BYTE	GetColorType()	const {return info.bColorType;}
	WORD	GetBpp()		const {return head.biBitCount;}
	DWORD	GetType()		const {return info.dwType;}
	BYTE	GetJpegQuality() const {return info.nQuality;}
	long	GetXDPI()		const {return info.xDPI;}
	long	GetYDPI()		const {return info.yDPI;}
	LPSTR	GetLastError()	{return info.szLastError;}

	void	SetJpegQuality(BYTE q) {info.nQuality = q;}
	void	SetXDPI(long dpi);
	void	SetYDPI(long dpi);

	long	GetProgress()	const {return info.nProgress;}
	long	GetEscape()     const {return info.nEscape;}
	void	SetProgress(long p) {info.nProgress = p;}
	void	SetEscape(long i)   {info.nEscape = i;}

	long	GetTransIndex()	const {return info.nBkgndIndex;}
	RGBQUAD	GetTransColor();
	void	SetTransIndex(long idx) {info.nBkgndIndex = idx;}
	void	SetTransColor(RGBQUAD rgb) {info.nBkgndColor = rgb;}

	//palette operations
	bool	IsGrayScale();
	DWORD	GetPaletteSize();
	RGBQUAD* GetPalette() const;
	RGBQUAD GetPaletteColor(BYTE idx);
	bool	GetRGB(int i, BYTE* r, BYTE* g, BYTE* b);
	BYTE	GetNearestIndex(RGBQUAD c);
	void	BlendPalette(COLORREF cr,long perc);
	void	SetGrayPalette();
	void	SetPalette(DWORD n, BYTE *r, BYTE *g, BYTE *b);
	void	SetPalette(RGBQUAD* pPal,DWORD nColors=256);
	void	SetPalette(rgb_color_struct *rgb,DWORD nColors=256);
	void	SetPaletteIndex(BYTE idx, BYTE r, BYTE g, BYTE b, BYTE alpha=0);
	void	SetPaletteIndex(BYTE idx, RGBQUAD c);
	void	SetPaletteIndex(BYTE idx, COLORREF cr);
	void	SwapIndex(BYTE idx1, BYTE idx2);
	void	SetStdPalette();

	//pixel operations
	bool	IsInside(long x, long y);
	BYTE	GetPixelIndex(long x,long y);
	RGBQUAD GetPixelColor(long x,long y);
	void	SetPixelColor(long x,long y,RGBQUAD c);
	void	SetPixelIndex(long x,long y,BYTE i);
	void	SetPixelColor(long x,long y,COLORREF cr);

	//painting operations
	long	Draw(HDC pDC, long x=0, long y=0, long cx = -1, long cy = -1);
	long	Draw(HDC hdc, const RECT& rect) { return Draw(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top); }
	long	Stretch(HDC pDC, long xoffset, long yoffset, long xsize, long ysize);
	long	Stretch(HDC hdc, const RECT& rect) { return Stretch(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top); }
	long	Tile(HDC pDC, RECT *rc);
//	long	Print(HDC pDC, long x=0, long y=0, long cx = -1, long cy = -1);
//	long	Print(HDC hdc, const RECT& rect) { return Print(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top); }


	// file operations
	bool SaveFile(const char * filename, DWORD imagetype=0);
	bool ReadFile(const char * filename, DWORD imagetype=0);
	bool SaveFile(LPCWSTR filename, DWORD imagetype=0);
	bool ReadFile(LPCWSTR filename, DWORD imagetype=0);
	bool LoadResource(HRSRC hRes, DWORD imagetype, HMODULE hModule=NULL);
	bool Decode(FILE * hFile, DWORD imagetype);
	bool Encode(FILE * hFile, DWORD imagetype);

	bool IsValid(){return (pDib!=0);}
	bool IsEnabled(){return info.bEnabled!=0;}
	void Enable(bool enable=true){info.bEnabled=enable;}

	// frame operations
	long GetNumFrames() const {return info.nNumFrames;}
	long GetFrame() const {return info.nFrame;}
	void SetFrame(long nFrame) {info.nFrame=nFrame;}

#if CXIMAGE_SUPPORT_TRANSFORMATION
	// image operations
	bool Flip();
	bool Mirror();
	bool Negative();
	bool GrayScale();
	bool Rotate(float angle, CxImage* iDst = NULL);
	bool Resample(long newx, long newy, int fast = 1);
	bool DecreaseBpp(DWORD nbit, bool errordiffusion, RGBQUAD* ppal = 0);
	bool IncreaseBpp(DWORD nbit);
	bool Dither(long method = 0);
	bool Crop(long left, long top, long right, long bottom, CxImage* iDst = NULL);
	bool Crop(const RECT& rect, CxImage* iDst = NULL) { return Crop(rect.left, rect.top, rect.right, rect.bottom, iDst); }
#endif //CXIMAGE_SUPPORT_TRANSFORMATION

#if CXIMAGE_SUPPORT_DSP
	bool Threshold(BYTE level);
	bool Colorize(BYTE hue, BYTE sat);
	bool Light(long level, long contrast=100);
	float Mean();
	bool Filter(long* kernel, long Ksize, long Kfactor, long Koffset);
	bool Erode(long Ksize=2);
	bool Dilate(long Ksize=2);
	void HuePalette(float correction=1);
	//color conversion utilities
	bool SplitRGB(CxImage* r,CxImage* g,CxImage* b);
	bool SplitYUV(CxImage* y,CxImage* u,CxImage* v);
	bool SplitHSL(CxImage* h,CxImage* s,CxImage* l);
	RGBQUAD HSLtoRGB(COLORREF cHSLColor);
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
	RGBQUAD YUVtoRGB(RGBQUAD lYUVColor);
	RGBQUAD RGBtoYUV(RGBQUAD lRGBColor);
#endif //CXIMAGE_SUPPORT_DSP
	RGBQUAD RGBtoRGBQUAD(COLORREF cr);
	COLORREF RGBQUADtoRGB (RGBQUAD c);

#if CXIMAGE_SUPPORT_SELECTION
	//selection
	void SelectionClear();
	void SelectionCreate();
	void SelectionDelete();
	void SelectionInvert();
	void SelectionAddRect(RECT r);
	void SelectionAddEllipse(RECT r);
	void SelectionAddPolygon(POINT *points, long npoints);
	bool SelectionCopy(CxImage &from);
	bool IsInsideSelection(long x, long y);
	bool HasSelection(){return pSelection!=0;}
	void GetSelectionBox(RECT& r){memcpy(&r,&info.rSelectionBox,sizeof(RECT));}
#endif //CXIMAGE_SUPPORT_SELECTION

#if CXIMAGE_SUPPORT_ALPHA
	//Alpha
	void AlphaClear();
	void AlphaCreate();
	void AlphaDelete();
	void AlphaInvert();
	bool AlphaMirror();
	bool AlphaFlip();
	bool AlphaCopy(CxImage &from);
	void AlphaStrip();
	void AlphaSet(BYTE level);
	void AlphaSet(long x,long y,BYTE level);
	BYTE AlphaGet(long x,long y);
	BYTE AlphaGetMax() const {return info.nAlphaMax;}
	void AlphaSetMax(BYTE nAlphaMax) {info.nAlphaMax=nAlphaMax;}
	bool HasAlpha(){return pAlpha!=0;}

	void AlphaPaletteClear();
	void AlphaPaletteEnable(bool enable=true){info.bAlphaPaletteEnabled=enable;}
	bool IsAlphaPaletteEnabled(){return info.bAlphaPaletteEnabled!=0;}
	bool HasAlphaPalette();
#endif //CXIMAGE_SUPPORT_ALPHA

protected:
	void Startup(DWORD imagetype = 0);
	void Ghost(CxImage *src);
	void RGBtoBGR(BYTE *buffer, int length);
	float HueToRGB(float n1,float n2, float hue);
	void Bitfield2RGB(BYTE *src, WORD redmask, WORD greenmask, WORD bluemask, BYTE bpp);

	void*				pDib; //contains the header, the palette, the pixels
    BITMAPINFOHEADER    head; //stadnard header
	CXIMAGEINFO			info; //extended information
	BYTE*				pSelection;	//selected region
	BYTE*				pAlpha; //alpha channel
};
////////////////////////////////////////////////////////////////////////////
#endif // !defined(__MYFXIMAGE_H)
