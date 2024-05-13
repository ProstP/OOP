#pragma once
#include <iostream>

const char END_OF_STRING = '\0';

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
	size_t GetCapacity() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString operator+(const CMyString& other) const;
	friend CMyString operator+(const CMyString& myStr, const std::string& str);
	friend CMyString operator+(const std::string& str, const CMyString& myStr);
	friend CMyString operator+(const CMyString& myStr, const char* str);
	friend CMyString operator+(const char* str, const CMyString& myStr);
	CMyString& operator+=(const CMyString& other);
	bool operator==(const CMyString& other) const;
	bool operator!=(const CMyString& other) const;
	bool operator<(const CMyString& other) const;
	bool operator>(const CMyString& other) const;
	bool operator<=(const CMyString& other) const;
	bool operator>=(const CMyString& other) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::istream& operator>>(std::istream& in, CMyString& myString);
	friend std::ostream& operator<<(std::ostream& out, CMyString& myString);

private:
	char* m_symbols;
	size_t m_length;
	size_t m_capacity;
};
