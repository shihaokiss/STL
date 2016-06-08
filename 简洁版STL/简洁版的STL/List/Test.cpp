#include"Configer.h"
#include"List.h"
#include"Vector.h"
#include"Iterator.h"
#include"_Alloctaor.h"
#include"Trace.h"
#include"TypeTraits.h"


/*****************************************************************************************/
//测试 Distance，Advance 函数
/*****************************************************************************************/
//void DistanceTest()
//{
//	List<int> LIST;
//	Vector<int> VECTOR;
//	for (int i = 0; i < 10; ++i)
//	{
//		LIST.push_back(i);
//		VECTOR.PushBack(i);
//	}
//
//	cout << Traits::Distance(LIST.begin(), LIST.end()) << endl;
//	cout << Traits::Distance(VECTOR.begin(), VECTOR.end()) << endl;
//}
//
//void AdvanceTest()
//{
//	List<int> LIST;
//	Vector<int> VECTOR;
//	for (int i = 0; i < 10; ++i)
//	{
//		LIST.push_back(i);
//		VECTOR.PushBack(i);
//	}
//
//	List<int>::iterator LIST_IT = LIST.begin();
//	Vector<int>::Iterator VECTOR_IT = VECTOR.begin();
//	Traits::Advance(LIST_IT, 5);
//	Traits::Advance(VECTOR_IT, 8);
//
//	cout << *LIST_IT << endl;
//	cout << *VECTOR_IT << endl;
//}

void Test()
{
	//测试类型萃取机
	/*DistanceTest();
	AdvanceTest();*/

	//测试Trace
	/*char* ch = "shihao";
	int c = 100;
	__TRECE__("%s,%d\n", ch, c);*/

	//测试一级空间配置器
	/*Allocator::__MallocAllocTemplate<0> TEST;
	void* p = TEST.Allocate(100);
	TEST.Reallocate(p, 100);
	TEST.Deallocate(p);
	TEST.OomMalloc(100);
	TEST.OomRealloc(p,100);*/

	/*测试二级空间配置器 （未封装之前）*/
	//Allocator::__DefaultAllocTemplate<0, 0> TEST;
	//void* p[30];
	//for (int i = 0; i < 20; ++i)    //将自由链表中的内存耗尽
	//{
	//	p[i] = TEST.Allocate(10);
	//}                              
	//p[20] = TEST.Allocate(128);    //重新申请空间
	//p[21] = TEST.Allocate(128);
	//p[22] = TEST.Allocate(128);
	//p[23] = TEST.Allocate(128);
	//TEST.Deallocate(p[23],128);    //向自由链表中挂节点
	//TEST.Deallocate(p[22], 128);
	//TEST.Deallocate(p[21], 128);
	//p[24] = TEST.Allocate(1024);
	//TEST.Deallocate(p[24], 1024);
	//p[25] = TEST.Allocate(7);     //测试 Reallocate 函数
	//TEST.Reallocate(p[25], 7, 25);

	/*测试对空间配置器封装后的效果*/
	//int* p[30];
	//for (int i = 0; i < 20; ++i)
	//{
	//	p[i] = SimplateAlloc<int>::Allocate(10);
	//}
	//p[20] = SimplateAlloc<int>::Allocate(15);
	//p[21] = SimplateAlloc<int>::Allocate(15);
	//p[22] = SimplateAlloc<int>::Allocate(15);
	//SimplateAlloc<int>::Deallocate(p[20],15);
	//SimplateAlloc<int>::Deallocate(p[21], 15);
	//SimplateAlloc<int>::Deallocate(p[22], 15);

	/**/

}




void main()
{
	//Test();
	//ListTest::Test();
	ListTest::TestReverseIterator();
}





