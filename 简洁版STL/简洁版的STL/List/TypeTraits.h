#pragma once
#include"Configer.h"

/*****************************************************************************
功能描述： 类型的萃取

类 /函数：template<class __TYPE> class TypeTraits{}

简    介：通过函数的特化，来实现类型的萃取
*****************************************************************************/

struct __TrueType
{};
struct __FalseType
{};


template<class __TYPE>
class TypeTraits
{
	typedef __FalseType HasTrivialDefaultConstructor;
	typedef __FalseType HasTrivialCopyConstructor;
	typedef __FalseType HasTrivialAssignmentOperator;
	typedef __FalseType HasTrivialDestructor;

	typedef __FalseType IsPODType;
};

template<>
class TypeTraits<bool>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<char>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<unsigned char>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<short>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<unsigned short>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<int>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<unsigned int>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<float>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<unsigned long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<long long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<unsigned long long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
class TypeTraits<long double>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<class TYPE>
class TypeTraits<TYPE*>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};



