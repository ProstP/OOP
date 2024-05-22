#pragma once
struct Node
{
	std::string str;
	Node* next = nullptr;
	Node* prev = nullptr;
};

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList& other);
	CStringList(const CStringList&& other) noexcept;
	void AddStrToBegin(const std::string& str);
	void AddStrToEnd(const std::string& str);
	int GetCount();

	class iterator
	{
	public:
		iterator();
		~iterator();

	private:
		Node* ptr;
	};

private:
	int m_count;
	Node* m_firstPtr;
	Node* m_lastPtr;
};

