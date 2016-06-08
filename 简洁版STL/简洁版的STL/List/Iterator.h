#pragma once

/*
�������ļ�飺
STL ������˼���ǽ��������㷨���뿪���˴˶�������ƣ��������ճ�ϼ������ǽ��������
���������ǰ��ݵ������ɫ����������һ�ֳ������Ƹ��ʵ�ֳ��������в�û��ֱ�Ӷ�Ӧ��
��������ʵ�
iterator���ģʽ�µĶ��壺�ṩһ�ַ������ܹ����η��������е�Ԫ�أ������豩¶��������
�ڲ���﷽ʽ
*/

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

/*****************************************************************************
���������� traits ������ȡ��

�� /������ template<class Iterator> struct IteratorTraits{};

��    �飺 ͨ����Ƕ���ͻ�ȡ��Ӧ�����������ͣ��Ӷ��ﵽ������ȡ��Ŀ��
*****************************************************************************/


/*�������� 5 ������*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//������ֵļ̳���������ʱ����Ҫ���ϼ��ݵ�ԭ��



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



/*****************************************************************************
���������� ���������(�������������һ���װ)

�� /������ template<class Iterator> struct IteratorTraits{};

��    �飺 ͨ����Ƕ���ͻ�ȡ��Ӧ�����������ͣ��Ӷ��ﵽ������ȡ��Ŀ��
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

	/*���캯��,�������캯��*/
	Self(){}
	explicit Self(Iterator Iterator) :_current(Iterator){}

	/*���ظ��ַ���*/
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
















