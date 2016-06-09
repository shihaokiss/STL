#pragma once
#include"Configer.h"

/*****************************************************************************
���������� ���͵���ȡ

�� /������template<struct __TYPE> struct TypeTraits{}

��    �飺ͨ���������ػ�����ʵ�����͵���ȡ
*****************************************************************************/

struct __TrueType
{};
struct __FalseType
{};


template<class __TYPE>
struct TypeTraits
{
	typedef __FalseType HasTrivialDefaultConstructor;
	typedef __FalseType HasTrivialCopyConstructor;
	typedef __FalseType HasTrivialAssignmentOperator;
	typedef __FalseType HasTrivialDestructor;

	typedef __FalseType IsPODType;
};

template<>
struct TypeTraits<bool>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<char>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<unsigned char>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<short>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<unsigned short>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<int>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<unsigned int>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<float>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<unsigned long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<long long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<unsigned long long>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<>
struct TypeTraits<long double>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};

template<class TYPE>
struct TypeTraits<TYPE*>
{
	typedef __TrueType HasTrivialDefaultConstructor;
	typedef __TrueType HasTrivialCopyConstructor;
	typedef __TrueType HasTrivialAssignmentOperator;
	typedef __TrueType HasTrivialDestructor;

	typedef __TrueType IsPODType;
};



