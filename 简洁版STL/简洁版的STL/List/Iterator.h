#pragma once
#include"List.h"
#include"Vector.h"

/*****************************************************************************

文件名: Iterator.h  

创建时间: 2016 - 5 - 30 

作者: 石豪

所在单位: 陕西科技大学

实现功能: 对迭代器功能的简单实现 与 类型萃取的机器
备注: STL源码剖析

修改记录：
日期       版本        修改人             修改内容
                         
*****************************************************************************/


namespace IteratorStudy
{
	/*
	迭代器的简介：
	STL 的中心思想是将容器与算法分离开，彼此独立的设计，最后在用粘合剂将它们结合起来。
	迭代器就是扮演的这个角色，迭代器是一种抽象的设计概念，实现程序语言中并没有直接对应于
	这个概念的实物。
	iterator设计模式下的定义：提供一种方法，能够依次访问容器中的元素，又无需暴露该容器的
	内部表达方式
	*/

	/*STL 中的 find 方法的实现*/
	template<class InputIterator, class T>
	InputIterator Find(InputIterator first, InputIterator last, const T& value)
	{
		while (first != last && *first != value)
			++first;
		return first;
	}

	/*迭代器作为粘合剂的例子*/
	void IteratorTest()
	{
		const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		vector<int> Vector(arr, arr + 10);  //vector 的初始化
		list<int> List(arr, arr + 10);      //list 的初始化
		deque<int> Deque(arr, arr + 10);    //deque 的初始化

		vector<int>::iterator it1 = Find(Vector.begin(), Vector.end(), 8);
		cout << *it1 << endl;

		list<int>::iterator it2 = Find(List.begin(), List.end(), 7);
		cout << *it2 << endl;

		deque<int>::iterator it3 = Find(Deque.begin(), Deque.end(), 10);
		if (it3 == Deque.end())
			cout << "Node Found : Data!" << endl;
	}


	/*****************************************************************************
	功能描述：利用模板函数的参数推导机制

	相关函数：  void FunImpl(I iter, T t);
	void Func(I iter);
	void FunTest();

	简介： 以 Func() 函数作为对外接口，由类型I，推导出类型 T
	缺点是，当 T 为返回值得类型时就无法推导得出了
	*****************************************************************************/

	template<class I, class T>
	void FunImpl(I iter, T t)
	{
		typename T test;
	}

	template<class I>
	void Func(I iter)
	{
		FunImpl(iter, *iter);
	}

	void FunTest()
	{
		int a = 10;
		Func(&a);
	}




	/*****************************************************************************

	功能描述： 使用内嵌类型的推导机制

	类 /函数： template<class T>  struct MyIter；
	template<class T>  typename T::value_type Fun(T it)；
	void TestTun()；
	template<class T>  struct IteratorTraits；
	template<class T>  struct IteratorTraits<T*>
	template<class T>  struct IteratorTraits<const T*>

	简    介： MyIter类中的成员对象是指向 T 类型的指针，通过在MyIter的内嵌类型
	可以萃取到 T 类型作为 Fun() 函数的返回值；
	当 MyIter 是原生指针无法内嵌时，我们可以通过偏特化来达到目标


	*****************************************************************************/

	template<class T>
	struct MyIter
	{
		typedef T value_type;					//内嵌类别声明
		MyIter(T* ptr) :_ptr(ptr){}				//构造函数
		T& operator* ()const { return *_ptr; }  //重载 *
		T* _ptr;
	};

	template<class T>
	typename T::value_type Fun(T it)
	{
		return *it;
	}

	void TestTun()
	{
		MyIter<int> ite(new int(10));    //构造一个MyIter对象
		Fun(ite);
	}

	template<class T>           //传进来的迭代器类型是 class  如：MyIter<int>  //value_type 是 int
	struct IteratorTraits
	{
		typedef typename T::value_type value_type;
	};

	template<class T>          //传进来的迭代器类型是原生指针  如：int*  //value_type 是 int
	struct IteratorTraits<T*>
	{
		typedef T value_type;
	};

	template<class T>		  //传进来的迭代器类型是 const 原生指针  如：const int*  //value_type 是 int
	struct IteratorTraits<const T*>
	{
		typedef T value_type;
	};

	//注：因为我们要通过这种机制来萃取出一个类型，来声明变量，所以不能萃取出 const T


}



namespace Traits
{
	/*****************************************************************************
	功能描述： traits 类型萃取机

	类 /函数：

	简    介：
	*****************************************************************************/

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


	void DistanceTest()
	{
		List<int> LIST;
		Vector<int> VECTOR;
		for (int i = 0; i < 10; ++i)
		{
			LIST.push_back(i);
			VECTOR.PushBack(i);
		}
		
		cout << Distance(LIST.begin(), LIST.end()) << endl;
		cout << Distance(VECTOR.begin(), VECTOR.end()) << endl;
	}

	void AdvanceTest()
	{
		List<int> LIST;
		Vector<int> VECTOR;
		for (int i = 0; i < 10; ++i)
		{
			LIST.push_back(i);
			VECTOR.PushBack(i);
		}

		List<int>::iterator LIST_IT = LIST.begin();
		Vector<int>::Iterator VECTOR_IT = VECTOR.begin();
		Advance(LIST_IT, 5);
		Advance(VECTOR_IT, 8);

		cout << *LIST_IT << endl;
		cout << *VECTOR_IT << endl;
	}

}










