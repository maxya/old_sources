#include "stdafx.h"
#include "swChunkedFile.h"
#include "SWLists.h"

CswTaggedChainsFile::CswTaggedChainsFile(void)
{
	m_dw1stChunkOffset = EOF;
	m_pswFilter = new SWCHAINFILTER (64);
	m_pInfoCache = new SWCHAININFO;
	ClearInfoCache ();
}

CswTaggedChainsFile::~CswTaggedChainsFile(void)
{
	m_pswFilter && (delete m_pswFilter, true);
}

void CswTaggedChainsFile::AddChainTypeFilter (CUniversalText utType, DWORD dwCookie)
{
	(*m_pswFilter)[utType] = dwCookie;
}

void CswTaggedChainsFile::RemoveChainTypeFilter (CUniversalText utType)
{
	(*m_pswFilter).UnSet (utType);
}

void CswTaggedChainsFile::ClearChainFilter ()
{
	(*m_pswFilter).Clear ();
}

BOOL CswTaggedChainsFile::StartChainsWalker (BOOL fUseFilter, BOOL fInitIfNew)
{
	CUniversalText utSWTaggedChainsSign = "SeekWood Tagged Chains";
	DWORD dwLen = utSWTaggedChainsSign.GetLength ();
	CUniversalText utSign;
	SeekBegin ();
	
	if (utSign.LoadAsPlain (*this, dwLen, FALSE) && !utSign.IsEmpty ())
	{
		if (utSign != utSWTaggedChainsSign)
			return FALSE;
	}
	else
	{
		// seems to be new file. Trying to write 
		if (fInitIfNew && (!utSWTaggedChainsSign.SaveAsPlain (*this, dwLen, FALSE)))
			return FALSE;
	}
	m_dw1stChunkOffset = GetSeekPos ();
	if (fUseFilter)
		AssertCurChainType ();
	return TRUE;
}

BOOL CswTaggedChainsFile::WalkChain (CUniversalText utType)
{
	do
	{
		if (!WalkChain_noTypeCheck ())
			return FALSE;	// EOF reached
	} 
	while (utType.IsEmpty() ? !IsCurChainFiltered () : (GetCurChainType () != utType));
	return TRUE;
}

BOOL CswTaggedChainsFile::AssertCurChainType (CUniversalText utType)
{
	while (utType.IsEmpty() ? !IsCurChainFiltered () : (GetCurChainType () != utType))
		if (!WalkChain_noTypeCheck ())
			return FALSE;	// EOF reached
	return TRUE;
}

CUniversalText CswTaggedChainsFile::GetCurChainType ()
{
	if (!ReadInfoToCache (CIT_BRIEF))
		return NULLSTRING;
	return (*m_pInfoCache).brief.GetType ();
}

BOOL CswTaggedChainsFile::IsCurChainFiltered ()
{
	return (*m_pswFilter).IsSet (GetCurChainType ());
}

DWORD CswTaggedChainsFile::GetCurChainLength ()
{
	if (!ReadInfoToCache (CIT_BRIEF))
		return 0;
	return (*m_pInfoCache).brief.cbUsed;
}

//////////////////////////////////////////////////////////////////////

BOOL CswTaggedChainsFile::OpenCurrentChain ()
{
	SWCNODELISTITEM litem;
	if (!ReadInfoToCache (CIT_FULL))
		return FALSE;
	m_lsNodes.Empty ();
	do
	{
		litem.dwOffset = m_dwCachedNodeOffset;
		litem.info = m_pInfoCache->full.node;
		m_lsNodes.Add (litem);
	}
	while (WalkNode ());
	m_uNode = 0;
	m_dwNodeOffset = 0;
	return TRUE;
}

void CswTaggedChainsFile::CloseCurrenChain ()
{
	m_lsNodes.Empty ();
	SeekTo (m_dwCachedChainOffset);
	ClearInfoCache ();
	ReadInfoToCache (CIT_BRIEF);
}

DWORD CswTaggedChainsFile::ChainRead (LPVOID pvBuff, DWORD cbToRead)
{
	DWORD cbNodeRead, cbNodeToRead, cbNodeRemainder;
	DWORD cbRead = 0;
	if (m_uNode >= m_lsNodes.Count ()) // over-noded
		return EOF;
	do
	{
		SWCNODELISTITEM& litem = m_lsNodes[m_uNode];
		cbNodeRemainder = litem.info.cbNodeLength - m_dwNodeOffset;
		cbNodeToRead = (cbNodeRemainder < (cbToRead - cbRead)) ? 
			(cbNodeRemainder) : (cbToRead - cbRead);
					
		SeekTo (litem.dwOffset + sizeof (m_pInfoCache->full.node) + m_dwNodeOffset);
		if ((cbNodeRead = Read (reinterpret_cast<PBYTE>(pvBuff) + cbRead, cbNodeToRead)) == EOF)
			return EOF;

		cbRead += cbNodeRead;
		m_dwNodeOffset += cbNodeRead;
		if (cbNodeRead == cbNodeRemainder)
		{
			m_uNode++;
			m_dwNodeOffset = 0;
		}
	} 
	while ((cbRead < cbToRead) && (m_uNode < m_lsNodes.Count ()));
	// fixme: добавить проверку на перелаз за длину цепочки в Brief info
	return cbRead;
}

