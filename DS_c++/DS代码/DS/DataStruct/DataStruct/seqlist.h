#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include"Common.h"

#define SEQLIST_DEFAULT_SIZE 8

//定义顺序表的结构
typedef struct SeqList
{
	ElemType *base;
	size_t    capacity;
	size_t    size;
}SeqList;

void SeqListInit(SeqList *plist);
void SeqListDestroy(SeqList *plist);
void SeqListPushBack(SeqList *plist, ElemType x);
void SeqListPushFront(SeqList *plist, ElemType x);
void SeqListShow(SeqList *plist);

void SeqListPopBack(SeqList *plist);
void SeqListPopFront(SeqList *plist);
void SeqListClear(SeqList *plist);
bool SeqListInsertByPos(SeqList *plist, int pos, ElemType x);
bool SeqListInsertByVal(SeqList *plist, ElemType x);
void SeqListEraseByPos(SeqList *plist, int pos);
void SeqListEraseByVal(SeqList *plist, ElemType key);
void SeqListSort(SeqList *plist);

size_t SeqListLength(SeqList *plist);
size_t SeqListCapacity(SeqList *plist);

int SeqListFind(SeqList *plist, ElemType key);

void SeqListReverse(SeqList *plist);

ElemType SeqListFront(SeqList *plist);
ElemType SeqListBack(SeqList *plist);
int      SeqListFind_Binary(SeqList *plist, ElemType key);
void     SeqListEraseAll(SeqList *plist, ElemType key);

/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

bool _Inc(SeqList *plist, size_t new_capacity)
{
#if 0
	assert(plist != NULL && new_capacity > plist->capacity);
	ElemType *new_base = (ElemType*)realloc(plist->base, sizeof(ElemType) * new_capacity); //realloc
	if(new_base == NULL)
		return false;
	plist->base = new_base;
	plist->capacity = new_capacity;
	return true;
#endif

	assert(plist != NULL && new_capacity > plist->capacity);
	
	ElemType *new_base = (ElemType*)malloc(sizeof(ElemType) * new_capacity); //realloc 重新开辟空间
	if(new_base == NULL)
		return false;
	
	memcpy(new_base, plist->base, sizeof(ElemType)*(plist->capacity)); // 拷贝原始数据

	free(plist->base);  //释放旧空间

	plist->base = new_base;  // 更改空间指向和容量
	plist->capacity = new_capacity;
	return true;
}

bool IsFull(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size >= plist->capacity;
}
bool IsEmpty(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size == 0;
}

void SeqListInit(SeqList *plist)
{
	assert(plist != NULL);
	plist->capacity = SEQLIST_DEFAULT_SIZE;
	plist->base = (ElemType*)malloc(sizeof(ElemType) * plist->capacity);
	plist->size = 0;
}

void SeqListDestroy(SeqList *plist)
{
	assert(plist != NULL);
	free(plist->base);
	plist->base = NULL;
	plist->capacity = plist->size = 0;
}

void SeqListPushBack(SeqList *plist, ElemType x)
{
	assert(plist != NULL);

	if(IsFull(plist) && !_Inc(plist, plist->capacity * 2))
	{
		printf("顺序表已满，%d 不能头部插入.\n", x);
		return;
	}
	plist->base[plist->size++] = x;
}

void SeqListPushFront(SeqList *plist, ElemType x)
{
	assert(plist != NULL);
	//判满
	if(IsFull(plist) && !_Inc(plist, plist->capacity * 2) )
	{
		printf("顺序表已满，%d 不能尾部插入.\n", x);
		return;
	}
	//头插
	for(size_t i=plist->size; i>0; --i)
		plist->base[i] = plist->base[i-1];
	plist->base[0] = x;
	plist->size++;
}

void SeqListShow(SeqList *plist)
{
	assert(plist != NULL);
	for(size_t i=0; i<plist->size; ++i)
		printf("%d ",plist->base[i]);
	printf("\n");
}

size_t SeqListLength(SeqList *plist)
{
	assert(plist != NULL);
	return plist->size;
}

size_t SeqListCapacity(SeqList *plist)
{
	assert(plist != NULL);
	return plist->capacity;
}

void SeqListPopBack(SeqList *plist)
{
	assert(plist != NULL);
	//判空
	if(IsEmpty(plist))
	{
		printf("顺序表已空,不能尾部删除.\n");
		return;
	}
	plist->size--;
}

