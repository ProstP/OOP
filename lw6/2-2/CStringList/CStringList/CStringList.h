#pragma once
#include <iostream>
#include "CStringListOutOfRangeError.h"

struct Node
{
	std::string str;
	Node* next = nullptr;
	Node* prev = nullptr;
	bool operator==(const Node& other) { return (str == other.str && next == other.next && prev == other.prev); };
	bool operator!=(const Node& other) { return (str != other.str || next != other.next || prev != other.prev); };
};

class CStringList
{
public:
	class iterator : public std::iterator<std::input_iterator_tag, Node>
	{
	public:
		typedef CStringList::iterator self_type;
		typedef std::string value_type;
		typedef std::string& references;
		typedef Node* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int differneces_type;

		iterator()
			: m_ptr{ nullptr } {};
		iterator(Node* ptr);
		~iterator();

		references operator*();
		pointer operator->();
		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
		iterator& operator++();
		iterator operator++(int);//const
		iterator& operator+=(int value);
		iterator& operator--();
		iterator operator--(int);
		iterator& operator-=(int value);
		iterator operator+(int value);
		iterator operator-(int value);

	private:
		Node* m_ptr;
	};

	class reverse_iterator : public std::reverse_iterator<CStringList::iterator>
	{
	public:
		reverse_iterator()
			: m_ptr{ nullptr } {};
		reverse_iterator(Node* ptr);
		~reverse_iterator();
		std::string operator*();
		Node* operator->();
		bool operator==(const reverse_iterator& other);
		bool operator!=(const reverse_iterator& other);
		reverse_iterator& operator++();
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);

	private:
		Node* m_ptr;
	};

	typedef iterator iterator;

	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList();
	void AddStrToBegin(const std::string& str);
	void AddStrToEnd(const std::string& str);
	void AddStrToPos(CStringList::iterator pos, const std::string& str);
	void RemoveStrInPos(CStringList::iterator pos);
	int GetCount() const;
	bool IsEmpty() const; 
	void Clear();

	std::string operator[](int index);

	iterator begin();
	iterator end();

	iterator begin() const;
	iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	reverse_iterator rbegin() const;
	reverse_iterator rend() const;

private:
	int m_count;
	Node* m_firstPtr;
	Node* m_lastPtr;
};
