#pragma once

template <class TYPE>
class CswRange
{
public:
	CswRange () : begin (0), end (0) { };
	CswRange (const TYPE& tbegin, const TYPE& tend) : begin (min (tbegin, tend)), end (max (tbegin, tend)) { };
	CswRange (const CswRange<TYPE>& range) : begin (range.begin), end (range.end) { };

	inline bool DoesIntersect (const CswRange<TYPE>& range) const
	{
		return ((begin <= range.end) && (range.begin <= end));
	}

	bool IntersectRange (const CswRange<TYPE>& range1, const CswRange<TYPE>& range2)
	{
		if (!range1.DoesIntersect (range2))
			return FALSE;		// they does not intersect
		begin = max(range1.begin, range2.begin);
		end = min(range1.end, range2.end);
		return TRUE;
	};

	inline void UnionRange (const CswRange<TYPE>& range1, const CswRange<TYPE>& range2)
	{
		begin = min(range1.begin, range2.begin);
		end = max(range1.end, range2.end);
	}

	inline TYPE Length ()
	{
		return end - begin;
	}

	
	TYPE begin;
	TYPE end;
};

template <class TYPE>
class CswRangeSet
{
	struct RSEntry
	{
		CswRange<TYPE> range;
		RSEntry* next;
	};
public:
	CswRangeSet () : m_root (NULL) {};
	CswRangeSet (const CswRangeSet<TYPE>& rangeSet) 
	{
		(*this) = rangeSet;
	};

	virtual ~CswRangeSet ()
	{
		RSEntry* pEntry = m_root; 
		while (pEntry)
		{
			RSEntry* pEntryNext = pEntry->next;
			delete pEntry;
			pEntry = pEntryNext;
		}
			
	}
	
	CswRangeSet<TYPE>& operator = (const CswRangeSet<TYPE>& rangeSet)
	{
		for (RSEntry* pEntry = rangeSet.m_root; pEntry; pEntry = pEntry->next)
		{
			RSEntry* pNewEntry = new RSEntry;
			pNewEntry->range = pEntry->range;
			pNewEntry->next = m_root;
			m_root = pNewEntry;
		}
		return (*this);
	}

	void AddRange (TYPE begin, TYPE end)
	{
		AddRange (CswRange<TYPE>(begin, end));
	}

	void AddRange (const CswRange<TYPE>& range)
	{
		for (RSEntry* pEntry = m_root; pEntry; pEntry = pEntry->next)
			if (pEntry->range.DoesIntersect (range))
			{
				pEntry->range.UnionRange (pEntry->range, range);
				SolveIntersections (pEntry);
				return;
			}
		pEntry = new RSEntry;
		pEntry->range = range;
		pEntry->next = m_root;
		m_root = pEntry;
	};
	
	void SubtractRange (TYPE begin, TYPE end)
	{
		SubtractRange (CswRange<TYPE>(begin, end));
	}

	void SubtractRange (const CswRange<TYPE>& range)
	{
		for (RSEntry* pEntry = m_root; pEntry; pEntry = pEntry->next)
		{
			if (pEntry->range.DoesIntersect (range))
			{
				if ((pEntry->range.begin < range.begin) && (pEntry->range.end > range.end))
				{
					// [......................pEntry->range.....................]
					// [...pEntry->range...][...range...][...pNewEntry->range...]
					RSEntry* pNewEntry = new RSEntry;
					pNewEntry->next = m_root;
					m_root = pNewEntry;
					pNewEntry->range.begin = range.end;
					pNewEntry->range.end = pEntry->range.end;
					pEntry->range.end = range.begin;
				}
				else
				{
					// [........pEntry->range.....[....]....range............]
					// [......pEntry->range.......]
					CswRange<TYPE> inter;
					inter.IntersectRange (pEntry->range, range);
					if (pEntry->range.begin < inter.begin)
						pEntry->range.end = inter.begin;
					else
						pEntry->range.begin = inter.end;
				}
			}
		}
		RemoveEmptyRanges ();
	};

	bool DoesIntersect (TYPE begin, TYPE end) const
	{
		return DoesIntersect (CswRange<TYPE>(begin, end));
	}

	bool DoesIntersect (const CswRange<TYPE>& range) const
	{
		for (RSEntry* pEntry = m_root; pEntry; pEntry = pEntry->next)
			if (pEntry->range.DoesIntersect (range))
				return true;
		return false;
	}

protected:
	RSEntry* m_root;

	void SolveIntersections (RSEntry* pEntry)
	{
		RSEntry* pLastEntry = NULL;
		for (RSEntry* pEntryFind = m_root; pEntryFind; pLastEntry = pEntryFind, pEntryFind = pEntryFind->next)
			if ((pEntryFind != pEntry) && (pEntry->range.DoesIntersect (pEntryFind->range)))
			{
				pEntry->range.UnionRange (pEntry->range, pEntryFind->range);
				if( pLastEntry )
					pLastEntry->next = pEntryFind->next;
				else
					m_root = pEntryFind->next;
				delete pEntryFind;
				SolveIntersections (pEntry);
				return;
			}
	}

	void RemoveEmptyRanges ()
	{
		RSEntry* pLastEntry = NULL;
		for (RSEntry* pEntryFind = m_root; pEntryFind; pLastEntry = pEntryFind)
			if (!pEntryFind->range.Length ())
			{
				if( pLastEntry )
					pLastEntry->next = pEntryFind->next;
				else
					m_root = pEntryFind->next;
				RSEntry* pEntryNext = pEntryFind->next;
				if (m_root = pEntryFind)
					m_root = pEntryNext;
				delete pEntryFind;
				pEntryFind = pEntryNext;
			}
			else
				pEntryFind = pEntryFind->next;
	}
};
