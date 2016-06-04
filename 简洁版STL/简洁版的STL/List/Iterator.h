#pragma once
#include"List.h"
#include"Vector.h"

/*****************************************************************************

�ļ���: Iterator.h  

����ʱ��: 2016 - 5 - 30 

����: ʯ��

���ڵ�λ: �����Ƽ���ѧ

ʵ�ֹ���: �Ե��������ܵļ�ʵ�� �� ������ȡ�Ļ���
��ע: STLԴ������

�޸ļ�¼��
����       �汾        �޸���             �޸�����
                         
*****************************************************************************/


namespace IteratorStudy
{
	/*
	�������ļ�飺
	STL ������˼���ǽ��������㷨���뿪���˴˶�������ƣ��������ճ�ϼ������ǽ��������
	���������ǰ��ݵ������ɫ����������һ�ֳ������Ƹ��ʵ�ֳ��������в�û��ֱ�Ӷ�Ӧ��
	��������ʵ�
	iterator���ģʽ�µĶ��壺�ṩһ�ַ������ܹ����η��������е�Ԫ�أ������豩¶��������
	�ڲ���﷽ʽ
	*/

	/*STL �е� find ������ʵ��*/
	template<class InputIterator, class T>
	InputIterator Find(InputIterator first, InputIterator last, const T& value)
	{
		while (first != last && *first != value)
			++first;
		return first;
	}

	/*��������Ϊճ�ϼ�������*/
	void IteratorTest()
	{
		const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		vector<int> Vector(arr, arr + 10);  //vector �ĳ�ʼ��
		list<int> List(arr, arr + 10);      //list �ĳ�ʼ��
		deque<int> Deque(arr, arr + 10);    //deque �ĳ�ʼ��

		vector<int>::iterator it1 = Find(Vector.begin(), Vector.end(), 8);
		cout << *it1 << endl;

		list<int>::iterator it2 = Find(List.begin(), List.end(), 7);
		cout << *it2 << endl;

		deque<int>::iterator it3 = Find(Deque.begin(), Deque.end(), 10);
		if (it3 == Deque.end())
			cout << "Node Found : Data!" << endl;
	}


	/*****************************************************************************
	��������������ģ�庯���Ĳ����Ƶ�����

	��غ�����  void FunImpl(I iter, T t);
	void Func(I iter);
	void FunTest();

	��飺 �� Func() ������Ϊ����ӿڣ�������I���Ƶ������� T
	ȱ���ǣ��� T Ϊ����ֵ������ʱ���޷��Ƶ��ó���
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

	���������� ʹ����Ƕ���͵��Ƶ�����

	�� /������ template<class T>  struct MyIter��
	template<class T>  typename T::value_type Fun(T it)��
	void TestTun()��
	template<class T>  struct IteratorTraits��
	template<class T>  struct IteratorTraits<T*>
	template<class T>  struct IteratorTraits<const T*>

	��    �飺 MyIter���еĳ�Ա������ָ�� T ���͵�ָ�룬ͨ����MyIter����Ƕ����
	������ȡ�� T ������Ϊ Fun() �����ķ���ֵ��
	�� MyIter ��ԭ��ָ���޷���Ƕʱ�����ǿ���ͨ��ƫ�ػ����ﵽĿ��


	*****************************************************************************/

	template<class T>
	struct MyIter
	{
		typedef T value_type;					//��Ƕ�������
		MyIter(T* ptr) :_ptr(ptr){}				//���캯��
		T& operator* ()const { return *_ptr; }  //���� *
		T* _ptr;
	};

	template<class T>
	typename T::value_type Fun(T it)
	{
		return *it;
	}

	void TestTun()
	{
		MyIter<int> ite(new int(10));    //����һ��MyIter����
		Fun(ite);
	}

	template<class T>           //�������ĵ����������� class  �磺MyIter<int>  //value_type �� int
	struct IteratorTraits
	{
		typedef typename T::value_type value_type;
	};

	template<class T>          //�������ĵ�����������ԭ��ָ��  �磺int*  //value_type �� int
	struct IteratorTraits<T*>
	{
		typedef T value_type;
	};

	template<class T>		  //�������ĵ����������� const ԭ��ָ��  �磺const int*  //value_type �� int
	struct IteratorTraits<const T*>
	{
		typedef T value_type;
	};

	//ע����Ϊ����Ҫͨ�����ֻ�������ȡ��һ�����ͣ����������������Բ�����ȡ�� const T


}



namespace Traits
{
	/*****************************************************************************
	���������� traits ������ȡ��

	�� /������

	��    �飺
	*****************************************************************************/

	/*
	�� STL �ںϵ������Ҫ���ͱ�
	1.value type  //��������ָ���������
	2.difference type  //����������֮��ľ���
	3.reference type  //������������
	4.pointer type  //��������ָ��
	5.iterator_category  //�����������
	(1)Input Iterator  //ֻ��������
	(2)Output Iterator  //ֻд������
	(3)Forward Iterator  //��ǰ������
	(4)Bidirectional Iterator  //˫�������
	(5)RandomAccess Iterator  //������ʵ�����
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

	/* T* ƫ�ػ��汾 */
	template<class T>
	struct IteratorTraits<T*>
	{
		typedef RandomAccessIteratorTag IteratorCategory;
		typedef ptrdiff_t DifferenceType;
		typedef T ValueType;
		typedef T& Reference;
		typedef T* Pointer;
	};

	/* const T* ƫ�ػ��汾 */
	template<class T>
	struct IteratorTraits<const T*>
	{
		typedef RandomAccessIteratorTag IteratorCategory;
		typedef ptrdiff_t DifferenceType;
		typedef T ValueType;
		typedef const T& Reference;
		typedef const T* Pointer;
	};


	//Distance �������ʵ�֣�����������֮��ľ��룩
	template<class InputIterator>
	inline typename IteratorTraits<InputIterator>::DifferenceType  //������ȡ���õ��ķ���ֵ
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
	inline typename IteratorTraits<InputIterator>::DifferenceType  //������ȡ���õ��ķ���ֵ
		__Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag)
	{
			return last - first;
		}


	template<class InputIterator>
	inline typename IteratorTraits<InputIterator>::DifferenceType  //������ȡ���õ��ķ���ֵ
		Distance(InputIterator first, InputIterator last)
	{
		return __Distance(first, last, typename IteratorTraits<InputIterator>::IteratorCategory());
	}


	//Advance �������ʵ�� �����������ۼ� n �Σ�
	template<class InputIterator,class Distance>   //����������ΪInputIteratorTag
	inline void __Advance(InputIterator& it, Distance n, InputIteratorTag)
	{
		while (n--)
			++it;
	}

	template<class InputIterator, class Distance>  //����������ΪBidirectionalIteratorTag
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










