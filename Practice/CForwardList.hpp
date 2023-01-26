#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#pragma region Node
template<typename T>
struct node
{
	node() : m_Val(NULL), m_nextNode(nullptr) {}
	node(const T& _Val): m_Val(_Val), m_nextNode(nullptr){}

	T m_Val;
	node* m_nextNode;
};
#pragma endregion

#pragma region ForwardList
template<typename T>
class CForwardList
{
public:
	CForwardList(): m_rootNode(nullptr) {}
	CForwardList(const CForwardList& _forwardList) : m_rootNode(nullptr)
	{
		//230126 begin, end 구현 후 작업 할 예정
	}
	CForwardList(const std::initializer_list<T> _initializerList) : m_rootNode(nullptr) {}

	~CForwardList()
	{
		clear();
	}

private:
	size_t m_curSize = 0;
	node<T>* m_rootNode;

public:
	void push_front(T&& _Val);
	void push_front(const T& _Val);

	T pop_front();
	const T& pop_front() const;

	const size_t size() const { return m_curSize; }

	void sort(std::function<bool (T, T)> _PredicateFunction 
		= [](T _Val1, T _Val2) -> bool 
		{return _Val1 >= _Val2 ? true : false; });

	void remove_if(std::function<bool (T)> _PredicateFunction);
	void remove(const T& _Val);
	void remove(T&& _Val);
	void clear();
};

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_Val"></param>
template<typename T>
inline void CForwardList<T>::push_front(T&& _Val)
{
	push_front(_Val);
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_Val"></param>
template<typename T>
inline void CForwardList<T>::push_front(const T& _Val)
{
	++m_curSize;
	if (m_rootNode == nullptr)
	{
		m_rootNode = new node<T>(_Val);
		return;
	}
	auto newNode = new node<T>(_Val);
	newNode->m_nextNode = m_rootNode;
	m_rootNode = newNode;
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline T CForwardList<T>::pop_front()
{
	if (m_rootNode == nullptr)
		throw "out of range";

	T data = m_rootNode->m_Val;
	m_rootNode = m_rootNode->m_nextNode;
	--m_curSize;
	return data;
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline const T& CForwardList<T>::pop_front() const
{
	return pop_front();
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
inline void CForwardList<T>::clear()
{
	while (m_rootNode->m_nextNode != nullptr)
	{
		auto deleteNode = m_rootNode;
		m_rootNode = m_rootNode->m_nextNode;
		delete deleteNode;
	}
	delete m_rootNode;
}

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_PredicateFunction"></param>
template<typename T>
inline void CForwardList<T>::sort( std::function<bool (T, T)> _PredicateFunction )
{
	auto curSize = m_curSize;
	std::vector<T> vec;
	vec.reserve(curSize);
	while(m_rootNode != nullptr)
		vec.emplace_back(pop_front());

	for (size_t i = 1; i < curSize; ++i) {
		for (size_t j = i; j < curSize; ++j) {
			if (false == _PredicateFunction(vec[i - 1], vec[j])) {
				auto temp = vec[i - 1];
				vec[i - 1] = vec[j];
				vec[j] = temp;
			}
		}
	}
	std::for_each(vec.cbegin(), vec.cend(), [&](const T& _Val) {push_front(_Val); } );

}
/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_predicateFunction"></param>
template<typename T>
inline void CForwardList<T>::remove_if(std::function<bool(T)> _PredicateFunction)
{
	auto curNode = m_rootNode;
	while (curNode->m_nextNode != nullptr)
	{
		if (true == _PredicateFunction(curNode->m_nextNode->m_Val) )
		{
			auto deleteNode = curNode->m_nextNode;
			curNode->m_nextNode = curNode->m_nextNode->m_nextNode;
			delete deleteNode;
			--m_curSize;
		}
		else
		{
			curNode = curNode->m_nextNode;
		}
	}
	if (true == _PredicateFunction(m_rootNode->m_Val))
	{
		auto deleteNode = m_rootNode;
		m_rootNode = m_rootNode->m_nextNode;
		delete deleteNode;

	}

}
/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_Val"></param>
template<typename T>
inline void CForwardList<T>::remove(const T& _Val)
{
	remove_if([&](const T& _Other) { return _Other == _Val; });
}
/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="_Val"></param>
template<typename T>
inline void CForwardList<T>::remove(T&& _Val)
{
	remove(_Val);
}
#pragma endregion
