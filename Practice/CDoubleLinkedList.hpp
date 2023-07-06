#pragma once
#include <functional>

template<typename T>
class CDoubleLinkedList
{
	struct node
	{
		node()
			: m_Val(NULL)
			, m_prevNode(nullptr)
			, m_nextNode(nullptr) {}
		node(const T& _Val, node* _prevNode, node* _nextNode)
			: m_Val(_Val)
			, m_prevNode(_prevNode)
			, m_nextNode(_nextNode) {}
		~node() {}
		T m_Val;
		node* m_nextNode;
		node* m_prevNode;
	};

public:
	CDoubleLinkedList();
	~CDoubleLinkedList();

private:
	node* m_rootNode;
	node* m_endNode;
	size_t m_curSize;

public:
	void push_front(T&& _Val) { push_front(_Val); }
	void push_front(const T& _Val);
	void push_back(T&& _Val) { push_back(_Val); }
	void push_back(const T& _Val);

	T pop_front();
	const T& pop_front() const { return pop_front(); };
	T pop_back();
	const T& pop_back() const { return pop_back(); };

	const size_t size() const { return m_curSize; }

	void sort(std::function<bool(T, T)> _PredicateFunction
		= [](T _Val1, T _Val2) -> bool
		{return (_Val1 >= _Val2) ? true : false; });

	void remove_if(std::function<bool(T)> _PredicateFunction);
	void remove(const T& _Val);
	void remove(T&& _Val);
	void clear() noexcept;

};

template<typename T>
inline CDoubleLinkedList<T>::CDoubleLinkedList()
	:m_rootNode(nullptr)
	, m_endNode(nullptr)
	, m_curSize(0)
{

}

template<typename T>
inline CDoubleLinkedList<T>::~CDoubleLinkedList()
{
	clear();
}

template<typename T>
inline void CDoubleLinkedList<T>::push_front(const T& _Val)
{
	++m_curSize;
	if (nullptr == m_rootNode)
	{
		m_rootNode = new node();
		m_endNode = new node();
		m_rootNode->m_nextNode = m_endNode;
		m_rootNode->m_Val = _Val;
		m_endNode->m_prevNode = m_rootNode;
		return;
	}
	auto curNode = new node(_Val, nullptr, m_rootNode);
	m_rootNode->m_prevNode = curNode;
	m_rootNode = curNode;
}

template<typename T>
inline void CDoubleLinkedList<T>::push_back(const T& _Val)
{
	++m_curSize;
	if (nullptr == m_rootNode)
	{
		m_rootNode = new node();
		m_endNode = new node();
		m_rootNode->m_Val = _Val;
		m_rootNode->m_nextNode = m_endNode;
		m_endNode->m_prevNode = m_rootNode;
		return;
	}
	auto curNode = new node(NULL, m_endNode, nullptr);
	m_endNode->m_nextNode = curNode;
	m_endNode->m_Val = _Val;
	m_endNode = curNode;
}

template<typename T>
inline T CDoubleLinkedList<T>::pop_front()
{
	if (nullptr == m_rootNode)
		return NULL;
	auto m_curNode = m_rootNode;
	m_rootNode = m_rootNode->m_nextNode;
	T Val = m_curNode->m_Val;
	delete m_curNode;
	return Val;
}

template<typename T>
inline T CDoubleLinkedList<T>::pop_back()
{
	if (nullptr == m_endNode)
		return NULL;

	auto curNode = m_endNode->m_prevNode;
	T Val = curNode->m_Val;
	curNode->m_prevNode->m_nextNode = m_endNode;
	m_endNode->m_prevNode = curNode->m_prevNode;
	delete curNode;
	return Val;
}

template<typename T>
inline void CDoubleLinkedList<T>::sort(std::function<bool(T, T)> _PredicateFunction)
{

}

template<typename T>
inline void CDoubleLinkedList<T>::remove_if(std::function<bool(T)> _PredicateFunction)
{
}

template<typename T>
inline void CDoubleLinkedList<T>::remove(const T& _Val)
{
}

template<typename T>
inline void CDoubleLinkedList<T>::remove(T&& _Val)
{
}

template<typename T>
inline void CDoubleLinkedList<T>::clear() noexcept
{
	if (nullptr == m_rootNode)
		return;

	while (nullptr != m_rootNode->m_nextNode)
	{
		auto curNode = m_rootNode;
		m_rootNode = m_rootNode->m_nextNode;
		delete curNode;
	}

}
