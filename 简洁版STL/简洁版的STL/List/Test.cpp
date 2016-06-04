#include"List.h"
#include"Vector.h"
#include"Iterator.h"
#include"alloctaor.h"
#include"_Alloctaor.h"
using namespace IteratorStudy;
using namespace Traits;

//void Show(List<int> LIST)
//{
//	List<int>::iterator it_begin = LIST.begin(), it_end = LIST.end();
//	it_begin = LIST.begin();
//	it_end = LIST.end();
//	if (it_begin == it_end)
//	{
//		cout << "This List Is Empty!" << endl;
//		return;
//	}
//
//	while (it_begin != it_end)
//	{
//		cout << it_begin->_value << "->";
//		it_begin++;
//	}
//	cout << endl;
//
//	it_begin = LIST.begin();
//	it_end = LIST.end();
//	while (it_begin != it_end)
//	{
//		--it_end;
//		cout << it_end->_value << "->";
//	}
//	cout << endl;
//	cout << endl;
//}

//void Test()
//{
//#ifdef _list_
//	vector<int> VECTOR = { 0, 2, 4, 6, 8, 10 };
//	vector<int> VECTOR1 = { 1, 3, 5, 7, 9 };
//	List<int> list;
//	for (int i = 0; i < 6; ++i)
//		list.push_back(VECTOR[i]);
//
//	List<int> list2;
//	for (int i = 0; i < 5; ++i)
//		list2.push_back(VECTOR1[i]);
//
//	Show(list);
//	Show(list2);
//
//	//list.unique();   //去重
//	//Show(list);
//	//List<int>::iterator ItBegin = list.begin(), ItEnd = list.end(),ItTmp;
//	//ItTmp = ItBegin++;
//	//list.Transfer(ItEnd,ItTmp,ItBegin);  //测试节点的交换函数
//	//Show(list);
//
//	list.merge(list2);
//	Show(list);
//	list.reverse();
//	Show(list);
//
//#endif
//#ifdef _LIST_
//	vector<int> Vector = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	List<int> LIST;
//	for (int i = 5; i < 10; ++i)
//		LIST.push_back(Vector[i]);
//	for (int i = 4; i >= 0; --i)
//		LIST.push_front(Vector[i]);
//
//	/*Show(LIST);
//	Show(list);
//	cout << endl;
//	LIST.Swap(list); 
//	Show(LIST);
//	Show(list);
//
//	cout << LIST.empty() << " ";
//	cout << LIST.front() << " ";
//	cout << LIST.back() << endl;*/
//
//	Show(LIST);
//	List<int>::iterator it = LIST.begin();
//	it++;
//	LIST.erase(it);  //删除
//	Show(LIST); 
//	LIST.insert(LIST.end(), 5, 100);
//	Show(LIST);
//	LIST.resize(20,0);  //重新定义长度
//	Show(LIST);
//	//LIST.resize(10);   //重定义长度
//	//Show(LIST);
//	//LIST.pop_back();   //尾删
//	//LIST.pop_front();  //头删
//	//Show(LIST);
//	LIST.remove(0);   //删除相应的元素
//	Show(LIST);
//#endif
//
//}

void Test2()
{
	Vector<int > v1;   
	v1.PushBack(1);   
	v1.PushBack(2);
	v1.PushBack(3); 
	v1.PushBack(4);     
	v1.PushBack(5);    
	v1.PushBack(6);    
	v1.PushBack(7);   
	v1.PushBack(8);
	v1.Print();

	Vector<int>::Iterator iter = v1.begin();
	iter = iter + 2;
	/*cout << v1.back() << endl;
	cout << v1.capacity() << endl;;
	cout << v1.empty() << endl;;
	v1.erase(v1.begin() + 5);
	v1.Print();
	cout << v1.front() << endl;;
	v1.insert(v1.begin() + 2, 100);
	v1.Print();
	v1.pop_back();
	v1.Print();
	v1.PushBack(1000);
	v1.Print();
	cout << v1.size() << endl;;

	Vector<int > v2;
	v2.PushBack(10);
	v2.PushBack(20);
	v2.PushBack(30);
	v2.PushBack(40);
	v2.PushBack(50);
	v2.PushBack(60);
	v2.PushBack(70);
	v2.PushBack(80);
	v2.Print();*/
}


void main()
{
	//Test();   //list 测试
	//Test2();  //vector 测试
	//Traits::DistanceTest();
	//Traits::AdvanceTest();

	string str("shihaohhhhhhhhhh");
	size_t count = str.rfind('h');
	int count1 = string::npos;
}