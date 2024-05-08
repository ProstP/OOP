#pragma once
#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(const std::string& stlString);
	~CMyString();
	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	size_t GetCapacity();

private:
	char* m_symbols;
	size_t m_length;
	size_t m_capicity;
};
