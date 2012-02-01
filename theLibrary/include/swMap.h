// swMap.h: interface for the CswMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWMAP_H__23611175_6DDC_46A9_8CBD_AE3C84576B43__INCLUDED_)
#define AFX_SWMAP_H__23611175_6DDC_46A9_8CBD_AE3C84576B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include <wchar.h>

/*	пример использования *
// объявление
CswMap <UINT, UINT> swMap;

  // добавление
  swMap [uKey] = uValue;
  
	// поиск 1 
	if (swMap.IsSet(uKey)) { UINT uValue = swMap [uKey]; ... }
	
	  // поиск 2
	  UINT *pValue;
	  if (pValue = swMap.Lookup (uKey)) { ... }
	  
		// удаление
		swMap.UnSet (123);
		
		  // перебор (неупорядоченный!)
		  UINT* puKey;
		  for (UINT* puVal = swMap.Reset (&puKey) ; puVal ; puVal = swMap.Next (&puKey))
		  { ... }
*/
typedef unsigned int UINT;

#if !defined IN
#define IN
#endif
#if !defined OUT
#define OUT
#endif

template<class Key, class Value>
class CswMap  
{
protected:
	struct BucketEntry
	{
		Value m_Value;
		Key		m_Key;
		BucketEntry *m_pNext;
	};
	
	void Init (UINT uBucketArrayLength = 1024)
	{
		m_uArrLength = uBucketArrayLength;
		m_pEntries = new BucketEntry*[m_uArrLength];	
		for( UINT i = 0; i < m_uArrLength; i++ )
		{
			m_pEntries[i] = NULL;
		}
		m_uCount = 0;
		m_idxTable = 0; 
		m_idxList = NULL;
	}	

public:
	CswMap()									{ Init ();	}
	CswMap(UINT uBucketArrayLength)				{ Init (uBucketArrayLength);}
	CswMap(const CswMap<Key, Value> &swMap)		{ Init (); (*this) += swMap; }
	
	virtual ~CswMap()
	{
		Clear ();
		delete [] m_pEntries;
		m_pEntries = NULL;
	}
	
	
	Value* Lookup (IN const Key &key) const
	{
		UINT uHash = HashIt( key ) % m_uArrLength;	
		BucketEntry *pEntry = Find( uHash , key);
		if (pEntry)
			return &(pEntry->m_Value);
		return NULL;
	}
	
	Value& operator [] (IN const Key &key)
	{
		UINT uHash = HashIt( key ) % m_uArrLength;	
		BucketEntry	*pEntry = Find( uHash , key);
		
		if( pEntry==NULL )
		{
			pEntry = new BucketEntry;
			pEntry -> m_Key = key;
			BucketEntry	*pRootEntry = m_pEntries[uHash];
			m_pEntries[uHash] = pEntry;
			m_uCount++;
			if( pRootEntry )
				pEntry -> m_pNext = pRootEntry;
			else
				pEntry -> m_pNext = NULL;
		}
		return pEntry -> m_Value;
	}
	
	bool __inline IsSet (const Key& key) const
	{
		if (!Lookup (key))
			return false;
		return true;
	}
	
	bool UnSet (const Key &key)
	{
		UINT uHash = HashIt (key) % m_uArrLength;
		BucketEntry *pEntry;
		if (pEntry = RemoveFromList (uHash, key))
		{
			delete pEntry;
			m_uCount--;
			return true;
		}
		return false;
	}
	
	void Clear ()
	{
		if( m_uCount )
		{
			for( UINT i = 0; i < m_uArrLength; i++ )
			{
				BucketEntry *pEntry = m_pEntries[i];
				while( pEntry )
				{
					BucketEntry *pEntryNext = pEntry -> m_pNext;
					delete pEntry;
					pEntry = pEntryNext;
				}
				
				m_pEntries[i] = NULL;
			}
			
			m_uCount = 0;
		}
	}
	
	UINT Count() const 
	{ 
		return m_uCount; 
	};
	
	void Remap (const Key& fromKey, const Key& toKey)
	{
		UINT uHash = HashIt (fromKey) % m_uArrLength;		
		BucketEntry *pEntry, *pDeadEntry, *pRootEntry;
		if (pEntry = RemoveFromList (uHash, fromKey))
		{
			uHash = HashIt( toKey ) % m_uArrLength;
			if (pDeadEntry = RemoveFromList (uHash, toKey))
			{
				delete pDeadEntry;
				m_uCount--;
			}
			pEntry->m_Key = toKey;					
			pRootEntry = m_pEntries[uHash];
			m_pEntries[uHash] = pEntry;
			if( pRootEntry )
				pEntry -> m_pNext = pRootEntry;
			else
				pEntry -> m_pNext = NULL;					
		}
	};

