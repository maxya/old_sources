/*typedef struct SswChunkInfo
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
} SWCHUNKINFO, *LPSWCHUNKINFO;*/

	
	/*
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
	IN LPVOID pvBuff,				// источник для записи
	IN DWORD cbLength,				// сколько байт записывать
	IN DWORD cbMinFragLen,			// минимальный размер фрагмента данных
	IN LPSWCHUNKINFO pInfo,			// имеет значение только тип куска, остальные поля игнорируются
	OUT PDWORD pcFragments			// число выделенных фрагментов (можно оставить NULL)
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
	if (cbRemain) // записать всё, что осталось, в конец файла
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