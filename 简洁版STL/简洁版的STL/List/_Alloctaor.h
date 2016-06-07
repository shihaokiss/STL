#pragma once
#include"Configer.h"
#include"Trace.h"
/*****************************************************************************
�ļ���: STL �ռ�������

����ʱ��: 2016-6-4

����: ʯ��

���ڵ�λ: �����Ƽ���ѧ

ʵ�ֹ���: �����ڴ�ռ�
��ע: ��Ч

�޸ļ�¼��
����       �汾        �޸���             �޸�����


*****************************************************************************/



//namespace Allocator
//{

/*****************************************************************************
����������һ���ռ�������

�� /������template<int inst>  class __MallocAllocTemplate;

��    �飺ֱ�ӵ��� malloc/free���ڴ����ʧ�ܺ���þ��������
*****************************************************************************/

typedef void(*ALLOC_OOM_FUN)();  //�ڴ����ʧ���Ժ���ľ��handler����
template<int inst>
class __MallocAllocTemplate
{
private:  
	static ALLOC_OOM_FUN __sMallocAllocOomHandler;
	static void* OomMalloc(size_t n)   //ģ�� c++ �� set_new_handler ����
	{

		//�� Trace ��Ϣ
		__TRECE__("���������ָ�� %p\n", __sMallocAllocOomHandler);

		ALLOC_OOM_FUN handler = __sMallocAllocOomHandler;
		void* result;

		for (;;)  //һֱѭ����ֱ���ڴ����ɹ�Ϊֹ
		{
			if (handler == 0)  //����Ƿ����ô���� handler
			{
				cout << "out of memory " << endl;
				exit(-1);
			}
			handler();    //���ÿͻ��Լ����ڴ���������ͷ��ڴ�
			result = malloc(n);  
			if (result)		//����ɹ�
				return result;
		}
	}

	static void* OomRealloc(void*p, size_t n)
	{

		//�� Trace 
		__TRECE__("\n");

		ALLOC_OOM_FUN handler = __sMallocAllocOomHandler;
		void* result;

		for (;;)  //һֱѭ����ֱ���ڴ����ɹ�Ϊֹ
		{
			if (handler == 0)  //����Ƿ����ô���� handler
			{
				cout << "out of memory " << endl;
				exit(-1);
			}
			handler();    //���ÿͻ��Լ����ڴ���������ͷ��ڴ�
			result = realloc(p,n);
			if (result)		//����ɹ�
				return result;
		}
	}


public:
	static void* Allocate(size_t n)  //ֱ�ӵ��� malloc
	{
		//�� Trace 
		__TRECE__("���� %d Bytes \n",n);

		void* result = malloc(n);
		return result == 0 ? OomMalloc(n) : result;
	}

	static void Deallocate(void* p,size_t)   //ֱ�� free
	{
		//�� Trace 
		__TRECE__("�ͷſռ�\n");

		free(p);
	}

	static void *Reallocate(void*p,size_t new_sz)
	{
		//�� Trace 
		__TRECE__("�������� %d Bytes \n", new_sz);

		void* result = realloc(p, new_sz);
		return result == 0 ? OomRealloc(p, new_sz) : result;
	}

	static void(*SetMallocHandler(void(*f)()))()    //�������þ��������
	{
		ALLOC_OOM_FUN result = __sMallocAllocOomHandler;
		__sMallocAllocOomHandler = f;
		return result;
	}
};

//��ʼ�������ڴ�ʧ�ܴ������ľ������ָ�� 
template<int inst>
ALLOC_OOM_FUN __MallocAllocTemplate<inst>::__sMallocAllocOomHandler = 0;


typedef __MallocAllocTemplate<0> MallocAlloc;

//#define __USE_MALLOC

#ifdef __USE_MALLOC__      //����
typedef __MallocAllocTemplate<0> MallocAlloc;
typedef MallocAlloc _Alloc;
#else


/*****************************************************************************
���������������ռ�������

�� ��template<bool threads, int inst>  class __DefaultAllocTemplate;

��    �飺���ռ���Ԥ������ڴ�أ�����ҪС�ռ�ʱ���ڴ��ڴ����ȡ
*****************************************************************************/

template<bool threads, int inst>
class __DefaultAllocTemplate
{
public:
	enum{ __ALIGN = 8 };                        //���л�׼ֵ��Ҳ�����м����   
	enum{ __MAX_BYTES = 128 };                   //���ֵ    
	enum{ __NFREELISTS = __MAX_BYTES / __ALIGN };    //��������С
	static size_t ROUND_UP(size_t bytes)
	{
		return (bytes + __ALIGN - 1 & ~(__ALIGN - 1));  //�ڴ��� 8 ����
	}
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return ((bytes + __ALIGN - 1) / __ALIGN - 1);  //���������������е��±�
	}

	union Obj
	{
		union Obj* _freeListLink;   //ָ����һ���ڴ���ָ��
		char _clientData[1];   /* The client sees this.*/
	};

	static Obj* volatile _freeList[__NFREELISTS];    //��������    
	static char* _startFree;                        //�ڴ����ʼ��ַ   
	static char* _endFree;                          //�ڴ�ؽ�����ַ    
	static size_t _heapSize;                        //�ڴ�ص�����   

	//���ڴ���л�ȡ�ڴ���뵽����������    
	static void* Refill(size_t n);
	//���ڴ���з����ڴ�   
	static char* ChunkAlloc(size_t size, int& nobjs);
	//�û����������ڴ溯��
	static void* Allocate(size_t n);
	//�ڴ��ͷź���
	static void Deallocate(void*p, size_t n);
	//���·����ڴ�
	static void* Reallocate(void*p, size_t old_sz, size_t new_sz);
};