	CswMap<Value, Key> Flip () const
	{
		CswMap<Value, Key> mapFlipped;
		if( m_uCount )
			for( UINT i = 0; i < m_uArrLength; i++ )
				for (BucketEntry *pEntry = m_pEntries[i] ; pEntry ; pEntry = pEntry->m_pNext)
					mapFlipped[pEntry->m_Value] = pEntry->m_Key;
		return mapFlipped;
	}
	
	Value* Reset (OUT Key** ppKey = NULL) const
	{
		const_cast< CswMap <Key, Value>* >(this)->m_idxTable = 0; 
		const_cast< CswMap <Key, Value>* >(this)->m_idxList = NULL;
		return Next (ppKey);
	};
	
	Value* Next (OUT Key** ppKey = NULL) const
	{
		if (m_uCount)
		{
			while (m_idxTable < m_uArrLength)
			{
				if (!m_idxList)
					const_cast< CswMap <Key, Value>* >(this)->m_idxList = m_pEntries [m_idxTable];
				while (m_idxList)
				{
					Value* retVal = &(m_idxList->m_Value);
					if (ppKey)
						*ppKey = &(m_idxList->m_Key);
					const_cast< CswMap <Key, Value>* >(this)->m_idxList = m_idxList->m_pNext;
					if (!m_idxList)
						const_cast< CswMap <Key, Value>* >(this)->m_idxTable++;
					return retVal;
				}
				const_cast< CswMap <Key, Value>* >(this)->m_idxTable++;
			}				
		}
		return NULL;
	}
	
	CswMap<Key, Value>& operator = (const CswMap<Key, Value>& swMap)
	{
		Clear ();
		return (*this) += swMap;
	}
	
	CswMap<Key, Value>& operator += (const CswMap<Key, Value>& swMap)
	{
		if( swMap.m_uCount )
			for( UINT i = 0; i < swMap.m_uArrLength; i++ )
				for( BucketEntry *pEntry = swMap.m_pEntries[i]; pEntry != NULL; pEntry = pEntry -> m_pNext )
					(*this)[pEntry->m_Key] = pEntry->m_Value;
		return (*this);
	}
	
	friend CswMap<Key, Value> operator + (CswMap<Key, Value>& op1, CswMap<Key, Value>& op2)
	{
		CswMap<Key, Value> res = op1;
		res += op2;
		return res;
	}
	
	
protected:
	UINT m_uArrLength;
	BucketEntry** m_pEntries;
	UINT m_uCount;
	
	UINT m_idxTable;			// Table-through iterator
	BucketEntry* m_idxList;		// List-trough iterator
	
	BucketEntry* Find (UINT uHash, const Key &key) const
	{
		for( BucketEntry *pEntry = m_pEntries[uHash]; pEntry != NULL; pEntry = pEntry -> m_pNext )
		{
			if( ElementsTheSame( pEntry -> m_Key, key ) )
			{
				return pEntry;
			}
		}
		return NULL;
	}
	
	BucketEntry* RemoveFromList (UINT uHash, const Key &key)
	{
		BucketEntry *pLastItem = NULL;
		for( BucketEntry *pEntry = m_pEntries[uHash]; pEntry != NULL; pLastItem = pEntry, pEntry = pEntry -> m_pNext )
		{
			if( ElementsTheSame( pEntry -> m_Key, key ) )
			{
				if( pLastItem )
				{
					pLastItem -> m_pNext = pEntry -> m_pNext;
				}
				else
				{
					m_pEntries[uHash] = pEntry -> m_pNext;
				}
				return pEntry;
			}
		}
		return NULL;
	}
};

//////////////////////////////////////////////////////////////////////
// ELEMENTS COMPARISON FUNCTIONS
//////////////////////////////////////////////////////////////////////


template<class Key>
inline bool ElementsTheSame(const Key &lhs, const Key &rhs)
{
	return const_cast<Key&>(lhs) == const_cast<Key&> (rhs);
}

template<>
inline bool ElementsTheSame<char*> (char* const &lhs, char* const &rhs)
{
	return strcmp(lhs, rhs) == 0;
//	return stricmp(pcszLHS, pcszRHS) == 0;
}

template<>
inline bool ElementsTheSame<wchar_t*> (wchar_t* const& pcszLHS, wchar_t* const& pcszRHS)
{
	return wcscmp(pcszLHS, pcszRHS) == 0;
//	return wcsicmp(pcszLHS, pcszRHS) == 0;
}


//////////////////////////////////////////////////////////////////////
// HASH FUNCTIONS COLLECTION
//////////////////////////////////////////////////////////////////////

template<class Key>
inline UINT HashIt(Key const& key)
{
	return ((UINT) key);
}


template<>
inline UINT HashIt<char*>(char* const& pcszText)
{
	UINT uHash = 0;
	char* psz = pcszText;
	while(*psz)
		uHash = uHash << 1 ^ (UINT)(*psz++);
//		uHash = uHash << 1 ^ (UINT)toupper(*psz++);
	
	return uHash;
}

