#pragma once
#include <iostream>

template <typename T>
class CMyArray
{
public:
	CMyArray()
		: m_count{ 0 }
		, m_capacity{ 2 }
	{
		m_data = new T[m_capacity]();
		m_data[m_count] = T();
	};
	CMyArray(const CMyArray& other)
	{
		m_capacity = other.m_capacity;
		m_count = other.m_count;
		m_data = new T[m_capacity];
		for (size_t i = 0; i < m_capacity; i++)
		{
			m_data[i] = other.m_data[i];
		}
	};
	CMyArray(CMyArray&& other) noexcept
	{
		m_data = new T[m_capacity];
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_count, other.m_count);
		std::swap(m_data, other.m_data);
	};
	~CMyArray()
	{
		delete[] m_data;
	};

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& references;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int differneces_type;

		iterator(T* ptr)
			: m_ptr{ ptr } {};
		~iterator()
		{
			m_ptr = nullptr;
		};

		references operator*()
		{
			return *m_ptr;
		};
		pointer operator->()
		{
			return m_ptr;
		};
		bool operator==(const self_type& other) const
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const self_type& other) const
		{
			return m_ptr != other.m_ptr;
		}
		self_type& operator++()
		{
			++m_ptr;
			return *this;
		};
		self_type operator++(int)
		{
			iterator temp(*this);
			++(*this);
			return temp;
		};
		self_type& operator--()
		{
			--m_ptr;
			return *this;
		};
		self_type operator--(int)
		{
			iterator temp(*this);
			--(*this);
			return temp;
		};

	private:
		T* m_ptr;
	};

	class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef reverse_iterator self_type;
		typedef T value_type;
		typedef T& references;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int differneces_type;

		reverse_iterator(T* ptr)
			: m_ptr{ ptr } {};
		~reverse_iterator()
		{
			m_ptr = nullptr;
		};

		references operator*()
		{
			return *m_ptr;
		};
		pointer operator->()
		{
			return m_ptr;
		};
		bool operator==(const self_type& other) const
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const self_type& other) const
		{
			return m_ptr != other.m_ptr;
		}
		self_type& operator++()
		{
			--m_ptr;
			return *this;
		};
		self_type operator++(int)
		{
			reverse_iterator temp(*this);
			++(*this);
			return temp;
		};
		self_type& operator--()
		{
			++m_ptr;
			return *this;
		};
		self_type operator--(int)
		{
			reverse_iterator temp(*this);
			--(*this);
			return temp;
		};

	private:
		T* m_ptr;
	};

	void AddToBack(const T& value)
	{
		if (m_count + 1 == m_capacity)
		{
			Resize(m_capacity * 2);
		}
		m_data[m_count] = value;
		m_count++;
	};
	size_t GetCount() const
	{
		return m_count;
	};
	size_t GetCapacity() const
	{
		return m_capacity;
	};
	void Resize(size_t newCapacity)
	{
		if (newCapacity < m_count)
		{
			throw std::invalid_argument("New capacity less then currnet size");
		}
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < newCapacity; i++)
		{
			newData[i] = (i < m_count) ? m_data[i] : T();
		}
		delete[] m_data;
		m_data = newData;
		m_capacity = newCapacity;
	};
	void Clear()
	{
		m_capacity = 1;
		m_count = 0;
		delete[] m_data;
		m_data = new T[m_capacity];
	};
	T& operator[](size_t index)
	{
		if (index >= m_capacity)
		{
			throw std::out_of_range("Index more then capacity");
		}
		return m_data[index];
	};
	const T& operator[](size_t index) const
	{
		if (index >= m_capacity)
		{
			throw std::out_of_range("Index more then capacity");
		}
		return m_data[index];
	};

	iterator begin()
	{
		return iterator(m_data);
	};
	iterator end()
	{
		return iterator(m_data + m_count);
	};
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_data + m_count - 1);
	};
	reverse_iterator rend()
	{
		return reverse_iterator(m_data - 1);
	};

	CMyArray& operator=(const CMyArray& other)
	{
		if (std::addressof(other) == this)
		{
			return *this;
		}
		m_count = other.m_count;
		m_capacity = other.m_capacity;
		m_data = new T[m_capacity];
		for (size_t i = 0; i < m_capacity; i++)
		{
			m_data[i] = other.m_data[i];
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (std::addressof(other) == this)
		{
			return *this;
		}
		delete[] m_data;
		m_data = nullptr;
		m_capacity = 2;
		m_count = 0;
		std::swap(m_data, other.m_data);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_count, other.m_count);
		return *this;
	}

private:
	size_t m_count;
	size_t m_capacity;
	T* m_data;
};
