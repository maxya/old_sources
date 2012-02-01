// LibraryTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TheLibrary.h"
#include "swMap.h"
#include "swRanges.h"
#define SWEcho(str) SWConsoleOutput (str, TEXT("theLib test"))

//#include "SWLists.h"
//#include "swStreamOnHeap.h"
//#include "swStreamOnFile.h"
//#include "swDirectory.h"
//#include "swChunkedFile.h"

SWDEBUGTRACE_ENABLE()

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CUniversalText utTest;
	CswFile	file;
	if( file.OpenHDD("sidebar.cgi", GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING) )
	{
		while(utTest.LoadAsLine(file, FALSE))
		{
			int a = 0;
		}
	}


//	SWDEBUGTRACE_START("C:\\var\\log\\test.log");
//	SWOutputDebugString("------------- [ Test debug output started ] -------------\n");
//	SWOutputDebugStringNamed("Hello!\n", "Global");
//	SWOutputDebugString("------------- [ Test debug output finished ] ----------\n\n\n");
//	SWDEBUGTRACE_END();

//////////////////////////////////////////////////////////////////////

//	CswUTArray arTest;
//	arTest.Push( "abc" );
//	arTest.Push( "def" );
//	arTest.Push( "ghi" );
//	arTest.Push( "jkl" );
//	arTest.PushAt( 2, "xyz" );
	
//////////////////////////////////////////////////////////////////////
	
//	CUniversalText utRes, utTest = "1234567";	
//	utRes = utTest.Reverse();
//	utTest;
	
//////////////////////////////////////////////////////////////////////
	
//	CUniversalText utTest = 
//		"First line\n"
//		"Second line\n"
//		"Third line";

//////////////////////////////////////////////////////////////////////

//	CswUTArray utaTest; 
//	CUniversalText utSample = "1234657890-1234657890-1234657890-1234657890";
//	for ( int i = 0; i < 2000 ; i++)
//		utaTest.Push (utSample);
//	utaTest.Clear ();
//	return 0;

//////////////////////////////////////////////////////////////////////
 
//	CswRangeSet<DWORD> set1, set2;
//	set1.AddRange (10, 20);			// [10, 20]
//	set1.AddRange (25, 30);			// [10, 20] U [25, 30]
//	set1.AddRange (15, 25);			// [10, 30]
//	set1.SubtractRange (15, 20);	// [10, 15] U [20, 30]
//	set1.DoesIntersect (15, 20);
//	return 0;

//////////////////////////////////////////////////////////////////////

//	SWDIR dirRoot, dir1, dir1c, dir2;
//	SWFILE file;
//	if (dirRoot.OpenHDD (L"Collection.com.stg", STGM_WANNAALL  , IT_COMSTG))
//	{
//		dirRoot.OpenDirVN (L"Screenshots", STGM_WANNAALL, dir1);
//		dirRoot.OpenDirVN (L"FAN Wallpapers", STGM_WANNAALL, dir2);
//		dirRoot.OpenDirVN (L"Screenshots", STGM_WANNAALL, dir1c);
//		dir2.Close ();
//		dir1c.Close ();
//		dir1.Close ();
//		dirRoot.Close();
//	}
//	return 0;
	
//////////////////////////////////////////////////////////////////////

//	CswMap<CUniversalText, UINT> swMap;
//	swMap["adin"] = 123;
//	swMap["dva"] = 234;
//	swMap["tri"] = 356;
//
//	CswMap<UINT, CUniversalText> swFlipped = swMap.Flip ();
//	CUniversalText utRes = swFlipped[123];
//
//	CswUTArray swArr;
//	swArr.Push ("minus adin");
//	swArr.Push ("nol");
//	swArr += swFlipped;
//	utRes = swArr[2];
//	return 0;

//////////////////////////////////////////////////////////////////////
//	CswUTArray swa1, swa2, swa3, swaRes;
//	swa1.Push (" => 0");
//	swa2.Push (" => 1");
//	swa3.Push (" => 2");
//	swaRes = swa1 + swa2 + swa3;
//	swaRes.Push (" => 3");
//	swaRes.Push (" => 4");
//	swaRes.Push (" => 5");
//	CUniversalText urVal; 
//	swaRes.PopFromMiddle (1, urVal);
//	urVal = swaRes[3];
//	UINT idx = 1; 
//	if (swaRes.SearchValue (urVal, idx))
//	{
//		int k = 0;
//	}
//	return 0;
//////////////////////////////////////////////////////////////////////

