#pragma once

/*
迭代器的简介：
STL 的中心思想是将容器与算法分离开，彼此独立的设计，最后在用粘合剂将它们结合起来。
迭代器就是扮演的这个角色，迭代器是一种抽象的设计概念，实现程序语言中并没有直接对应于
这个概念的实物。
iterator设计模式下的定义：提供一种方法，能够依次访问容器中的元素，又无需暴露该容器的
内部表达方式
*/

/*
与 STL 融合的五个必要的型别
1.value type  //迭代器所指对象的类型
2.difference type  //两个迭代器之间的距离
3.reference type  //迭代器的引用
4.pointer type  //迭代器的指针
5.iterator_category  //迭代器的类别
(1)Input Iterator  //只读迭代器
(2)Output Iterator  //只写迭代器
(3)Forward Iterator  //向前迭代器
(4)Bidirectional Iterator  //双向迭代器
(5)RandomAccess Iterator  //随机访问迭代器
*/

/*****************************************************************************
功能描述： traits 类型萃取机

类 /函数： template<class Iterator> struct IteratorTraits{};

简    介： 通过内嵌类型获取相应迭代器的类型，从而达到类型萃取的目的
*****************************************************************************/


/*迭代器的 5 个类型*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//这里出现的继承是由于有时候需要向上兼容的原因



template<class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::DifferenceType DifferenceType;
	typedef typename Iterator::ValueType ValueType;
	typedef typename Iterator::Reference Reference;
	typedef typename Iterator::Pointer Pointer;
};

/* T* 偏特化版本 */
template<class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef ptrdiff_t DifferenceType;
	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
};

/* const T* 偏特化版本 */
template<class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef ptrdiff_t DifferenceType;
	typedef T ValueType;
	typedef const T& Reference;
	typedef const T* Pointer;
};


//Distance 函数组的实现（两个迭代器之间的距离）
template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType  //利用萃取机得到的返回值
	__Distance(InputIterator first, InputIterator last, InputIteratorTag)
{
		IteratorTraits<InputIterator>::DifferenceType n = 0;
		while (first != last)
		{
			++n, ++first;
		}
		return n;
}

template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType  //利用萃取机得到的返回值
	__Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag)
{
		return last - first;
}


template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType  //利用萃取机得到的返回值
	Distance(InputIterator first, InputIterator last)
{
	return __Distance(first, last, typename IteratorTraits<InputIterator>::IteratorCategory());
}


//Advance 函数组的实现 （将迭代器累加 n 次）
template<class InputIterator,class Distance>   //迭代器类型为InputIteratorTag
inline void __Advance(InputIterator& it, Distance n, InputIteratorTag)
{
	while (n--)
		++it;
}

template<class InputIterator, class Distance>  //迭代器类型为BidirectionalIteratorTag
inline void __Advance(InputIterator& it, Distance n, RandomAccessIteratorTag)
{
	it += n;
}

template<class InputIterator,class Distance>
inline void Advance(InputIterator& it, Distance n)
{
	InputIterator a;
	__Advance(it, n, typename IteratorTraits<InputIterator>::IteratorCategory());
}



/*****************************************************************************
功能描述： 反向迭代器(对正向迭代器的一层封装)

类 /函数： template<class Iterator> struct IteratorTraits{};

简    介： 通过内嵌类型获取相应迭代器的类型，从而达到类型萃取的目的
*****************************************************************************/

template<class Iterator>
class ReverseIterator
{
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
	typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
	typedef typename IteratorTraits<Iterator>::ValueType ValueType;
	typedef typename IteratorTraits<Iterator>::Reference Reference;
	typedef typename IteratorTraits<Iterator>::Pointer Pointer;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;

	/*构造函数,拷贝构造函数*/
	Self(){}
	explicit Self(Iterator Iterator) :_current(Iterator){}

	/*重载各种符号*/
	Reference operator*()
	{
		IteratorType tmp = _current;
		return *--tmp;
	}

	Pointer operator->()
	{
		return &(*_current);
	}

	Self& operator++()
	{
		--_current;
		return *this;
	}
	Self operator++(int)
	{
		Self tmp = *this;
		--_current;
		return tmp;
	}
	Self operator--()
	{
		++_current;
		return *this;
	}
	Self operator--(int)
	{
		Self tmp = *this;
		++_current;
		return tmp;
	}

	bool operator == (const Self& it)
	{
		return _current == it._current;
	}
	bool operator != (const Self& it)
	{
		return _current != it._current;
	}
protected:
	Iterator _current;
};



namespace TraitsTest
{

}
















