#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<assert.h>
#define _list_
#define _vector_


/*�������� 5 ������*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//������ֵļ̳���������ʱ����Ҫ���ϼ��ݵ�ԭ��

using namespace std;