#pragma once
#include"Configer.h"

template<class T>
struct ListNode
{
	typedef ListNode<T> Node;
	ListNode()
		:_value(0),_next(NULL), _prev(NULL)
	{}
	ListNode(const T& value) 
		:_next(NULL), _prev(NULL), _value(value)
	{}
	Node* _next;
	Node* _prev;
	T _value;
};

template<class T>
struct ListIterator
{
	typedef T ValueType;	 //指向对象的类型
	typedef T* Pointer;      //指针
	typedef T& Reference;    //引用
	typedef ptrdiff_t DifferenceType;      //两个迭代器之间的距离
	typedef BidirectionalIteratorTag IteratorCategory;      //迭代器类型

	typedef ListNode<T>* LinkType;
	typedef ListIterator<T> Self;
	/*成员对象*/
	LinkType _node;

	/*两个构造函数*/
	ListIterator(){};
	ListIterator(LinkType node_pointer) :_node(node_pointer){};
	/*拷贝构造函数*/
	ListIterator(const Self& node) :_node(node._node){};
	/*赋值运算符的重载*/
	Self& operator = (const Self& node)
	{ 
		if (this != &node)
			_node = node._node; 
		return *this;
	};

	/*重载各种方法*/
	bool operator == (Self& It)
	{
		return _node == It._node;
	}
	bool operator!=(Self& It)
	{
		return _node != It._node;
	}
	LinkType operator -> (){ return _node; }
	T& operator* (){ return _node->_value; };
	Self& operator ++ (){ _node = _node->_next; return *this; };
	Self operator ++ (int){ Self tmp = *this; ++*this; return tmp; }
	Self& operator -- (){ _node = _node->_prev; return *this; };
	Self& operator -- (int){ Self tmp = *this; --*this; return tmp; }

};


template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef Node* LinkType;
	typedef ListIterator<T> iterator;
	typedef T ValueType;

	List() //头结点
		:_head(new Node())
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	iterator begin() { return _head->_next; }
	iterator end() { return _head; }
	bool empty() const { return _head->_next == _head; }

	T& front() { return *begin(); }
	T& back() { return *(--end()); }

	void Swap(List<T>& x) { swap(_head, x._head); }

	iterator insert(iterator position, const T& x) 
	{
		LinkType tmp = new Node(x);
		tmp->_next = position._node;
		tmp->_prev = position->_prev;
		position->_prev->_next = tmp;
		position->_prev = tmp;
		return tmp;
	}
	void insert(iterator position, int n, const T& x)
	{
		assert(n > 0);
		for (int i = n; n > 0; --n)
			insert(position, x);
	}

	void push_front(const T& x) { insert(begin(), x); }
	void push_back(const T& x) { insert(end(), x); }

	iterator erase(iterator position) 
	{
		LinkType prev = position->_prev;
		LinkType next = position->_next;
		prev->_next = next;
		next->_prev = prev;
		delete position._node;
		return next;
	}

	void resize(size_t new_size, const T& x)
	{
		iterator it = begin();
		int i = 0;
		for (; it != end() && i < new_size; ++i, ++it)
			;
		if (i == new_size)
		while (it != end())
			it = erase(it);
			
		else
		insert(end(), new_size - i, x);
	}
	void resize(size_t new_size) { resize(new_size, T()); }

	void clear()
	{
		LinkType tmp = _head->_next;
		while (tmp != _head)
		{
			LinkType cur = tmp;
			tmp = tmp->_next;
			delete cur;
		}
		_head->_prev = _head;
		_head->_next = _head;
	}

	void pop_front() { erase(begin()); }
	void pop_back() {
		iterator tmp = end();
		erase(--tmp);
	}

	void remove(const T& value)
	{
		iterator First = begin(), End = end();
		while (First != End)
		{
			if (First->_value == value)
				First = erase(First);
			else
				First++;
		}
	}

	void unique()
	{
		iterator first = begin(),next = first;
		while (++next != end())
		{
			if (first->_value == next->_value)
				erase(next);
			else
				first = next;
			next = first;
		}
	}
	void merge(List& x)   //合并两个排好序的链表
	{
		iterator first1 = begin(), first2 = x.begin(), end1 = end(), end2 = x.end(),next;
		while (first1 != end1 && first2 != end2)
		if (first1->_value < first2->_value)
			++first1;
		else
		{
			next = first2;
			Transfer(first1, first2, ++next);
			first2 = next;
		}
		if (first2 != end2)
			Transfer(end1, first2, end2);
	}

	void Transfer(iterator one, iterator two, iterator three)
	{
		three->_prev->_next = one._node;
		two->_prev->_next = three._node;
		one->_prev->_next = two._node;

		LinkType tmp = one->_prev;
		one->_prev = three->_prev;
		three->_prev = two->_prev;
		two->_prev = tmp;

	}

	void Swap(iterator& it)
	{
		swap(it->_prev, it->_next);
	}
	void reverse()
	{
		iterator it_begin = begin(), it_end = end(), prev;
		while (it_begin != it_end)
		{
			prev = it_begin++;
			Swap(prev);
		}
		Swap(it_end);
	}

protected:
	LinkType _head;
};

