#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <xmemory>
#include <xutility>
#pragma region Node
template<typename T>
struct node
{
	node() : m_Val(NULL), m_nextNode(nullptr) {}
	node(const T& _Val) : m_Val(_Val), m_nextNode(nullptr) {}

	T m_Val;
	node* m_nextNode;
};
#pragma endregion

//1
template <class _Mylist, class _Base = std::_Iterator_base0>
class _Flist_unchecked_const_iterator : public _Base {
public:
	using iterator_category = std::forward_iterator_tag;


	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::const_pointer;
	using reference = const value_type&;

	_Flist_unchecked_const_iterator() noexcept : _Ptr() {}

	_Flist_unchecked_const_iterator(_Nodeptr _Pnode, const _Mylist* _Plist) noexcept : _Ptr(_Pnode) {
		this->_Adopt(_Plist);// _Iterator_base0의 멤버함수
	}

	_NODISCARD reference operator*() const noexcept {
		return _Ptr->_Myval;
	}

	_NODISCARD pointer operator->() const noexcept {
		return std::pointer_traits<pointer>::pointer_to(**this);
	}

	_Flist_unchecked_const_iterator& operator++() noexcept {
		_Ptr = _Ptr->_Next;
		return *this;
	}

	_Flist_unchecked_const_iterator operator++(int) noexcept {
		_Flist_unchecked_const_iterator _Tmp = *this;
		_Ptr = _Ptr->_Next;
		return _Tmp;
	}

	_NODISCARD bool operator==(const _Flist_unchecked_const_iterator& _Right) const noexcept {
		return _Ptr == _Right._Ptr;
	}

#if !_HAS_CXX20
	_NODISCARD bool operator!=(const _Flist_unchecked_const_iterator& _Right) const noexcept {
		return !(*this == _Right);
	}
#endif // !_HAS_CXX20

	_NODISCARD bool operator==(std::_Default_sentinel) const noexcept {
		return _Ptr == nullptr;
	}

#if !_HAS_CXX20
	_NODISCARD bool operator!=(std::_Default_sentinel) const noexcept {
		return _Ptr != nullptr;
	}
#endif // !_HAS_CXX20
	_Nodeptr _Ptr; // pointer to node

};

//2-1
template <class _Mylist>
class _Flist_const_iterator : public _Flist_unchecked_const_iterator<_Mylist, std::_Iterator_base> {
public:
	using _Mybase = _Flist_unchecked_const_iterator<_Mylist, std::_Iterator_base>;
	using iterator_category = std::forward_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::const_pointer;
	using reference = const value_type&;

	using _Mybase::_Mybase;

	_NODISCARD reference operator*() const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
		const auto _Mycont = static_cast<const _Mylist*>(this->_Getcont());
		_STL_ASSERT(_Mycont, "cannot dereference value-initialized forward_list iterator");
		_STL_VERIFY(this->_Ptr != _Mycont->_Before_head(), "cannot dereference forward_list before_begin");
#endif // _ITERATOR_DEBUG_LEVEL == 2

		return this->_Ptr->_Myval;
	}

	_Flist_const_iterator& operator++() noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
		_STL_VERIFY(this->_Getcont(), "forward_list iterator not incrementable");
#endif // _ITERATOR_DEBUG_LEVEL == 2

		this->_Ptr = this->_Ptr->_Next;
		return *this;
	}

	_Flist_const_iterator operator++(int) noexcept {
		_Flist_const_iterator _Tmp = *this;
		this->_Ptr = this->_Ptr->_Next;
		return _Tmp;
	}

	_NODISCARD bool operator==(const _Flist_const_iterator& _Right) const noexcept {
#if _ITERATOR_DEBUG_LEVEL == 2
		_STL_VERIFY(this->_Getcont() == _Right._Getcont(), "forward_list iterators incompatible");
#endif // _ITERATOR_DEBUG_LEVEL == 2

		return this->_Ptr == _Right._Ptr;
	}

