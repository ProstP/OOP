#pragma once
#include <iostream>

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
	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList();
	void AddStrToBegin(const std::string& str);
	void AddStrToEnd(const std::string& str);
	void AddStrToPos(int pos, const std::string& str);
	void RemoveStrInPos(int pos);
	int GetCount();
	bool IsEmpty();
	void Clear();

	class iterator
	{
	public:
		iterator(Node* ptr);
		~iterator();
		Node& operator*();
		Node* operator->();
		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

	private:
		Node* m_ptr;
	};

	iterator begin();
	iterator end();

	iterator begin() const;
	iterator end() const;

private:
	int m_count;
	Node* m_firstPtr;
	Node* m_lastPtr;
};
