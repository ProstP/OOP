#include "CMyString.h"

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		length = 0;
	}
	m_length = length;
	m_capacity = length * 2;
	m_symbols = new char[m_capacity + 1];
	memcpy(m_symbols, pString, length);
	m_symbols[m_length] = END_OF_STRING;
}

CMyString::CMyString()
	: CMyString(nullptr, 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = 0;
	m_capacity = 0;
	delete[] m_symbols;
	m_symbols = new char[1];
	m_symbols[0] = END_OF_STRING;
	std::swap(m_length, other.m_length);
	std::swap(m_symbols, other.m_symbols);
	std::swap(m_capacity, other.m_capacity);
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_symbols;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

const char* CMyString::GetStringData() const
{
	return m_symbols;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start < 0 || start > m_length)
	{
		throw std::out_of_range("Start out of range");
	}
	if (length > m_length - start)
	{
		length = m_length - start;
	}

	return CMyString(&m_symbols[start], length);
}

void CMyString::Clear()
{
	delete[] m_symbols;
	m_length = 0;
	m_symbols = new char[1];
	m_symbols[0] = END_OF_STRING;
}

CMyString CMyString::operator+(const CMyString& other) const
{
	size_t newStrLen = this->GetLength() + other.GetLength();

	char* newStrSymbols = new char[newStrLen + 1];
	memcpy(newStrSymbols, this->GetStringData(), this->GetLength());
	memcpy(newStrSymbols + this->GetLength(), other.GetStringData(), other.GetLength());

	newStrSymbols[newStrLen] = END_OF_STRING;
	CMyString newMyString(newStrSymbols, newStrLen);
	delete[] newStrSymbols;
	return newMyString;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	size_t newStrLen = this->GetLength() + other.GetLength();
	if (m_capacity >= newStrLen)
	{
		memcpy(m_symbols + this->GetLength(), other.GetStringData(), other.GetLength());
	}
	else
	{
		while (m_capacity < newStrLen)
		{
			if (m_capacity == 0)
			{
				m_capacity = 2;
			}
			else
			{
				m_capacity *= 2;
			}
		}
		char* newStrSymbols = new char[m_capacity + 1];
		memcpy(newStrSymbols, this->GetStringData(), this->GetLength());
		memcpy(newStrSymbols + this->GetLength(), other.GetStringData(), other.GetLength());
		delete[] m_symbols;
		m_symbols = newStrSymbols;
	}

	m_symbols[newStrLen] = END_OF_STRING;
	m_length = newStrLen;

	return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
	if (this->GetLength() != other.GetLength())
	{
		return false;
	}

	return (memcmp(this->GetStringData(), other.GetStringData(), this->GetLength()) == 0);
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	size_t minLen = std::min(this->GetLength(), other.GetLength());
	return (memcmp(this->GetStringData(), other.GetStringData(), minLen) < 0);
}

bool CMyString::operator>(const CMyString& other) const
{
	size_t minLen = std::min(this->GetLength(), other.GetLength());
	return (memcmp(this->GetStringData(), other.GetStringData(), minLen) > 0);
}

bool CMyString::operator<=(const CMyString& other) const
{
	if (*this == other || *this < other)
	{
		return true;
	}

	return false;
}

bool CMyString::operator>=(const CMyString& other) const
{
	if (*this == other || *this > other)
	{
		return true;
	}

	return false;
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_length || index < 0)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_symbols[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length || index < 0)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_symbols[index];
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (std::addressof(other) != this)
	{
		CMyString copy(other.GetStringData(), other.GetLength());
		std::swap(m_symbols, copy.m_symbols);
		std::swap(m_length, copy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_symbols;
		m_length = 0;
		m_capacity = 0;
		m_symbols = new char[1];
		m_symbols[0] = END_OF_STRING;

		std::swap(m_symbols, other.m_symbols);
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);
	}

	return *this;
}

CMyString operator+(const CMyString& myStr, const std::string& str)
{
	return myStr + CMyString(str);
}

CMyString operator+(const std::string& str, const CMyString& myStr)
{
	return CMyString(str) + myStr;
}

CMyString operator+(const CMyString& myStr, const char* str)
{
	return myStr + CMyString(str);
}

CMyString operator+(const char* str, const CMyString& myStr)
{
	return CMyString(str) + myStr;
}

std::istream& operator>>(std::istream& in, CMyString& myString)
{
	size_t strCapicity = 1;
	size_t strLen = 0;
	char* str = new char[strCapicity];
	char ch;

	while (in.get(ch) && ch != ' ' && ch != '\n')
	{
		str[strLen] = ch;
		strLen++;
		if (strLen == strCapicity)
		{
			char* biggerStr = new char[strCapicity * 2];
			memcpy(biggerStr, str, strCapicity);
			delete[] str;
			str = biggerStr;
			strCapicity *= 2;
		}
	}
	str[strLen] = END_OF_STRING;

	delete[] myString.m_symbols;
	myString.m_length = strLen;
	myString.m_symbols = str;

	return in;
}

std::ostream& operator<<(std::ostream& out, CMyString& myString)
{
	out << myString.GetStringData();
	return out;
}
