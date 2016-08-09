#pragma once
#include"_traits.h"
#include"_ReverseIterator.h"

template<class T>
class Vector
{
public:
	/* 定义 Vector 的5中型别方便萃取*/
	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
	typedef int DifferenceType;
    typedef RandomAccessIterator_tag IteratorCategory;


	typedef ValueType* Iterator;    /*正向迭代器*/
	typedef _ReverseIterator<Iterator> ReverseIterator;  /*反向迭代器*/
	//typedef SimpleAlloc<T, Alloc> DataAlloc;

	Vector()
		:_begin(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	void PushBack(const ValueType& x)
	{
		_checkMemory();

		*_finish = x;
		_finish++;
	}

	void PopBack()
	{
		if (!Empty())
		{
			_finish--;
		}
		else
		{
			cout << "Empty can't pop" << endl;
		}
	}

	void Insert(Iterator pos, const ValueType& x)
	{
		_checkMemory();
		Iterator tmp = _finish++;
		while (--tmp != pos - 1)
		{
			*(tmp + 1) = *tmp;
		}
	}

	void Erase(Iterator pos)
	{
		Iterator* tmp = pos;
		while (tmp + 1 != _finish)
			*(tmp) = *(tmp + 1);
	}

	bool Empty()
	{
		return _begin == _finish ? true : false;
	}

	Iterator Begin()
	{
		return _begin;
	}

	Iterator End()
	{
		return _finish;
	}

	size_t Size()
	{
		return _finish - _begin;
	}

	ValueType& operator[](size_t index)
	{
		assert(index >= 0 && index < Size());
		return _begin[index];
	}

	ReverseIterator Rbegin()
	{
		return ReverseIterator(_finish);
	}

	ReverseIterator Rend()
	{
		return ReverseIterator(_begin);
	}

protected:
	Iterator _begin;
	Iterator _finish;
	Iterator _endOfStorage;

	/*内存的检测*/
	void _checkMemory()
	{
		if (_finish == _endOfStorage)
		{
			int _oldSize = _finish - _begin;
			int _newSize = _oldSize * 2 + 3;
			T* tmp = new T[_newSize];
			for (int i = 0; i < _oldSize; ++i)
			{
				tmp[i] = _begin[i];
			}
			delete[] _begin;
			_begin = tmp;
			_finish = _begin + _oldSize;
			_endOfStorage = _begin + _newSize;
		}
	}     
};


namespace VECTOR
{
	void test()
	{
		Vector<int> My_Vector;
		for (int i = 0; i < 10; ++i)
			My_Vector.PushBack(i);

		Vector<int>::Iterator begin = My_Vector.Begin(),end = My_Vector.End();
		cout << Distance(begin, end) << endl;

		Vector<int>::ReverseIterator Begin = My_Vector.Rbegin(), End = My_Vector.Rend();
		while (Begin != End)
		{
			cout << *Begin << " ";
			Begin++;
		}
		cout << endl;
	}
}
