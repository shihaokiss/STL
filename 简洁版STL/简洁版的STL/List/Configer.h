#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<assert.h>
#include<stdarg.h>
#include<string>
#define _list_
#define _vector_

//#define __USE_MALLOC__
#define __DEBUG__
#define __WIN32__

/*�������� 5 ������*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//������ֵļ̳���������ʱ����Ҫ���ϼ��ݵ�ԭ��

using namespace std;