//��ʼ��ȫ�־�̬���� 
//1.��������
template<bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj* volatile
__DefaultAllocTemplate<threads, inst>::_freeList[__DefaultAllocTemplate<threads, inst>::__NFREELISTS];
//2.�ڴ��
template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = 0;
template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = 0;
template<bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;


//�������������Ķ���
template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Refill(size_t n)
{

	int nobjs = 20;
	char* result = ChunkAlloc(n, nobjs);

	//Trace ��Ϣ
	__TRECE__("���ڴ���������� %d * %d Bytes", n, nobjs);

	if (nobjs == 1)
		return result;
	Obj* cur = (Obj*)(result + n);
	size_t index = FREELIST_INDEX(n);
		_freeList[index] = cur;
	for (int i = 2; i < nobjs; ++i)  //�����ͷ��
	{
		cur->_freeListLink = (Obj*)(i*n + result);
		cur = cur->_freeListLink;
	}

#ifdef __DEBUG__
	cout << "������Ŀռ���뵽������ȥ" << endl;
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

	//Trace ��Ϣ
	__TRECE__("����ռ�Ϊ %d * %d Bytes\n�ڴ���пռ�Ϊ %d Bytes\n", size, nobjs, bytesHave);

	if (bytesHave >= bytesNeed)   //�ڴ������ʣ�ڴ������Ҫ���ڴ�
	{
		result = _startFree;
		_startFree += bytesNeed;

#ifdef __DEBUG__
		cout << "�ڴ������ʣ�ڴ������Ҫ���ڴ�" << endl;
#endif
	}
	else if (bytesHave >= size)   //����������һ�� size �ķ���
	{
		result = _startFree;
		nobjs = bytesHave / size;
		_startFree += size*nobjs;

#ifdef __DEBUG__
		cout << "����������һ�� size �ķ���" << endl;
#endif
	}
	else      //�ڴ������ʣ�ռ䲻��һ�� size
	{
#ifdef __DEBUG__
		cout << "�ڴ������ʣ�ռ䲻��һ�� size,����ڴ�����ע��" << endl;
#endif

		//����ڴ�أ�׼�����ڴ���в���ռ�
		if (bytesHave > 0)
		{
			Obj* cur = (Obj*)_startFree;
			size_t index = FREELIST_INDEX(bytesHave);
			cur->_freeListLink = _freeList[index];
			_freeList[index] = cur;
			_startFree = NULL, _endFree = NULL;
		}
		
		//������ϵͳ���� bytesNeed*2 + _heapSize/16
		size_t bytesToGet = bytesNeed * 2 + (_heapSize >> 4);
		_startFree = (char*)malloc(bytesToGet);

		if (_startFree == NULL)    //��ϵͳ�����ڴ�ʧ��
		{
			//�����������������еĴ���ڴ�����Ѱ��
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
			//������Ҳû���ˣ�ʵ�����Σ�����һ���������е��ڴ���亯��
			_startFree = (char*)MallocAlloc::Allocate(bytesToGet);
		}

		_heapSize += bytesToGet;
		_endFree = _startFree + bytesToGet;
		return ChunkAlloc(size, nobjs);  //�����ĸ���
	}
	return result;
}



template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Allocate(size_t n)
{
	//Trace ��Ϣ
	__TRECE__("���ö����ռ����������� %d Bytes\n", n);

	void* result;
	if (n > __MAX_BYTES)
	{
		result = MallocAlloc::Allocate(n);
		return result;
	}
		
	//
	//���������У���ֱ��ȡ
	//û�У���ͨ�� Refill�������
	//
	size_t index = FREELIST_INDEX(n);
	if (_freeList[index])
	{
#ifdef __DEBUG__
		cout << "��������������Ӧ����ڴ�" << endl;
#endif

		result = _freeList[index];
		_freeList[index] = ((Obj*)result)->_freeListLink;
	}
	else
	{
#ifdef __DEBUG__
		cout << "����������û����Ӧ���С���ڴ�" << endl;
#endif

		result = Refill(ROUND_UP(n));
	}

	return result;
}

template<bool threads, int inst>
void __DefaultAllocTemplate<threads, inst>::Deallocate(void*p, size_t n)
{
	//Trace ��Ϣ
	__TRECE__("���ö����ռ��������ͷ� %d Bytes\n", n);

	if (n > __MAX_BYTES)
		MallocAlloc::Deallocate(p,0);
	//������ __MAX_BYTES �����˿ռ�����������
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
	//Trace ��Ϣ
	__TRECE__("���ö����ռ��������������� %d Bytes\n", new_sz);

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
�����������Կռ��������ķ�װ

�� /������

��    �飺
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