void SeqListPopFront(SeqList *plist)
{
	assert(plist != NULL);
	if(IsEmpty(plist))
	{
		printf("顺序表已空,不能头部删除.\n");
		return;
	}

	for(size_t i=0; i<plist->size; ++i)
		plist->base[i] = plist->base[i+1];
	plist->size--;
}

void SeqListClear(SeqList *plist)
{
	assert(plist != NULL);
	plist->size = 0;
}

bool SeqListInsertByPos(SeqList *plist, int pos, ElemType x)
{
	assert(plist != NULL);
	if(IsFull(plist) && !_Inc(plist, plist->capacity * 2))
	{
		printf("顺序表已满,%d 不能在 %d 位置插入.\n", x, pos);
		return false;
	}
	if(pos<0 || pos>plist->size)
	{
		printf("要插入的位置[%d]是非法位置, %d 不能插入.\n", pos, x);
		return false;
	}

	for(size_t i=plist->size; i>pos; --i)
		plist->base[i] = plist->base[i-1];
	plist->base[pos] = x;
	plist->size++;

	return true;
}

bool SeqListInsertByVal(SeqList *plist, ElemType x)
{
	assert(plist != NULL);
	if(IsFull(plist) && !_Inc(plist, plist->capacity * 2))
	{
		printf("顺序表已满,%d 不能插入.\n", x);
		return false;
	}
#if 0
	size_t pos = 0;
	while(pos<plist->size && x>plist->base[pos])
		pos++;

	for(size_t i=plist->size; i>pos; --i)
		plist->base[i] = plist->base[i-1];
	plist->base[pos] = x;

	plist->size++;
#endif

	size_t end = plist->size-1;
	while(end >=0 && x<plist->base[end])
	{
		plist->base[end+1] = plist->base[end];
		end--;
	}
	plist->base[end+1] = x;
	plist->size++;
}

void SeqListEraseByPos(SeqList *plist, int pos)
{
	assert(plist != NULL);
	if(IsEmpty(plist))
	{
		printf("顺序表已空,不能在%d的位置删除数据.\n",pos);
		return;
	}
	if(pos<0 && pos>=plist->size)
	{
		printf("删除的位置非法，不能删除数据.\n");
		return;
	}

	for(size_t i=pos; i<plist->size; ++i)
		plist->base[i] = plist->base[i+1];  
	plist->size--;
}

void SeqListEraseByVal(SeqList *plist, ElemType key)
{
	assert(plist != NULL);
	int pos = SeqListFind(plist, key);
	if(pos == -1)
		return;
	SeqListEraseByPos(plist, pos);
}

void SeqListSort(SeqList *plist)
{
	assert(plist != NULL);
	for(size_t i=0; i<plist->size-1; ++i)
	{
		for(size_t j=0; j<plist->size-i-1; ++j)
		{
			if(plist->base[j] > plist->base[j+1])
				Swap(&plist->base[j], &plist->base[j+1]);
		}
	}
}

int SeqListFind(SeqList *plist, ElemType key)
{
	assert(plist != NULL);
	int pos = 0;
	while(pos<plist->size &&  key!=plist->base[pos])
		pos++;
	if(pos == plist->size)
		pos = -1;
	return pos;
}

void SeqListReverse(SeqList *plist)
{
	assert(plist != NULL);
	if(plist->size == 1)
		return;
	int start = 0, end = plist->size-1;
	while(start < end)
	{
		Swap(&plist->base[start], &plist->base[end]);
		start++;
		end--;
	}
}

ElemType SeqListFront(SeqList *plist)
{
	assert(plist != NULL);
	if(IsEmpty(plist))
	{
		printf("顺序表已空,不能取表头数据.\n");
		return;
	}
	return plist->base[0];
}
ElemType SeqListBack(SeqList *plist)
{
	assert(plist != NULL);
	if(IsEmpty(plist))
	{
		printf("顺序表已空,不能取表尾数据.\n");
		return;
	}
	return plist->base[plist->size-1];
}
int      SeqListFind_Binary(SeqList *plist,  ElemType key)
{
	assert(plist != NULL);
	if(IsEmpty(plist))
		return -1;
	int start = 0;
	int end = plist->size-1;
	int mid;
	while(start <= end)
	{
		mid = (start + end) / 2;
		if(key == plist->base[mid])
			return mid;
		else if(key < plist->base[mid])
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}
void     SeqListEraseAll(SeqList *plist, ElemType key)
{
	//????????????????
}

#endif /* _SEQLIST_H_ */
