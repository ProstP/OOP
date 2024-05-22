#include <iostream>
#include "CStringList.h"

CStringList::CStringList()
{
	m_count = 0;
	m_firstPtr = nullptr;
	m_lastPtr == nullptr;
}

CStringList::CStringList(const CStringList& other)
{
	m_count = other.m_count;
}

CStringList::CStringList(const CStringList&& other) noexcept
{
}
