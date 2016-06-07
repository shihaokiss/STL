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

/*迭代器的 5 个类型*/
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag { BidirectionalIteratorTag(){} };
struct RandomAccessIteratorTag : public BidirectionalIteratorTag { RandomAccessIteratorTag(){} };
//这里出现的继承是由于有时候需要向上兼容的原因

using namespace std;

