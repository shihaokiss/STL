#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<assert.h>
#define _list_
#define _vector_


/*迭代器的 5 个类型*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//这里出现的继承是由于有时候需要向上兼容的原因

using namespace std;