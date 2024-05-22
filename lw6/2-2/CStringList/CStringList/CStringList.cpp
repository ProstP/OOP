#include "CStringList.h"

CStringList::CStringList()
{
	m_count = 0;
	m_firstPtr = nullptr;
	m_lastPtr = nullptr;
}

CStringList::CStringList(const CStringList& other)
{
	m_count = other.m_count;

	for (auto& str : other)
	{
		AddStrToEnd(str.str);
	}
}

CStringList::CStringList(CStringList&& other) noexcept
{
	m_count = 0;
	m_firstPtr = nullptr;
	m_lastPtr == nullptr;
	std::swap(m_count, other.m_count);
	std::swap(m_firstPtr, other.m_firstPtr);
	std::swap(m_lastPtr, other.m_lastPtr);
}

CStringList::~CStringList()
{
}

void CStringList::AddStrToBegin(const std::string& str)
{
	Node node;
	node.str;
	if (m_firstPtr == nullptr)
	{
		m_firstPtr = &node;
		m_lastPtr = &node;
	}
	else
	{
		node.next = m_firstPtr;
		m_firstPtr = &node;
	}
}

void CStringList::AddStrToEnd(const std::string& str)
{
	Node node;
	node.str = str;
	if (m_firstPtr == nullptr)
	{
		m_firstPtr = &node;
		m_lastPtr = &node;
	}
	else
	{
		node.prev = m_lastPtr;
		m_lastPtr = &node;
	}
}

void CStringList::AddStrToPos(int pos, const std::string& str)
{
}

void CStringList::RemoveStrInPos(int pos)
{
}

int CStringList::GetCount()
{
	return m_count;
}

bool CStringList::IsEmpty()
{
	return (m_count == 0);
}

void CStringList::Clear()
{
	while (m_lastPtr != nullptr)
	{
		Node* temp;
		temp = m_lastPtr;
		m_lastPtr = m_lastPtr->prev;
		delete temp;
	}
	m_count = 0;
	m_firstPtr = nullptr;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstPtr);
}

CStringList::iterator CStringList::end()
{
	return iterator(m_lastPtr);
}

CStringList::iterator CStringList::begin() const
{
	return iterator(m_firstPtr);
}

CStringList::iterator CStringList::end() const
{
	return iterator(m_lastPtr);
}

CStringList::iterator::iterator(Node* ptr)
	: m_ptr{ ptr }
{
}

CStringList::iterator::~iterator()
{
	delete m_ptr;
}

Node& CStringList::iterator::operator*()
{
	return *m_ptr;
}

Node* CStringList::iterator::operator->()
{
	return m_ptr;
}

bool CStringList::iterator::operator==(const iterator& other)
{
	return (*this->m_ptr == *other.m_ptr);
}

bool CStringList::iterator::operator!=(const iterator& other)
{
	return (*this->m_ptr != *other.m_ptr);
}

CStringList::iterator& CStringList::iterator::operator++()
{
	if (this->m_ptr->next == nullptr)
	{
		std::cout << "Караул!!";
	}
	*this = this->m_ptr->next;
}

CStringList::iterator CStringList::iterator::operator++(int)
{
	iterator temp(*this);
	++temp;
	return temp;
}

CStringList::iterator& CStringList::iterator::operator--()
{
	if (this->m_ptr->prev == nullptr)
	{
		std::cout << "Караул!!";
	}
	*this = this->m_ptr->prev;
}

CStringList::iterator CStringList::iterator::operator--(int)
{
	iterator temp(*this);
	--temp;
	return temp;
}
