#include"List.h"
#include"Vector.h"
#include"Iterator.h"
#include"_Alloctaor.h"
#include"Trace.h"
#include"Configer.h"
using namespace IteratorStudy;
using namespace Traits;
using namespace TRACE;
//using namespace Allocator;

void Test()
{
	//����Trace
	/*char* ch = "shihao";
	int c = 100;
	__TRECE__("%s,%d\n", ch, c);*/

	//����һ���ռ�������
	/*Allocator::__MallocAllocTemplate<0> TEST;
	void* p = TEST.Allocate(100);
	TEST.Reallocate(p, 100);
	TEST.Deallocate(p);
	TEST.OomMalloc(100);
	TEST.OomRealloc(p,100);*/

	/*���Զ����ռ������� ��δ��װ֮ǰ��*/
	//Allocator::__DefaultAllocTemplate<0, 0> TEST;
	//void* p[30];
	//for (int i = 0; i < 20; ++i)    //�����������е��ڴ�ľ�
	//{
	//	p[i] = TEST.Allocate(10);
	//}                              
	//p[20] = TEST.Allocate(128);    //��������ռ�
	//p[21] = TEST.Allocate(128);
	//p[22] = TEST.Allocate(128);
	//p[23] = TEST.Allocate(128);
	//TEST.Deallocate(p[23],128);    //�����������йҽڵ�
	//TEST.Deallocate(p[22], 128);
	//TEST.Deallocate(p[21], 128);
	//p[24] = TEST.Allocate(1024);
	//TEST.Deallocate(p[24], 1024);
	//p[25] = TEST.Allocate(7);     //���� Reallocate ����
	//TEST.Reallocate(p[25], 7, 25);

	/*���ԶԿռ���������װ���Ч��*/
	int* p[30];
	for (int i = 0; i < 20; ++i)
	{
		p[i] = SimplateAlloc<int>::Allocate(10);
	}
	p[20] = SimplateAlloc<int>::Allocate(15);
	p[21] = SimplateAlloc<int>::Allocate(15);
	p[22] = SimplateAlloc<int>::Allocate(15);
	SimplateAlloc<int>::Deallocate(p[20],15);
	SimplateAlloc<int>::Deallocate(p[21], 15);
	SimplateAlloc<int>::Deallocate(p[22], 15);
}

void main()
{
	Test();
}