/*
	SWCHFILE file;
	if (file.OpenHDD ("chains.bin"))
	{
		file.AddChainTypeFilter ("TXT");
		if (file.StartChainsWalker ())
		{
			//CUniversalText utType = file.GetCurChainType ();
			DWORD dwLen = file.GetCurChainLength ();
			SWEcho ("Chunked file initialized.\r\n");
			if (file.AssertCurChainType ())
			{
				DWORD dwLen = file.GetCurChainLength ();
				LPVOID pvBuff = malloc (dwLen);
				file.OpenCurrentChain ();
				if (file.ChainRead (pvBuff, dwLen) != EOF)
				{
					SWEcho (CUniversalText("Read: ") + (LPSTR)pvBuff + "\r\n");
					int i = 0;
				}
				file.CloseCurrenChain ();
				free (pvBuff);
			}
			else
			{
				CUniversalText utTest;
				SWEcho ("No data found. Writing test chunk.\r\n");
				chnkInfo.SetType ("TXT");
				utTest = "Test data: 1 2 3 :)";
				file.WriteChain ( (LPSTR) utTest, utTest.GetSizeA (), 32, &chnkInfo, NULL);
				utTest = "qwertyuiopasdfghjklzxcvbnm";
				file.WriteChain ( (LPSTR) utTest, utTest.GetSizeA (), 32, &chnkInfo, NULL);
				utTest = "[queen]";
				file.WriteChain ( (LPSTR) utTest, utTest.GetSizeA (), 32, &chnkInfo, NULL);
				file.SeekToFirstChunk ();
				file.DiscardChunk ();
				utTest = "";
				for (int i = 0 ; i < 45 ; i++)
				{
					CUniversalText utSuff;
					utSuff.Format ("%d|", i);
					utTest += utSuff;
				}
				for (i = 0 ; i < 25 ; i++)
				{
					file.WriteChain ( (LPSTR) utTest, utTest.GetSizeA (), 32, &chnkInfo, NULL);
				}
			}
		}
		else
			SWEcho ("This file is not Chunked file.\r\n");

		file.Close ();
	}
	return 0;

*/
//////////////////////////////////////////////////////////////////////
	/*
	{
		CUniversalText utText = "Cat01/Coll02/file03.data";
		CswUTArray parts = 10;
		utText.Explode ("/", parts, TRUE);
		CUniversalText utPiece;
		while (parts.Shift (utPiece))
		{
			SWEcho (utPiece + "\r\n");
		}
		return 0;
	}
	*/
//////////////////////////////////////////////////////////////////////
/* using SWDIR and SWFILE */

/*	
	
	SWDIR swRootDir, swColDir, swCatDir;
	SWFILE swFile;
	if (swRootDir.OpenHDD (L"Collection.com.stg", 
		STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, IT_COMSTG))
	{
		if (swRootDir.OpenDir (L"Porno", 
			STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, swColDir))
		{
			if (swColDir.OpenDir (L"Cyndy Crawford", 
				STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, swCatDir))
			{
				if (swCatDir.OpenFile (L"Cyndy Crawford 001", 
					STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, swFile))
				{
					SWFILE swFileReadMe;
					if (swFileReadMe.OpenHDD ("readme.txt", GENERIC_READ, 0, OPEN_EXISTING))
					{
						swFileReadMe.CopyTo (swFile);
						swFileReadMe.Close ();
					}
					swFile.Close ();
				}
				swCatDir.Close ();
			}
			swColDir.Close ();
		}
		swRootDir.Close();
	}
	return 0;	
*/

//////////////////////////////////////////////////////////////////////
// * hash table test * //

//	CswMap<CUniversalText, CUniversalText> arTest;
//	arTest[":-)"] = "123";
//	arTest[":-|"] = "456";
//	arTest[":-("] = "789";
//	
//	CUniversalText* pKey;
//	for (CUniversalText* pVal = arTest.Reset (&pKey) ; pVal ; pVal = arTest.Next (&pKey))
//		MessageBoxUT (NULL, *pVal, *pKey, 0);
//
//	return 0;
//////////////////////////////////////////////////////////////////////
// * Retrieving key name test * //

