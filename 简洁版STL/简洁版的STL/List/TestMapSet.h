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
		Dictionary[1] = "���ݽṹ";
		Dictionary[2] = "C++";
		Dictionary[3] = "STLԴ������";
		Dictionary[3] = "����ϵͳ";

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
		Dictionary.insert(pair<int,string>(1,"���ݽṹ"));
		Dictionary.insert(pair<int, string>(2, "C++"));
		Dictionary.insert(pair<int, string>(3, "STLԴ������"));
		Dictionary.insert(pair<int, string>(3, "����ϵͳ"));

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
		Dictionary[4] = "���ݽṹ";
		Dictionary[3] = "C++";
		Dictionary[2] = "STLԴ������";
		Dictionary[2] = "����ϵͳ";

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
		Dictionary.insert(pair<int, string>(4, "���ݽṹ"));
		Dictionary.insert(pair<int, string>(3, "C++"));
		Dictionary.insert(pair<int, string>(2, "STLԴ������"));
		Dictionary.insert(pair<int, string>(2, "����ϵͳ"));

		unordered_multimap<int, string>::iterator it_begin = Dictionary.begin();
		while (it_begin != Dictionary.end())
		{
			cout << it_begin->first << " " << it_begin->second << endl;
			++it_begin;
		}
	}
}