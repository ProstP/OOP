#include "CMyString.h"

CMyString::CMyString()
{
}

CMyString::CMyString(const char* pString)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
}

CMyString::CMyString(CMyString const& other)
{
}

CMyString::CMyString(CMyString&& other) noexcept
{
}

CMyString::CMyString(const std::string& stlString)
{
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return size_t();
}

const char* CMyString::GetStringData() const
{
	return nullptr;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	return CMyString();
}

void CMyString::Clear()
{
}

size_t CMyString::GetCapacity()
{
	return size_t();
}
