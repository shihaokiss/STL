#pragma once
#include"Configer.h"
#include"Trace.h"
/*****************************************************************************
文件名: STL 空间配置器

创建时间: 2016-6-4

作者: 石豪

所在单位: 陕西科技大学

实现功能: 分配内存空间
备注: 高效

修改记录：
日期       版本        修改人             修改内容


*****************************************************************************/



//namespace Allocator
//{

/*****************************************************************************
功能描述：一级空间配置器

类 /函数：template<int inst>  class __MallocAllocTemplate;

简    介：直接调用 malloc/free，内存分配失败后调用句柄处理函数
*****************************************************************************/

typedef void(*ALLOC_OOM_FUN)();  //内存分配失败以后处理的句柄handler类型
template<int inst>
class __MallocAllocTemplate
{
private:  
	static ALLOC_OOM_FUN __sMallocAllocOomHandler;
	static void* OomMalloc(size_t n)   //模仿 c++ 的 set_new_handler 机制
	{

		//打 Trace 信息
		__TRECE__("句柄函数的指针 %p\n", __sMallocAllocOomHandler);

		ALLOC_OOM_FUN handler = __sMallocAllocOomHandler;
		void* result;

		for (;;)  //一直循环，直到内存分配成功为止
		{
			if (handler == 0)  //检查是否设置处理的 handler
			{
				cout << "out of memory " << endl;
				exit(-1);
			}
			handler();    //调用客户自己的内存管理函数，释放内存
			result = malloc(n);  
			if (result)		//分配成功
				return result;
		}
	}

	static void* OomRealloc(void*p, size_t n)
	{

		//打 Trace 
		__TRECE__("\n");

		ALLOC_OOM_FUN handler = __sMallocAllocOomHandler;
		void* result;

		for (;;)  //一直循环，直到内存分配成功为止
		{
			if (handler == 0)  //检查是否设置处理的 handler
			{
				cout << "out of memory " << endl;
				exit(-1);
			}
			handler();    //调用客户自己的内存管理函数，释放内存
			result = realloc(p,n);
			if (result)		//分配成功
				return result;
		}
	}


public:
	static void* Allocate(size_t n)  //直接调用 malloc
	{
		//打 Trace 
		__TRECE__("申请 %d Bytes \n",n);

		void* result = malloc(n);
		return result == 0 ? OomMalloc(n) : result;
	}

	static void Deallocate(void* p,size_t)   //直接 free
	{
		//打 Trace 
		__TRECE__("释放空间\n");

		free(p);
	}

	static void *Reallocate(void*p,size_t new_sz)
	{
		//打 Trace 
		__TRECE__("重新申请 %d Bytes \n", new_sz);

		void* result = realloc(p, new_sz);
		return result == 0 ? OomRealloc(p, new_sz) : result;
	}

	static void(*SetMallocHandler(void(*f)()))()    //重新设置句柄处理函数
	{
		ALLOC_OOM_FUN result = __sMallocAllocOomHandler;
		__sMallocAllocOomHandler = f;
		return result;
	}
};

//初始化分配内存失败处理函数的句柄函数指针 
template<int inst>
ALLOC_OOM_FUN __MallocAllocTemplate<inst>::__sMallocAllocOomHandler = 0;


typedef __MallocAllocTemplate<0> MallocAlloc;

//#define __USE_MALLOC

#ifdef __USE_MALLOC__      //开关
typedef __MallocAllocTemplate<0> MallocAlloc;
typedef MallocAlloc _Alloc;
#else


/*****************************************************************************
功能描述：二级空间配置器

类 ：template<bool threads, int inst>  class __DefaultAllocTemplate;

简    介：将空间先预分配给内存池，当需要小空间时，在从内存池中取
*****************************************************************************/

template<bool threads, int inst>
class __DefaultAllocTemplate
{
public:
	enum{ __ALIGN = 8 };                        //排列基准值（也是排列间隔）   
	enum{ __MAX_BYTES = 128 };                   //最大值    
	enum{ __NFREELISTS = __MAX_BYTES / __ALIGN };    //排列链大小
	static size_t ROUND_UP(size_t bytes)
	{
		return (bytes + __ALIGN - 1 & ~(__ALIGN - 1));  //内存与 8 对齐
	}
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) / __ALIGN - 1);  //返回在自由链表中的下标
	}

	union Obj
	{
		union Obj* _freeListLink;   //指向下一个内存块的指针
		char _clientData[1];   /* The client sees this.*/
	};

	static Obj* volatile _freeList[__NFREELISTS];    //自由链表    
	static char* _startFree;                        //内存池起始地址   
	static char* _endFree;                          //内存池结束地址    
	static size_t _heapSize;                        //内存池的容量   

	//从内存池中获取内存插入到自由链表中    
	static void* Refill(size_t n);
	//从内存池中分配内存   
	static char* ChunkAlloc(size_t size, int& nobjs);
	//用户调用申请内存函数
	static void* Allocate(size_t n);
	//内存释放函数
	static void Deallocate(void*p, size_t n);
	//重新分配内存
	static void* Reallocate(void*p, size_t old_sz, size_t new_sz);
};

//初始化全局静态对象 
//1.自由链表
template<bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj* volatile
__DefaultAllocTemplate<threads, inst>::_freeList[__DefaultAllocTemplate<threads, inst>::__NFREELISTS];
//2.内存池
template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = 0;
template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = 0;
template<bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;


