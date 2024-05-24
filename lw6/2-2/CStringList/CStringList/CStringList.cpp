#include "CStringList.h"

CStringList::CStringList()
{
	m_count = 0;
	m_firstPtr = nullptr;
	m_lastPtr = new Node;
}

CStringList::CStringList(const CStringList& other)
{
	m_count = other.m_count;

	for (const auto& str : other)
	{
		AddStrToEnd(str);
	}
}

CStringList::CStringList(CStringList&& other) noexcept
{
	m_count = 0;
	m_firstPtr = nullptr;
	m_lastPtr = nullptr;
	std::swap(m_count, other.m_count);
	std::swap(m_firstPtr, other.m_firstPtr);
	std::swap(m_lastPtr, other.m_lastPtr);
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::AddStrToBegin(const std::string& str)
{
	Node* ptr;
	ptr = new Node;
	ptr->str = str;
	if (m_firstPtr == nullptr)
	{
		m_firstPtr = ptr;
		ptr->next = m_lastPtr;
		m_lastPtr->prev = m_firstPtr;
	}
	else
	{
		m_firstPtr->prev = ptr;
		ptr->next = m_firstPtr;
		m_firstPtr = ptr;
	}
	m_count++;
}

void CStringList::AddStrToEnd(const std::string& str)
{
	Node* ptr;
	ptr = new Node;
	ptr->str = str;
	if (m_firstPtr == nullptr)
	{
		m_firstPtr = ptr;
		ptr->next = m_lastPtr;
		m_lastPtr->prev = m_firstPtr;
	}
	else
	{
		Node* prev = m_lastPtr->prev;
		prev->next = ptr;
		ptr->prev = prev;
		ptr->next = m_lastPtr;
		m_lastPtr->prev = ptr;
	}
	m_count++;
}

void CStringList::AddStrToPos(CStringList::iterator pos, const std::string& str)
{
	if (pos == m_lastPtr)
	{
		AddStrToEnd(str);
		return;
	}
	if (pos == m_firstPtr)
	{
		AddStrToBegin(str);
		return;
	}
	Node* ptr;
	ptr = new Node;
	ptr->str = str;

	Node* prev;
	prev = pos->prev;
	ptr->next = prev->next;
	ptr->prev = prev;
	prev->next = ptr;
	pos->prev = ptr;
	m_count++;
}

void CStringList::RemoveStrInPos(CStringList::iterator pos)
{
	if (pos == m_lastPtr)
	{
		throw CStringListOutOfRangeError("Position to remove out of range");
	}
	if (pos == m_firstPtr)
	{
		m_firstPtr = pos->next;
	}
	else
	{
		Node* next;
		Node* prev;
		next = pos->next;
		prev = pos->prev;
		next->prev = prev;
		prev->next = next;
	}
	pos->next = nullptr;
	pos->prev = nullptr;
	delete pos->prev;
	delete pos->next;
	m_count--;
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

std::string CStringList::operator[](int index)
{
	return *(begin() + index);
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

CStringList::reverse_iterator CStringList::rbegin()
{
	return reverse_iterator(m_lastPtr);
}

CStringList::reverse_iterator CStringList::rend()
{
	return reverse_iterator(m_firstPtr);
}

CStringList::reverse_iterator CStringList::rbegin() const
{
	return reverse_iterator(m_lastPtr);
}

CStringList::reverse_iterator CStringList::rend() const
{
	return reverse_iterator(m_firstPtr);
}

CStringList::iterator::iterator(Node* ptr)
	: m_ptr{ ptr }
{
}

CStringList::iterator::~iterator()
{
	m_ptr = nullptr;
	delete m_ptr;
}

std::string CStringList::iterator::operator*()
{
	return m_ptr->str;
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
		throw CStringListOutOfRangeError("Can not increament, iterator to last element");
	}
	this->m_ptr = this->m_ptr->next;
	return *this;
}

CStringList::iterator CStringList::iterator::operator++(int)
{
	iterator temp(*this);
	++temp;
	return temp;
}

CStringList::iterator& CStringList::iterator::operator+=(int value)
{
	for (int i = 0; i < value; i++)
	{
		++*this;
	}

	return *this;
}

CStringList::iterator& CStringList::iterator::operator--()
{
	if (this->m_ptr->prev == nullptr)
	{
		throw CStringListOutOfRangeError("Can not deacreament, iterator to first element");
	}
	this->m_ptr = this->m_ptr->prev;
	return *this;
}

CStringList::iterator CStringList::iterator::operator--(int)
{
	iterator temp(*this);
	--temp;
	return temp;
}

CStringList::iterator& CStringList::iterator::operator-=(int value)
{
	for (int i = 0; i < value; i++)
	{
		--* this;
	}

	return *this;
}

CStringList::iterator CStringList::iterator::operator+(int value)
{
	iterator iter(*this);
	return iter += value;
}

CStringList::iterator CStringList::iterator::operator-(int value)
{
	iterator iter(*this);
	return iter -= value;
}

CStringList::reverse_iterator::reverse_iterator(Node* ptr)
	: m_ptr{ ptr }
{
}

CStringList::reverse_iterator::~reverse_iterator()
{
	m_ptr = nullptr;
	delete m_ptr;
}

std::string CStringList::reverse_iterator::operator*()
{
	return m_ptr->str;
}

Node* CStringList::reverse_iterator::operator->()
{
	return m_ptr;
}

bool CStringList::reverse_iterator::operator==(const reverse_iterator& other)
{
	return (*this->m_ptr == *other.m_ptr);
}

bool CStringList::reverse_iterator::operator!=(const reverse_iterator& other)
{
	return (*this->m_ptr != *other.m_ptr);
}

CStringList::reverse_iterator& CStringList::reverse_iterator::operator++()
{
	if (this->m_ptr->prev == nullptr)
	{
		throw CStringListOutOfRangeError("Can not increament, iterator to last element");
	}
	this->m_ptr = this->m_ptr->prev;
	return *this;
}

CStringList::reverse_iterator CStringList::reverse_iterator::operator++(int)
{
	reverse_iterator temp(*this);
	++temp;
	return temp;
}

CStringList::reverse_iterator& CStringList::reverse_iterator::operator--()
{
	if (this->m_ptr->next == nullptr)
	{
		throw CStringListOutOfRangeError("Can not deacreament, iterator to first element");
	}
	this->m_ptr = this->m_ptr->next;
	return *this;
}

CStringList::reverse_iterator CStringList::reverse_iterator::operator--(int)
{
	reverse_iterator temp(*this);
	--temp;
	return temp;
}