DWORD CswTaggedChainsFile::ChainWrite (LPVOID pvBuff, DWORD cbToRead)
{
	return EOF;
}

//////////////////////////////////////////////////////////////////////

void CswTaggedChainsFile::ClearInfoCache ()
{ 
	m_pInfoCache && (delete m_pInfoCache, m_pInfoCache = NULL, m_enInfoCacheType = CIT_NONE); 
}

BOOL CswTaggedChainsFile::ReadInfoToCache (enum SWCHAININFOTYPE enType)
{
	SWCHAININFOTYPE enNeededType;
	m_pInfoCache || (m_pInfoCache = new SWCHAININFO, m_enInfoCacheType = CIT_NONE );
	if (enType == m_enInfoCacheType)
		return TRUE;

	switch (m_enInfoCacheType)
	{
	case CIT_NONE:
		enNeededType = enType;
		break;
	case CIT_BRIEF:
	case CIT_NODE:
		switch (enType)
		{
		case CIT_NODE:
		case CIT_FULL:
			enNeededType = CIT_NODE;
			enType = CIT_FULL;
		}
		break;
	case CIT_FULL:
		switch (enType)
		{
		case CIT_BRIEF:
			enNeededType = CIT_BRIEF;
			break;
		case CIT_NODE:
		case CIT_FULL:
			enNeededType = CIT_NODE;
			enType = CIT_FULL;
		}
	};

	DWORD dwRead;
	switch (enNeededType)
	{
	case CIT_BRIEF:
		if ((dwRead = Read (&(m_pInfoCache->brief), sizeof (m_pInfoCache->brief))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedChainOffset = GetSeekPos () - dwRead;
		break;
	case CIT_FULL:
		if ((dwRead = Read (&(m_pInfoCache->full), sizeof (m_pInfoCache->full))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedChainOffset = GetSeekPos () - dwRead;
		m_dwCachedNodeOffset = m_dwCachedChainOffset + sizeof (m_pInfoCache->full.brief);
		break;
	case CIT_NODE:
		if ((dwRead = Read (&(m_pInfoCache->full.node), sizeof (m_pInfoCache->full.node))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedNodeOffset = GetSeekPos () - dwRead;
		break;
	default:
		return FALSE;
	}
	m_enInfoCacheType = enType;
	return TRUE;
}

BOOL CswTaggedChainsFile::WriteInfoToCache (enum SWCHAININFOTYPE enType)
{
	SWCHAININFOTYPE enNeededType;
	if (!m_pInfoCache)		
		return FALSE;		// шо ты собрался записывать, мудила?
	if (enType == m_enInfoCacheType)
		return TRUE;		// уже всё готово! отвали!

	switch (m_enInfoCacheType)
	{
	case CIT_NONE:
		enNeededType = enType;
		break;
	case CIT_BRIEF:
	case CIT_NODE:
		switch (enType)
		{
		case CIT_NODE:
		case CIT_FULL:
			enNeededType = CIT_NODE;
			enType = CIT_FULL;
		}
		break;
	case CIT_FULL:
		switch (enType)
		{
		case CIT_BRIEF:
			enNeededType = CIT_BRIEF;
			break;
		case CIT_NODE:
		case CIT_FULL:
			enNeededType = CIT_NODE;
			enType = CIT_FULL;
		}
	};

	DWORD dwWritten;
	switch (enNeededType)
	{
	case CIT_BRIEF:
		if ((dwWritten = Write (&(m_pInfoCache->brief), sizeof (m_pInfoCache->brief))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedChainOffset = GetSeekPos () - dwWritten;
		break;
	case CIT_FULL:
		if ((dwWritten = Write (&(m_pInfoCache->full), sizeof (m_pInfoCache->full))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedChainOffset = GetSeekPos () - dwWritten;
		m_dwCachedNodeOffset = m_dwCachedChainOffset + sizeof (m_pInfoCache->full.brief);
		break;
	case CIT_NODE:
		if ((dwWritten = Write (&(m_pInfoCache->full.node), sizeof (m_pInfoCache->full.node))) == EOF)
		{
			ClearInfoCache ();
			return FALSE;
		}
		m_dwCachedNodeOffset = GetSeekPos () - dwWritten;
		break;
	default:
		return FALSE;
	}
	m_enInfoCacheType = enType;
	return TRUE;
}

BOOL CswTaggedChainsFile::WalkNode ()
{
	return (ReadInfoToCache (CIT_FULL) && 
		m_pInfoCache->full.node.dwNextNode &&
		(SeekTo (m_pInfoCache->full.node.dwNextNode), ReadInfoToCache (CIT_NODE)));
}

BOOL CswTaggedChainsFile::WalkChain_noTypeCheck ()
{
	return (ReadInfoToCache (CIT_BRIEF) && 
		m_pInfoCache->brief.dwNextChain &&
		(SeekTo (m_pInfoCache->brief.dwNextChain), ClearInfoCache (), ReadInfoToCache (CIT_BRIEF)));
}


