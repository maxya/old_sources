/*typedef struct SswChunkInfo
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
} SWCHUNKINFO, *LPSWCHUNKINFO;*/

	
	/*
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
	*/


/*
DWORD CswChunkedFile::SeekToFirstChunk ()
{
	return SeekTo (m_dw1stChunkOffset);
}


BOOL CswChunkedFile::GetChunkInfo (OUT LPSWCHUNKINFO lpInfo)
{
	while (1)
	{
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
		if (IsChunkDiscardable (lpInfo) || (lpInfo->rgfFlags & CHF_CONTINUE))
			ChunkAdvance (FALSE, lpInfo);
		else
			break;
	}
	return TRUE;
}

BOOL CswChunkedFile::GetChunkInfoAny (OUT LPSWCHUNKINFO lpInfo)
{
	return (Read (lpInfo, sizeof (*lpInfo)) == sizeof (*lpInfo));
}

BOOL CswChunkedFile::WriteChunkInfo (IN LPSWCHUNKINFO lpInfo)
{
	return (Write (lpInfo, sizeof (*lpInfo)) == sizeof (*lpInfo));
}

BOOL CswChunkedFile::ReadChunk (LPVOID pvBuff, BOOL fReadInfo, LPSWCHUNKINFO lpInfo)
{
	SWCHUNKINFO info;
	if (fReadInfo)
	{
		if (!lpInfo)
			lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
	}
	
	if (Read (pvBuff, lpInfo->cbDataLen) != lpInfo->cbDataLen)
		return FALSE;
	ChunkAdvance (FALSE, lpInfo);
	return TRUE;
}

BOOL CswChunkedFile::ChunkAdvance (BOOL fReadInfo, LPSWCHUNKINFO lpInfo)
{
	SWCHUNKINFO info;
	if (fReadInfo)
	{
		if (!lpInfo)
			lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
	}
	Seek ((LONG) lpInfo->cbLength, SEEK_CUR);
	return TRUE;
}

BOOL CswChunkedFile::ChainedChunkAdvance (BOOL fReadInfo, LPSWCHUNKINFO lpInfo)
{
	SWCHUNKINFO info;
	if (fReadInfo)
	{
		if (!lpInfo)
			lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
	}
	if (!lpInfo->dwNext)
		return FALSE;
	SeekTo (lpInfo->dwNext);
	return TRUE;
}

BOOL CswChunkedFile::FindDiscarded (IN DWORD dwLength, 
									OUT PDWORD pdwOffset, OUT PDWORD pdwLength)
{
	SWCHUNKINFO info;
	DWORD dwPos;
	DWORD dwStartPos = GetSeekPos ();
	BOOL fRes = FALSE;
	while (dwPos = GetSeekPos (), GetChunkInfoAny (&info))
	{
		
		if (IsChunkDiscardable (&info) && (info.cbLength >= dwLength))
		{
			fRes = TRUE;
			if (pdwOffset)
				*pdwOffset = dwPos;
			if (pdwLength)
				*pdwLength = info.cbLength;
			break;
		}
		ChunkAdvance (FALSE, &info);
	}

	SeekTo (dwStartPos);
	return fRes;
}

DWORD CswChunkedFile::WriteChain (
	IN LPVOID pvBuff,				// �������� ��� ������
	IN DWORD cbLength,				// ������� ���� ����������
	IN DWORD cbMinFragLen,			// ����������� ������ ��������� ������
	IN LPSWCHUNKINFO pInfo,			// ����� �������� ������ ��� �����, ��������� ���� ������������
	OUT PDWORD pcFragments			// ����� ���������� ���������� (����� �������� NULL)
)
{
	DWORD cFragments, cbChunkLen, dwOffset, cbDataLen;
	if (!pcFragments)
			pcFragments = &cFragments;
		
	CSWOneWayList<DWORD> lsOffsets;
	CSWOneWayList<DWORD> lsLengths;
	CSWOneWayList<DWORD> lsDataLens;
	DWORD dwStartPos = GetSeekPos ();
	SeekToFirstChunk ();
	DWORD cbRemain = cbLength;
	
	while (1)
	{
		BOOL fCrossBound = (cbRemain >= cbMinFragLen);
		DWORD dwDLen = fCrossBound ? (cbRemain - cbMinFragLen) : 0;
		//if (dwDLen < cbMinFragLen)
		//	dwDLen = cbMinFragLen;
		DWORD dwAllocTarget = fCrossBound ? cbRemain : cbMinFragLen;

		if (!FindDiscarded (cbMinFragLen, &dwOffset, &cbChunkLen))
			break;
		
		SeekTo (dwOffset);
		ChunkAdvance ();

		if (((cbMinFragLen <= cbChunkLen) && (cbChunkLen <= dwDLen)) ||
			(cbChunkLen == dwAllocTarget) ||
			(cbChunkLen >= dwAllocTarget + (cbMinFragLen + sizeof (SWCHUNKINFO))))
		{
			cbDataLen = cbChunkLen;
			// it is appropriate chunk
			if (cbChunkLen > cbRemain) // large enought chunk allocated.
			{
				if (cbRemain >= cbMinFragLen)
				{
					// check if selection was correct
					if (cbChunkLen - cbRemain < cbMinFragLen + sizeof (SWCHUNKINFO))
					{
						SWConsoleOutput ("FIXME: Incorrect chunk allocated, ignored.\r\n");
						continue;
					}
				}
				else
					cbDataLen = cbRemain;
			}
			lsOffsets.Add (dwOffset);
			lsLengths.Add (cbChunkLen);
			lsDataLens.Add (cbDataLen);
			cbRemain -= cbDataLen;
			if (!cbRemain)
				break;
		}
	}

	
	DWORD cbToWrite = cbLength;
	DWORD dwLastOffset = 0;
	(*pcFragments) = 0;
	if (cbRemain) // �������� ��, ��� ��������, � ����� �����
	{
		pInfo->cbLength = cbRemain > cbMinFragLen ? cbRemain : cbMinFragLen;
		pInfo->cbDataLen = cbRemain;
		pInfo->dwNext = 0;
		pInfo->rgfFlags = 0;
		SeekEnd ();
		dwLastOffset = GetSeekPos ();
		if (!WriteChunk (pInfo, reinterpret_cast<PBYTE>(pvBuff) + (cbLength - cbRemain)))
			return FALSE;
		cbToWrite -= cbRemain;
		(*pcFragments)++;
	}

	for (UINT i = 0; i < lsOffsets.Count () ; i++)
	{
		cbChunkLen = lsLengths[i];
		cbDataLen = lsDataLens[i];
		pInfo->cbLength = cbChunkLen;
		pInfo->cbDataLen = cbDataLen;	// = cbChunkLen < cbToWrite ? cbChunkLen : cbToWrite;
		pInfo->dwNext = lsOffsets.Count () - i == 1 ? dwLastOffset : lsOffsets[i+1];
		pInfo->rgfFlags = 0;
		SeekTo (lsOffsets[i]);
		if (!WriteChunk (pInfo, reinterpret_cast<PBYTE>(pvBuff) + (cbLength - cbToWrite - cbRemain)))
			return FALSE;
	
		if ((cbChunkLen > cbToWrite) && (cbDataLen == cbChunkLen))
		{
			SWCHUNKINFO info; 
			info.rgfFlags = 0;
			info.SetType ("\0\0\0");
			info.cbLength = cbChunkLen - cbToWrite - sizeof (info);
			info.cbDataLen = 0;
			MarkChunkDiscarded (&info);
			if (!WriteChunkInfo (&info))
				return FALSE;
		};
		cbToWrite -= pInfo->cbDataLen;
		(*pcFragments)++;
	}
	
	return (cbLength - cbToWrite);
}

DWORD CswChunkedFile::WriteChunk (IN LPSWCHUNKINFO lpInfo, IN LPVOID pvBuff)
{
	if (!WriteChunkInfo (lpInfo))
		return FALSE;
	if (Write (pvBuff, lpInfo->cbDataLen) != lpInfo->cbDataLen)
		return FALSE;
	if (lpInfo->cbDataLen < lpInfo->cbLength)
	{
		BYTE bChar = 0;
		Seek ((LONG) lpInfo->cbLength - lpInfo->cbDataLen - sizeof (bChar), SEEK_CUR);
		if (Write (&bChar, sizeof (bChar)) != sizeof (bChar))
			return FALSE;
	}
	return TRUE;
}

DWORD CswChunkedFile::GetChainLength (BOOL fReadInfo, LPSWCHUNKINFO lpInfo,	
									  OUT PDWORD pcFragments)
{
	SWCHUNKINFO info;
	DWORD cFragments, dwStartPos = GetSeekPos ();
	if (!pcFragments)
			pcFragments = &cFragments;

	if (fReadInfo)
	{
		if (!lpInfo)
			lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
	}
	if (lpInfo->rgfFlags & CHF_CONTINUE)
		return 0;
	
	DWORD dwLen = lpInfo->cbDataLen;
	while (lpInfo->dwNext)
	{
		if (!ChainedChunkAdvance (FALSE, lpInfo))
		//if (SeekTo (lpInfo->dwNext) != lpInfo->dwNext)
			return FALSE;
		lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
		dwLen += lpInfo->cbDataLen;
	}

	SeekTo (dwStartPos);
	return dwLen;
}

DWORD CswChunkedFile::ReadChain (IN LPVOID pvBuff, IN BOOL fReadInfo, 
								 LPSWCHUNKINFO lpInfo, OUT PDWORD pcFragments)
{
	SWCHUNKINFO info;
	DWORD cFragments, dwStartPos = GetSeekPos ();
	if (!pcFragments)
			pcFragments = &cFragments;

	if (fReadInfo)
	{
		if (!lpInfo)
			lpInfo = &info;
		if (!GetChunkInfoAny (lpInfo))
			return FALSE;
	}
	if (lpInfo->rgfFlags & CHF_CONTINUE)
		return 0;
	DWORD cbRead = 0;
	fReadInfo = FALSE;
	while (
		ReadChunk (((PBYTE)pvBuff) + cbRead, fReadInfo, lpInfo) && 
		(cbRead += lpInfo->cbDataLen, TRUE) &&
		(fReadInfo = TRUE, TRUE) &&
		ChainedChunkAdvance (FALSE, lpInfo)
		);

	return cbRead;
}

BOOL CswChunkedFile::IsChunkDiscardable (LPSWCHUNKINFO lpInfo)
{
	//return lpInfo->IsTypeOf ("RIP");
	return lpInfo->rgfFlags & CHF_DEAD;
}

BOOL CswChunkedFile::MarkChunkDiscarded (LPSWCHUNKINFO lpInfo)
{
	//lpInfo->SetType ("RIP");
	lpInfo->rgfFlags |= CHF_DEAD;
	return TRUE;
}

BOOL CswChunkedFile::DiscardChunk (IN BOOL fDecrease, IN DWORD cMaxRealloc)
{
	SWCHUNKINFO info;
	DWORD dwPos = GetSeekPos ();
	if (!GetChunkInfoAny (&info))
		return FALSE;
	MarkChunkDiscarded (&info);
	SeekTo (dwPos);
	return WriteChunkInfo (&info);
	//return FALSE;
}
*/