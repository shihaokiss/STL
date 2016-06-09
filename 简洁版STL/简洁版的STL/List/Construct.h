#pragma once
#include"Iterator.h"
#include"TypeTraits.h"

/******************************************************************************************
����������STL �еĹ���/��������

�� /������

��    �飺���ڿռ�������ֻ����������ռ��û�й����������������Ҫ����Ӧ�Ŀռ������ֶ�����
		  ���캯�������й�����󡣵��������й���ʱ�����������������ʱÿ�ζ����ù��캯������
		  �������Ч���ϵ��������ǲ�������ġ��ڹ���֮ǰ�����ȵ����ж����������û�����õĹ�
		  �캯���������˵������������ֱ��memove������͵ùԹԵ�һ��һ�������ˣ�����ʱ��һ��
		  �ĵ���
*******************************************************************************************/

/*���졢�ͷŵ�������*/
template<class T,class T2>
inline void Construct(T* point,const T2& value)
{
	new(point)T(value); //operator new
}

template<class T>
inline void Destory(T* point)
{
	point->~T();   //��ʾ���� T ���͵���������
}

/*�ͷ� һ����������*/
template<class Iterator>
inline void __Destory(Iterator& first,const Iterator& end, __TrueType)
{}

template<class Iterator>
inline void __Destory(Iterator& first,const Iterator& end, __FalseType)
{
	while (first != end)
	{
		Destory(first.operator->());
		first++;
	}
}

template<class Iterator,class T>
inline void _Destory(Iterator& first,const Iterator& end, T*)
{
	__Destory(first, end, typename TypeTraits<T>::HasTrivialDestructor());
}

template<class Iterator>
inline void Destory(Iterator& first,const Iterator& end)
{
	_Destory(first, end, IteratorReferentType(first));
}

