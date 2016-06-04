#pragma once
#include"Configer.h"
template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType* Iterator;
	typedef ValueType& Reference;

	Vector() : _start(0), _finish(0), _endOfStorage(0) {}

	Vector(const Vector<T>& x)
	{
		_start = allocate_and_copy(x.end() - x.begin(), x.begin());
		_finish = _start + (x.end() - x.begin());
		_endOfStorage = _finish;
	}

	Vector<T>& operator=(const Vector<T>& x)
	{
		if (this != &x)
		{
			if (x.size() >= capacity())
			{
				Vector<T> VECTOR = x;
				Swap(VECTOR);
			}
			else
			{
				int i = 0;
				for (;i < x.size(); ++i)
				{
					_start[i] = x[i];
				}
				while (i < size())
				{
					_start[i] = 0;
				}
				_finish = x._finish - x._start + _start;
			}
		}


	}

	~Vector() 
	{
		if (_start)
		{
			delete[] _start;
		}
	}

	Iterator begin() { return _start; }
	Iterator end() { return _finish; }
	size_t size()  { return _finish - _start; }
	size_t capacity() const { return _endOfStorage - _start; }
	bool empty()  { return begin() == end(); }
	Reference operator[](size_t n) { return *(begin() + n); }


	Reference front() { return *begin(); }
	Reference back() { return *(end() - 1); }

	void PushBack(const T& x) 
	{
		_CheckExpand();

		*_finish = x;
		++_finish;
	}

	void pop_back() 
	{
		--_finish;
	}

	Iterator erase(Iterator position) 
	{
		if (position + 1 != end())
			copy(position + 1, _finish, position);
		--_finish;
		return position;
	}

	Iterator insert(Iterator position, const T& x)
	{
		_CheckExpand();
		Iterator tmp = end(), prev = tmp - 1;
		while (tmp != position)
			*tmp-- = *prev--;
		*position = x;
		++_finish;
		return position + 1;
	}

	void _CheckExpand()
	{
		if (_finish == _endOfStorage)
		{
			size_t size = capacity();
			size_t NewCapacity = size * 2 + 3;
			T*tmp = new T[NewCapacity];
			memcpy(tmp, _start, sizeof(T)*size);

			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + NewCapacity;
		}
	}

	void Print()
	{
		Iterator tmp = _start;
		while (tmp != _finish)
			cout << *tmp++ << "  ";
		cout << endl;
	}

private:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;

	void Swap(Vector<T>& x)
	{
		swap(_start, x._start);
		swap(_finish, x._finish);
		swap(_endOfStorage, x._endOfStorage);
	}
	Iterator allocate_and_copy(size_t n, Iterator it)
	{
		assert(n > 0);
		Iterator begin = new T[n];
		for (int i = 0; i < n; ++i)
		{
			begin[i] = it[i];
		}
	}
	void copy(Iterator Next, Iterator _finish, Iterator Position)
	{
		while (Next != _finish)
			*Position++ = *Next++;
	}

};