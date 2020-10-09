#ifndef _HEAP_H_
#define _HEAP_H_

#include"Common.h"

#define HEAP_DEFAULT_SIZE 20

typedef int HeapElemType;
typedef struct MinHeap
{
	HeapElemType *base;
	size_t        capacity;
	size_t        size;
}MinHeap;

void HeapInit(MinHeap *php,  int sz = HEAP_DEFAULT_SIZE);
void HeapCreate(MinHeap *php, int ar[], int n);
void HeapInsert(MinHeap *php, HeapElemType x);
void HeapErase(MinHeap *php);
void HeapShow(MinHeap *php);
bool HeapEmpty(MinHeap *php);
HeapElemType HeapTop(MinHeap *php);
void HeapSort(MinHeap *php, int ar[], int n);
void HeapShiftUp(MinHeap *php, int start);
void HeapShiftDown(MinHeap *php, int start, int n);
/////////////////////////////////////////////////////////////////////
void HeapInit(MinHeap *php, int sz)
{
	assert(php != NULL);
	php->capacity = sz > HEAP_DEFAULT_SIZE ? sz : HEAP_DEFAULT_SIZE;
	php->base = (HeapElemType*)malloc(sizeof(HeapElemType) * php->capacity);
	memset(php->base, 0, sizeof(HeapElemType) * php->capacity);
	php->size = 0;
}

void HeapCreate(MinHeap *php, HeapElemType ar[], int n)
{
	php->capacity = n;
	php->base = (HeapElemType*)malloc(sizeof(HeapElemType) * php->capacity);
	assert(php->base != NULL);
	for(int i=0; i<n; ++i)
		php->base[i] = ar[i];
	php->size = n;

	//堆调整
	int curpos = n/2 - 1; //找到最后一个分支
	while(curpos >= 0)
	{
		HeapShiftDown(php, curpos, n);
		curpos--;
	}
}

void HeapInsert(MinHeap *php, HeapElemType x)
{
	assert(php != NULL);
	if(php->size >= php->capacity)
	{
		printf("堆空间已满，%d 不能插入堆.\n", x);
		return;
	}

	php->base[php->size] = x;
	HeapShiftUp(php, php->size);
	php->size++;
}

void HeapErase(MinHeap *php)
{
	assert(php != NULL);
	if(php->size == 0)
	{
		printf("堆已空，不能删除堆顶元素.\n");
		return;
	}

	php->size--;
	php->base[0] = php->base[php->size];
	HeapShiftDown(php, 0, php->size);
}

bool HeapEmpty(MinHeap *php)
{
	assert(php != NULL);
	return php->size == 0;
}

HeapElemType HeapTop(MinHeap *php)
{
	assert(php!=NULL && php->size>0);
	return php->base[0];
}

void HeapSort(MinHeap *php, int ar[], int n)
{
	HeapCreate(php, ar, n);
	while(php->size > 0)
	{
		php->size--;
		Swap(&php->base[php->size], &php->base[0]);
		HeapShiftDown(php, 0, php->size);
	}

	for(int i=0; i<n; ++i)
		ar[i] = php->base[i];
}

void HeapShow(MinHeap *php)
{
	assert(php != NULL);
	for(int i=0; i<php->size; ++i)
		printf("%d ", php->base[i]);
	printf("\n");
}

void HeapShiftUp(MinHeap *php, int start) //i=parent j=child
{
	int j = start;
	int i = (j-1) / 2;
	while(j > 0)
	{
		if(php->base[j] < php->base[i])
		{
			Swap(&php->base[j], &php->base[i]);
			j = i;
			i = (j-1) / 2;
		}
		else
			break;
	}
}

void HeapShiftDown(MinHeap *php, int start, int n)
{
	int i = start;
	int j = 2*i+1;
	while(j < n)
	{
		if(j+1<n && php->base[j]>php->base[j+1]) //寻求左右子树中的最小值
			j++;
		if(php->base[i] > php->base[j])
		{
			Swap(&php->base[i], &php->base[j]);
			i = j;
			j = 2*i+1;
		}
		else 
			break;
	}
}

#endif /* _HEAP_H_ */