template<>
inline UINT HashIt<wchar_t*>(wchar_t* const& pcszText)
{
	UINT uHash = 0;
	wchar_t* psz = pcszText;
	while(*psz)
		uHash = uHash << 1 ^ (UINT)(*psz++);
	
	return uHash;
}

//////////////////////////////////////////////////////////////////////
// CswArray class
//////////////////////////////////////////////////////////////////////

template<class Value>
class CswArray : public CswMap<UINT, Value>
{
public:
	CswArray()									{ }
	CswArray(UINT uBucketArrayLength)			{ }
	CswArray(const CswArray<Value> &swMap)		{  (*this) += swMap; }
	
	UINT Push (const Value& val)
	{
		UINT iNew = m_uCount;
		(*this)[iNew] = /*const_cast<Value&>*/(val);
		return iNew;
	}
	
	bool Pop (Value& val)
	{
		Value* pVal;
		if ((!m_uCount) || (!(pVal = Lookup (m_uCount - 1))))
			return false;
        val = *pVal;
		UnSet (m_uCount - 1);
		return true;
	}

	bool Pop ()
	{
		return UnSet (m_uCount - 1);		
	}
	
	void Unshift (const Value& val)
	{
		for (UINT i = m_uCount; i > 0; i--)
			Remap (i - 1, i);
		(*this)[0] = const_cast<Value&>(val);
	}
	
	bool Shift (Value& val)
	{
		Value* pVal;
		if ((!m_uCount) || (!(pVal = Lookup (0))))
			return false;
		val = *pVal;
		UnSet (0);
		for (UINT i = 0; i < m_uCount; i++)
			Remap (i + 1, i); 
		return true;
	}

	bool Shift ()
	{
		if( ( !m_uCount ) || ( !UnSet( 0 ) ) )
			return false;
		for (UINT i = 0; i < m_uCount; i++)
			Remap (i + 1, i); 
		return true;
	}

	bool PopAt (IN const UINT& key, OUT Value& val)
	{
		Value* pVal;
		if ((!m_uCount) || (!(pVal = Lookup (key))))
			return false;
        val = *pVal;
		UnSet (key);
		for (UINT i = key; i < m_uCount; i++)
			Remap (i + 1, i); 
		return true;		
	}

	UINT PushAt (IN const UINT& key, IN const Value& val)
	{
		if (key >= m_uCount)
			return Push( val );
		for (UINT i = m_uCount; i > key; i--)
			Remap (i - 1, i);
		(*this)[key] = val;
		return key;
	}
	
	bool SearchValue ( IN const Value& val, IN OUT UINT& key )
	{
		for (UINT i = key; i < m_uCount; i++)
			if( ElementsTheSame( (*this)[i], val ) )
			{
				key = i;
				return true;
			}
		return false;		
	}

	Value* GetFirst () const
	{
		return Lookup (0);
	}
	
	Value* GetLast () const
	{
		return Lookup (m_uCount - 1);
	}

	CswArray<Value>& operator = (const CswArray<Value>& swMap)
	{
		Clear ();
		return (*this) += swMap;
	}
	
	CswArray<Value>& operator += (const CswArray<Value>& swMap)
	{
		for (UINT i = 0; i < swMap.m_uCount; i++)
			Push (const_cast< CswArray<Value>& >(swMap)[i]);
		return (*this);
	}
	
	CswArray<Value>& operator += (const CswMap<UINT, Value>& swMap)
	{
		UINT cEntries;
		if ( cEntries = swMap.Count () )
		{
			UINT iEntry = 0;
			BucketEntry** rgpEntries = new BucketEntry* [cEntries];
			UINT* puKey;
			for ( Value* pVal = swMap.Reset (&puKey) ; pVal ; pVal = swMap.Next (&puKey), iEntry++ )
			{
				rgpEntries[iEntry] = new BucketEntry;
				rgpEntries[iEntry]->m_Key = *puKey;
				rgpEntries[iEntry]->m_Value = *pVal;
			}
			qsort (rgpEntries, cEntries, sizeof (*rgpEntries), qSortCallback);
			for (iEntry = 0; iEntry < cEntries; iEntry++)
			{
				Push (rgpEntries[iEntry]->m_Value);
				delete rgpEntries[iEntry];
			}
		}
		
		return (*this);
	}

	static int qSortCallback (const void* p1, const void* p2)
	{
		return ((*((const BucketEntry**)(p1)))->m_Key - (*((const BucketEntry**)(p2)))->m_Key);
			
	}

	friend CswArray<Value> operator + (CswArray<Value>& op1, CswArray<Value>& op2)
	{
		CswArray<Value> res = op1;
		res += op2;
		return res;
	}
};

#endif // !defined(AFX_SWMAP_H__23611175_6DDC_46A9_8CBD_AE3C84576B43__INCLUDED_)
