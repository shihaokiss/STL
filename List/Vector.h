#pragma once

template<class T>
class Vector
{
	typedef T value_type;
	typedef value_type* iterator;
	typedef value_type& reference;
public:
	Vector() : start(0), finish(0), end_of_storage(0) {}


	Vector(const Vector<T>& x)
	{
		start = allocate_and_copy(x.end() - x.begin(), x.begin());
		finish = start + (x.end() - x.begin());
		end_of_storage = finish;
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
					start[i] = x[i];
				}
				while (i < size())
				{
					start[i] = 0;
				}
				finish = x.finish - x.start + start;
			}
		}


	}

	~Vector() 
	{
		destroy(start);
	}




	iterator begin() { return start; }
	iterator end() { return finish; }
	size_t size() const { return size_type(end() - begin()); }
	size_t capacity() const { return size_type(end_of_storage - begin()); }
	bool empty() const { return begin() == end(); }
	reference operator[](size_t n) { return *(begin() + n); }

	void reserve(size_t n)
	{
		if (capacity() < n) 
		{
			const size_t old_size = size();
			iterator tmp = allocate_and_copy(n, start);
			destroy(start);
			start = tmp;
			finish = tmp + old_size;
			end_of_storage = start + n;
		}
	}

	reference front() { return *begin(); }
	reference back() { return *(end() - 1); }

	void push_back(const T& x) 
	{
		if (finish != end_of_storage) 
		{
			*finish = x;
			++finish;
		}
		else
			insert_aux(end(), x);
	}

	void Swap(Vector<T>& x) 
	{
		swap(start, x.start);
		swap(finish, x.finish);
		swap(end_of_storage, x.end_of_storage);
	}

	iterator insert(iterator position, const T& x) 
	{
		size_t n = position - begin();
		if (finish != end_of_storage && position == end()) 
		{
			*finish = x;
			++finish;
		}
		else
			insert_aux(position, x);
		return begin() + n;
	}
	

	void pop_back() 
	{
		--finish;
	}

	iterator erase(iterator position) 
	{
		if (position + 1 != end())
			copy(position + 1, finish, position);
		--finish;
		return position;
	}


	/*void resize(size_type new_size, const T& x) 
	{
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}

	void clear() { erase(begin(), end()); }*/


private:
	iterator start;
	iterator finish;
	iterator end_of_storage;
	iterator allocate_and_copy(size_t n, iterator it)
	{
		assert(n > 0);
		iterator* begin = new T[n];
		for (int i = 0; i < n; ++i)
		{
			begin[i] = it[i];
		}
	}
	void destory(iterator)
	{
		delete[] iterator;
	}
	void copy(iterator Next, iterator Finish, iterator Position)
	{
		while (Next != Finish)
			*Position++ = *Next++;
	}
	void insert_aux(iterator it, T& x)
	{
		if (finish == end_of_storage)
		{
			size_t newcapacity = capacity() * 2 + 1;
			iterator tmp = allocate_and_copy(newcapacity, start);
			size_t n = size();
			delete[] start;
			start = tmp;
			finish = start + n;
			end_of_storage = start + newcapacity;
		}
	
		iterator cur = finish - 1;
		while (cur != (it - 1))
		{
			*cur = *(cur + 1);
			--cur;
		}
		*it = x;
		finish++;
	}
};