//类中声明函数的定义
template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Refill(size_t n)
{

	int nobjs = 20;
	char* result = ChunkAlloc(n, nobjs);

	//Trace 信息
	__TRECE__("向内存池中申请了 %d * %d Bytes", n, nobjs);

	if (nobjs == 1)
		return result;
	Obj* cur = (Obj*)(result + n);
	size_t index = FREELIST_INDEX(n);
		_freeList[index] = cur;
	for (int i = 2; i < nobjs; ++i)  //链表的头插
	{
		cur->_freeListLink = (Obj*)(i*n + result);
		cur = cur->_freeListLink;
	}

#ifdef __DEBUG__
	cout << "将多余的空间插入到链表中去" << endl;
#endif

	cur->_freeListLink = NULL;
	return result;
}


template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::ChunkAlloc(size_t size, int& nobjs)
{
	char* result;
	size_t bytesNeed = size*nobjs;
	size_t bytesHave = _endFree - _startFree;

	//Trace 信息
	__TRECE__("所需空间为 %d * %d Bytes\n内存池中空间为 %d Bytes\n", size, nobjs, bytesHave);

	if (bytesHave >= bytesNeed)   //内存池中所剩内存大于需要的内存
	{
		result = _startFree;
		_startFree += bytesNeed;

#ifdef __DEBUG__
		cout << "内存池中所剩内存大于需要的内存" << endl;
#endif
	}
	else if (bytesHave >= size)   //至少能满足一个 size 的分配
	{
		result = _startFree;
		nobjs = bytesHave / size;
		_startFree += size*nobjs;

#ifdef __DEBUG__
		cout << "至少能满足一个 size 的分配" << endl;
#endif
	}
	else      //内存池中所剩空间不够一个 size
	{
#ifdef __DEBUG__
		cout << "内存池中所剩空间不够一个 size,清空内存重新注入" << endl;
#endif

		//清空内存池，准备往内存池中补充空间
		if (bytesHave > 0)
		{
			Obj* cur = (Obj*)_startFree;
			size_t index = FREELIST_INDEX(bytesHave);
			cur->_freeListLink = _freeList[index];
			_freeList[index] = cur;
			_startFree = NULL, _endFree = NULL;
		}
		
		//重新向系统申请 bytesNeed*2 + _heapSize/16
		size_t bytesToGet = bytesNeed * 2 + (_heapSize >> 4);
		_startFree = (char*)malloc(bytesToGet);

		if (_startFree == NULL)    //向系统申请内存失败
		{
			//先向自由链表上游中的大块内存链中寻找
			for (int i = size; i <= __MAX_BYTES; i += __ALIGN)
			{
				Obj* head = _freeList[FREELIST_INDEX(size)];
				if (head)
				{
					_startFree = (char*)head;
					_endFree = (char*)head + i;
					_freeList[FREELIST_INDEX(size)] = head->_freeListLink;
					return ChunkAlloc(size, nobjs);
				}
			}
			//链表中也没有了，实在无奈，调用一级配置器中的内存分配函数
			_startFree = (char*)MallocAlloc::Allocate(bytesToGet);
		}

		_heapSize += bytesToGet;
		_endFree = _startFree + bytesToGet;
		return ChunkAlloc(size, nobjs);  //函数的复用
	}
	return result;
}



template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Allocate(size_t n)
{
	//Trace 信息
	__TRECE__("利用二级空间配置器申请 %d Bytes\n", n);

	void* result;
	if (n > __MAX_BYTES)
	{
		result = MallocAlloc::Allocate(n);
		return result;
	}
		
	//
	//自由链表有，就直接取
	//没有，就通过 Refill进行填充
	//
	size_t index = FREELIST_INDEX(n);
	if (_freeList[index])
	{
#ifdef __DEBUG__
		cout << "自由链表中有相应快的内存" << endl;
#endif

		result = _freeList[index];
		_freeList[index] = ((Obj*)result)->_freeListLink;
	}
	else
	{
#ifdef __DEBUG__
		cout << "自由链表中没有相应快大小的内存" << endl;
#endif

		result = Refill(ROUND_UP(n));
	}

	return result;
}

template<bool threads, int inst>
void __DefaultAllocTemplate<threads, inst>::Deallocate(void*p, size_t n)
{
	//Trace 信息
	__TRECE__("利用二级空间配置器释放 %d Bytes\n", n);

	if (n > __MAX_BYTES)
		MallocAlloc::Deallocate(p,0);
	//不大于 __MAX_BYTES ，将此空间插回自由链表
	else
	{
		size_t index = FREELIST_INDEX(n);
		Obj* cur = (Obj*)p;
		cur->_freeListLink = _freeList[index];
		_freeList[index] = cur;
	}
}

template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Reallocate(void* p, size_t old_sz, size_t new_sz)
{
	//Trace 信息
	__TRECE__("利用二级空间配置器重新申请 %d Bytes\n", new_sz);

	void* result;
	if (old_sz > (size_t)__MAX_BYTES && new_sz > (size_t)__MAX_BYTES)    //
		return realloc(p, new_sz);
	if (ROUND_UP(old_sz) == ROUND_UP(new_sz))
		return p;
	result = Allocate(new_sz);
	size_t size = old_sz > new_sz ? old_sz : new_sz;
	memcpy(result, p, size);
	Deallocate(p, old_sz);
	return result;
}


typedef __DefaultAllocTemplate<false, 0> _Alloc;
#endif // __USE_MALLOC

//}


/*****************************************************************************
功能描述：对空间配置器的封装

类 /函数：

简    介：
*****************************************************************************/

template<class T, class Alloc = _Alloc>
class SimplateAlloc
{
public:
	static T* Allocate(size_t n)
	{
		return (T*)Alloc::Allocate(n * sizeof(T));
	}
	static T* Allocate(void)
	{
		return (T*)Alloc::Allocate(sizeof(T));
	}
	static void Deallocate(T* p, size_t n)
	{
		Alloc::Deallocate(p, n*sizeof(T));
	}
	static void Deallocate(T* p)
	{
		Alloc::Deallocate(p, sizeof(T));
	}
};

