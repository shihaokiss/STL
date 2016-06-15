#pragma once
#include"Configer.h"
#include<map>
#include <unordered_map>
using std::unordered_map;

namespace TestMapSet
{
	void TestMap()
	{
		map<int,string> Dictionary;
		Dictionary[1] = "数据结构";
		Dictionary[2] = "C++";
		Dictionary[3] = "STL源码剖析";
		Dictionary[3] = "操作系统";

		map<int,string>::iterator it_begin = Dictionary.begin();
		while (it_begin != Dictionary.end())
		{
			cout << it_begin->first<<" "<<it_begin->second << endl;
			++it_begin;
		}
	}

	void TestMutilmap()
	{
		multimap<int, string> Dictionary;
		Dictionary.insert(pair<int,string>(1,"数据结构"));
		Dictionary.insert(pair<int, string>(2, "C++"));
		Dictionary.insert(pair<int, string>(3, "STL源码剖析"));
		Dictionary.insert(pair<int, string>(3, "操作系统"));

		multimap<int, string>::iterator it_begin = Dictionary.begin();
		while (it_begin != Dictionary.end())
		{
			cout << it_begin->first << " " << it_begin->second << endl;
			++it_begin;
		}
	}

	void TestUnorderMap()
	{
		unordered_map<int, string> Dictionary;
		Dictionary[4] = "数据结构";
		Dictionary[3] = "C++";
		Dictionary[2] = "STL源码剖析";
		Dictionary[2] = "操作系统";

		unordered_map<int, string>::iterator it_begin = Dictionary.begin();
		while (it_begin != Dictionary.end())
		{
			cout << it_begin->first << " " << it_begin->second << endl;
			++it_begin;
		}
	}

	void TestMutilUnorderMap()
	{
		unordered_multimap<int, string> Dictionary;
		Dictionary.insert(pair<int, string>(4, "数据结构"));
		Dictionary.insert(pair<int, string>(3, "C++"));
		Dictionary.insert(pair<int, string>(2, "STL源码剖析"));
		Dictionary.insert(pair<int, string>(2, "操作系统"));

		unordered_multimap<int, string>::iterator it_begin = Dictionary.begin();
		while (it_begin != Dictionary.end())
		{
			cout << it_begin->first << " " << it_begin->second << endl;
			++it_begin;
		}
	}
}