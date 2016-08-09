#pragma once
#include"Configer.h"
#include"_traits.h"

template <class Iterator>
class _ReverseIterator
{
protected:
	Iterator current;
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory
		IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType
		ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType
		DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer
		Pointer;
	typedef typename IteratorTraits<Iterator>::Reference
		Reference;

	typedef Iterator IteratorType;
	typedef _ReverseIterator<Iterator> Self;

public:
	_ReverseIterator() {}
	explicit _ReverseIterator(IteratorType x) : current(x) {}   /*构造*/
	_ReverseIterator(const Self& x) : current(x.current) {}      /*拷贝构造*/

	IteratorType base() const { return current; }
	Reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
	}

	Pointer operator->() const { return &(operator*()); }

	Self& operator++() {
		--current;
		return *this;
	}
	Self operator++(int) {
		Self tmp = *this;
		--current;
		return tmp;
	}
	Self& operator--() {
		++current;
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		++current;
		return tmp;
	}

	Self operator+(DifferenceType n) const {
		return Self(current - n);
	}
	Self& operator+=(DifferenceType n) {
		current -= n;
		return *this;
	}
	Self operator-(DifferenceType n) const {
		return Self(current + n);
	}
	Self& operator-=(DifferenceType n) {
		current += n;
		return *this;
	}
	Reference operator[](DifferenceType n) const { return *(*this + n); }

	bool operator ==(const Self& data)
	{
		return current == data.current;
	}

	bool operator !=(const Self& data)
	{
		return current != data.current;
	}
};
