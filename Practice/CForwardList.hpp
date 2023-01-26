#pragma once

#pragma region Node
template<typename T>
struct node
{
	node() : m_data(NULL), m_nextNode(nullptr) {}
	node(const T& _data): m_data(_data), m_nextNode(nullptr){}

	T m_data;
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
		while (m_rootNode->m_nextNode != nullptr)
		{
			auto deleteNode = m_rootNode;
			m_rootNode = m_rootNode->m_nextNode;
			delete deleteNode;
		}
		delete m_rootNode;
	}

private:
	node<T>* m_rootNode;

public:
	void push_front(T&& _data);
	void push_front(const T& _data);

};
#pragma endregion

template<typename T>
inline void CForwardList<T>::push_front(T&& _data)
{
	push_front(_data);
}

template<typename T>
inline void CForwardList<T>::push_front(const T& _data)
{
	if (m_rootNode == nullptr)
	{
		m_rootNode = new node<T>(_data);
		return;
	}
	auto newNode = new node<T>(_data);
	newNode->m_nextNode = m_rootNode;
	m_rootNode = newNode;

}