//	CUniversalText utKeyName = GetVKNameTextUT (VK_RCONTROL);

//////////////////////////////////////////////////////////////////////
// * UT case-insetive compare test * //

//	CUniversalText utComp ("ABC");
//	BOOL fEq = utComp.CaseInsensitiveCompare (L"abd");

//////////////////////////////////////////////////////////////////////
// * Save/Open file dlgbox test * //

//	static LPWSTR wszFilter = L"All Files (*.*)\0*.*\0\0";
//	static LPSTR szFilter = "All Files (*.*)\0*.*\0\0";
//	CUniversalText utFileName;
//	GetSaveFileNameUT (NULL, wszFilter, szFilter, (LPSTR)NULL, utFileName);

//////////////////////////////////////////////////////////////////////
// * Getting current directory test * //

//	CUniversalText utCurDir = GetCurrentDirectoryUT ();

//////////////////////////////////////////////////////////////////////
// * Command line parser test * //

//	CSWCommandLine CmdLine = "\"C:\\Projects\\WIN32\\Multi Block Storage\\Version 3.3\\Debug\\MBS.exe\" \"C:\\test.sdd\"";
//	MessageBoxUT (NULL, CmdLine.GetFormalParameter (0) + "\r\n", "CmdLine", MB_ICONINFORMATION);

//////////////////////////////////////////////////////////////////////
// * Dynamic array testing * //

//	LPSTR szStr1 = "(1) String 1";
//	LPSTR szStr2 = "(2) Kalyaka-Malyaka";
//	LPSTR szStr3 = "(3) Get Outta Here!";
//	CSWPtrArray ptrArray;
//	ptrArray.Add (szStr1);
//	ptrArray.Add (szStr2);
//	ptrArray.Add (szStr3);
//
//	LPSTR szTest1;
//	LPSTR szTest2;
//	LPSTR szTest3;
//
//	szTest1 = (LPSTR) ptrArray[0];
//	szTest2 = (LPSTR) ptrArray[1];
//	szTest3 = (LPSTR) ptrArray[2];

//////////////////////////////////////////////////////////////////////
// * Stream implementations test * //

	//ULONG uWritten;
	//IStream* pStream = NULL;
	//IStream* pTarget = NULL;
	//LARGE_INTEGER liSeek;
	//ULARGE_INTEGER uliSeek;
	//liSeek.QuadPart = 0;

	//CUniversalText utTest;// = "Hello :)";
	//CSWFile file, ramFile;
	//file.OpenHDD (L"Test.txt");
	//ramFile.OpenRAM ();
	//file.CopyTo (ramFile);
	//file.Close ();
	//ramFile.SeekBegin ();
	//utTest.LoadAsPlain (ramFile, EOF, FALSE);
	//ramFile.Close ();
	//pStream->Write (szStr1, strlen (szStr1), &uWritten);
//	uliSeek.QuadPart = (ULONGLONG)-1;
//	pStream->Seek (liSeek, STREAM_SEEK_SET, &uliSeek);
//	pStream->CopyTo (pTarget, uliSeek, &uliSeek, &uliSeek);

//	LPVOID pvMem;
//	SWGetBufferFromIStream (pTarget, &pvMem);
//	pStream->Release ();
//	pTarget->Release ();


//	SWConsoleOutput ("to Events\r\n", "Events");
//	SWConsoleOutput ("to General\r\n", "General");
//	SWConsoleOutput ("to UnNamed\r\n");

//////////////////////////////////////////////////////////////////////
// * Find token test * //

//	CUniversalText ut = "012\\456\\78 0";
//	int nPos = 0;
//	while ((nPos = ut.FindToken ("\\ ", nPos)) != -1)
//		int i = i;

//////////////////////////////////////////////////////////////////////
// * List implementation test * //

//	CSWOneWayList<CUniversalText> lstutTest;
//	lstutTest.Add ("First");
//	lstutTest.Add ("Second");
//	lstutTest.Add ("Third");
//	lstutTest.Add ("Fourth");
//	lstutTest.Add ("Fifth");
//	lstutTest.Add ("Sixth");
//	CUniversalText utResponse = lstutTest[2];
//	lstutTest.Remove (2);
//	utResponse = lstutTest[2];
	return 0;
}