#if !_HAS_CXX20
	_NODISCARD bool operator!=(const _Flist_const_iterator& _Right) const noexcept {
		return !(*this == _Right);
	}
#endif // !_HAS_CXX20

#if _ITERATOR_DEBUG_LEVEL == 2
	friend void _Verify_range(const _Flist_const_iterator& _First, const _Flist_const_iterator& _Last) noexcept {
		_STL_VERIFY(
			_First._Getcont() == _Last._Getcont(), "forward_list iterators in range are from different containers");
	}
#endif // _ITERATOR_DEBUG_LEVEL == 2

	using _Prevent_inheriting_unwrap = _Flist_const_iterator;

	_NODISCARD _Flist_unchecked_const_iterator<_Mylist> _Unwrapped() const noexcept {
		return _Flist_unchecked_const_iterator<_Mylist>(this->_Ptr, static_cast<const _Mylist*>(this->_Getcont()));
	}

	void _Seek_to(const _Flist_unchecked_const_iterator<_Mylist> _It) noexcept {
		this->_Ptr = _It._Ptr;
	}

};

//2-2
template <class _Mylist>
class _Flist_unchecked_iterator : public _Flist_unchecked_const_iterator<_Mylist> {
public:
	using _Mybase = _Flist_unchecked_const_iterator<_Mylist>;
	using iterator_category = std::forward_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::pointer;
	using reference = value_type&;

	using _Mybase::_Mybase;

	_NODISCARD reference operator*() const noexcept {
		return const_cast<reference>(_Mybase::operator*());
	}

	_NODISCARD pointer operator->() const noexcept {
		return std::pointer_traits<pointer>::pointer_to(**this);
	}

	_Flist_unchecked_iterator& operator++() noexcept {
		_Mybase::operator++();
		return *this;
	}

	_Flist_unchecked_iterator operator++(int) noexcept {
		_Flist_unchecked_iterator _Tmp = *this;
		_Mybase::operator++();
		return _Tmp;
	}
};

//3
template <class _Mylist>
class _Flist_iterator : public _Flist_const_iterator<_Mylist> {
public:
	using _Mybase = _Flist_const_iterator<_Mylist>;
	using iterator_category = std::forward_iterator_tag;

	using _Nodeptr = typename _Mylist::_Nodeptr;
	using value_type = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer = typename _Mylist::pointer;
	using reference = value_type&;

	using _Mybase::_Mybase;

	_NODISCARD reference operator*() const noexcept {
		return const_cast<reference>(_Mybase::operator*());
	}

	_NODISCARD pointer operator->() const noexcept {
		return std::pointer_traits<pointer>::pointer_to(**this);
	}

	_Flist_iterator& operator++() noexcept {
		_Mybase::operator++();
		return *this;
	}

	_Flist_iterator operator++(int) noexcept {
		_Flist_iterator _Tmp = *this;
		_Mybase::operator++();
		return _Tmp;
	}

	using _Prevent_inheriting_unwrap = _Flist_iterator;

	_NODISCARD _Flist_unchecked_iterator<_Mylist> _Unwrapped() const noexcept {
		return _Flist_unchecked_iterator<_Mylist>(this->_Ptr, static_cast<const _Mylist*>(this->_Getcont()));
	}
};










#pragma region ForwardList
template<typename T>
class CForwardList
{
public:
	CForwardList() : m_rootNode(nullptr) {}
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

	void sort(std::function<bool(T, T)> _PredicateFunction
		= [](T _Val1, T _Val2) -> bool
		{return _Val1 >= _Val2 ? true : false; });

	void remove_if(std::function<bool(T)> _PredicateFunction);
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
inline void CForwardList<T>::sort(std::function<bool(T, T)> _PredicateFunction)
{
	auto curSize = m_curSize;
	std::vector<T> vec;
	vec.reserve(curSize);
	while (m_rootNode != nullptr)
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
	std::for_each(vec.cbegin(), vec.cend(), [&](const T& _Val) {push_front(_Val); });

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
		if (true == _PredicateFunction(curNode->m_nextNode->m_Val))
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
