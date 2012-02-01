// SWLists.h
// --------------
// Copyright (c) by SeekWood Corp.
// All rights reserved.
//////////////////////////////////////////////////////////////////////
// Created on 04/12/2001 by Yarik.

#if !defined __SWLINKEDLIST_H__E829B657_C6A4_4738_9382_9015F80AE7C7_INCLUDED__
#define __SWLINKEDLIST_H__E829B657_C6A4_4738_9382_9015F80AE7C7_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


template <class TYPE>
class CSWOneWayList
{
	struct ListNode
	{
		TYPE Item;
		ListNode* pNext;
	};
public:
	CSWOneWayList ();
	virtual ~CSWOneWayList ();

	void Add (TYPE Item);
	TYPE& Item (UINT uIdx);
	UINT Count ();
	void Remove (UINT uIdx);
	void Empty ();

	TYPE& operator [] (UINT uIdx) {return Item (uIdx);}

	TYPE& Reset (TYPE& idEOL);
	TYPE& Next (TYPE& idEOL);	
protected:
	UINT m_cNodes;
	ListNode* m_pRoot;
	ListNode* m_pLast;
	ListNode* m_pCurrent;
	UINT m_uCurrentIdx;
	ListNode* FindNode (UINT uIdx);
};

//typedef CSWOneWayList<class TYPE> SWLIST1<class TYPE>, *LPSWLIST1<class TYPE>;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template <class TYPE>
CSWOneWayList<TYPE>::CSWOneWayList () :
	m_cNodes (0),
	m_pRoot (NULL),
	m_pLast (NULL),
	m_pCurrent (NULL),
	m_uCurrentIdx (0)
{
}

template <class TYPE>
CSWOneWayList<TYPE>::~CSWOneWayList ()
{
	Empty ();
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
void CSWOneWayList<TYPE>::Add (TYPE Item)
{
	ListNode* pNewNode = new ListNode;
	pNewNode->Item = Item;
	pNewNode->pNext = NULL;
	
	if (m_pLast)
		m_pLast->pNext = pNewNode;
	m_pLast = pNewNode;
	if (!m_pRoot)
		m_pRoot = pNewNode;
	
	m_pCurrent = pNewNode;
	m_uCurrentIdx = m_cNodes;

	m_cNodes++;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
TYPE& CSWOneWayList<TYPE>::Item (UINT uIdx)
{
	ListNode* pNode = FindNode (uIdx);
	return pNode->Item;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
UINT CSWOneWayList<TYPE>::Count ()
{
	return m_cNodes;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
void CSWOneWayList<TYPE>::Remove (UINT uIdx)
{
	if (uIdx >= m_cNodes)
		return;

	ListNode *pNode, *pPending;
	if (uIdx == 0) // Removing root element
	{
		pNode = NULL;
		pPending = m_pRoot;
		m_pRoot = m_pRoot->pNext;
	}
	else
	{
		pNode = FindNode (uIdx - 1);
		pPending = pNode->pNext;
	}

	if (pPending)
	{
		if (pNode)
			pNode->pNext = pPending->pNext;
		if (pPending == m_pLast)
			m_pLast = pNode;
		delete pPending;
		m_cNodes--;
	}
	m_pCurrent = m_pRoot;
	m_uCurrentIdx = 0;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
void CSWOneWayList<TYPE>::Empty ()
{
	ListNode* pPending;
	for (ListNode* pNode = m_pRoot ; pNode != NULL ; pPending = pNode, pNode = pNode->pNext, delete pPending);
	m_pRoot = m_pLast = m_pCurrent = NULL;
	m_uCurrentIdx = m_cNodes = 0;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
CSWOneWayList<TYPE>::ListNode* CSWOneWayList<TYPE>::FindNode (UINT uIdx)
{
	if (uIdx < m_cNodes)
	{	
		if (uIdx < m_uCurrentIdx)
		{
			m_uCurrentIdx = 0;
			m_pCurrent = m_pRoot;
		}
		
		UINT uFoundIdx = m_uCurrentIdx;
		for (ListNode* pNode = m_pCurrent; pNode != NULL ; pNode = pNode->pNext, uFoundIdx++)
			if (uFoundIdx == uIdx)
			{
				if (uFoundIdx - m_uCurrentIdx != 1)
				{
					m_uCurrentIdx = uFoundIdx;
					m_pCurrent = pNode;
				}
				return pNode;
			}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
TYPE& CSWOneWayList<TYPE>::Reset (TYPE& idEOL)
{
	m_pCurrent = m_pRoot; 
	m_uCurrentIdx = 0;
	if (m_pCurrent)
		return m_pCurrent->Item;
	return idEOL;
}

//////////////////////////////////////////////////////////////////////

template <class TYPE>
TYPE& CSWOneWayList<TYPE>::Next (TYPE& idEOL)
{ 
	if (m_pCurrent)
	{
		m_pCurrent = m_pCurrent->pNext ; m_uCurrentIdx++; 
	}
	
	if (m_pCurrent)
		return m_pCurrent->Item;
	return idEOL;
}

//////////////////////////////////////////////////////////////////////

#endif //!defined __SWLINKEDLIST_H__E829B657_C6A4_4738_9382_9015F80AE7C7_INCLUDED__