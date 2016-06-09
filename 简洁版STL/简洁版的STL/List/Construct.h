#pragma once
#include"Iterator.h"
#include"TypeTraits.h"

/******************************************************************************************
功能描述：STL 中的构造/析构函数

类 /函数：

简    介：由于空间配置器只是用来分配空间而没有构造对象，所以我们需要在相应的空间上行手动调用
		  构造函数来进行构造对象。当批量进行构造时，内置类型如果构造时每次都调用构造函数，肯
		  定会带来效率上的消耗这是不被允许的。在构造之前我们先得来判断这个类型有没有无用的构
		  造函数，如果有说明是内置类型直接memove，否则就得乖乖的一个一个构造了；析构时是一样
		  的道理；
*******************************************************************************************/

/*构造、释放单个对象*/
template<class T,class T2>
inline void Construct(T* point,const T2& value)
{
	new(point)T(value); //operator new
}

template<class T>
inline void Destory(T* point)
{
	point->~T();   //显示调用 T 类型的析构函数
}

/*释放 一个对象区间*/
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

