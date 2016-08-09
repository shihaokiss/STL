#pragma once
#include"Configer.h"

struct InputIterator_tag {};
struct OutputIterator_tag {};
struct ForwardIterator_tag : public InputIterator_tag {};
struct BidirectionalIterator_tag : public ForwardIterator_tag {};
struct RandomAccessIterator_tag : public BidirectionalIterator_tag {};

//类型萃取机
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

//指针特化版
template <class T> 
struct IteratorTraits<T*>
{
	typedef RandomAccessIterator_tag IteratorCategory;
	typedef T                          ValueType;
	typedef ptrdiff_t                  DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};


template<class InputIterator>
int Distance(InputIterator first, InputIterator last)
{
	return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}


template<class InputIterator>
int _Distance(InputIterator first, InputIterator last, ForwardIterator_tag)
{
	int count = 0;
	while (first != last)
	{
		count++;
		first++;
	}
	return count;
}


template<class InputIterator>
int _Distance(InputIterator first, InputIterator last, RandomAccessIterator_tag)
{
	return last - first;
}
