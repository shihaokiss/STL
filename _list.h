#pragma once
#include"_ReverseIterator.h"
#include"_traits.h"

template<class T>
class _List_Node     //双向链表的节点
{
public:
	_List_Node()
		:_prev(NULL), _next(NULL)
	{}
	_List_Node(T value)
		:_data(value), _prev(NULL), _next(NULL)
	{}
	_List_Node<T>* _prev;
	_List_Node<T>* _next;
	T _data;
};


template<class T, class Ref, class Ptr>
struct _List_Iterator   /*双向链表的迭代器*/
{
	/*五种型别，方便萃取*/
	typedef BidirectionalIterator_tag IteratorCategory;
	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
	typedef int DifferenceType;

	typedef _List_Node<T> *LinkType;
	LinkType _node;
	typedef _List_Iterator<T, T&, T*> Iterator;
	typedef _List_Iterator<T, Ref, Ptr> Self;


	_List_Iterator()
	{

	}
	_List_Iterator(LinkType x)
		:_node(x)
	{

	}
	Reference operator*()
	{
		return _node->_data;
	}

	Pointer operator->()
	{
		return &(_node->_data);
	}
	Iterator operator++()
	{
		_node = _node->_next;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator tmp;
		tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	Iterator operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}
	bool operator!=(const Self& x)
	{
		return _node != x._node;
	}
	bool operator==(const Self& x)
	{
		return _node == x._node;
	}

};



template<class T/*, class Alloc = Alloc*/>
class List
{
public:
	typedef _List_Node<T>* LinkType;
	typedef _List_Iterator<T, T&, T*> Iterator;    /*正向迭代器*/
	typedef _ReverseIterator<Iterator> ReverseIterator;  /*反向迭代器*/
	//typedef SimpleAlloc<_List_Node, Alloc> ListNodeAllocator;
	List()
	{
		_node = new _List_Node<T>();
		_node->_next = _node;
		_node->_prev = _node;
	}

	//~List()
	//{
	//	Destory(Begin(), End());
	//	Iterator it = Begin();
	//	while (it != End())
	//	{
	//		//ListNodeAllocator::Deallocate(it._node);      //调用析构
	//	}
	//}


	Iterator Begin()
	{
		return _node->_next;
	}

	Iterator End()
	{
		return _node;
	}

	Iterator Insert(Iterator pos, const T& x)
	{
		LinkType prev = pos._node->_prev;

		/*LinkType tmp = ListNodeAllocator::Allocate();
		Construct(tmp, x);*/

		LinkType tmp = new _List_Node<T>(x);

		prev->_next = tmp;
		pos._node->_prev = tmp;
		tmp->_next = pos._node;
		tmp->_prev = prev;

		return tmp;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	ReverseIterator ReBegin()   //反向迭代器
	{
		return ReverseIterator(_node);
	}

	ReverseIterator ReEnd()     //反向迭代器
	{
		return ReverseIterator(_node->_next);
	}
protected:
	LinkType _node;
};


namespace LIST
{
	void Test()
	{
		List<int> My_List;
		for (int i = 0; i < 10; ++i)
		{
			My_List.PushFront(i);
		}

		/*List<int>::Iterator begin = My_List.Begin(),end = My_List.End();
		cout << Distance(begin, end) << endl;*/
		List<int>::ReverseIterator begin = My_List.ReBegin(), end = My_List.ReEnd();
		while (begin != end)
		{
			cout << *begin << endl;
			begin++;
		}

		begin = My_List.ReBegin(), end = My_List.ReEnd();
		cout << Distance(begin, end) << endl;
	}
}