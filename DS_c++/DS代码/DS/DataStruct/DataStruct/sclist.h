#ifndef _SC_LIST_H_
#define _SC_LIST_H_

#include"Common.h"
typedef struct SCListNode
{
	ElemType data;
	struct SCListNode *next;
}SCListNode;

//不带头结点的单循环链表

typedef SCListNode* SCList;

void SCListInit(SCList *phead);
void SCListPushBack(SCList *phead, ElemType x);
void SCListShow(SCList phead);

void SCListPushFront(SCList *phead, ElemType x);

/*
void SListPopBack(SList *phead);
void SListPopFront(SList *phead);
void SListShow(SList *phead);
size_t SListLength(SList *phead);

SListNode* SListFind(SList phead, ElemType key);
void SListEraseByVal(SList *phead, ElemType key);
void SListInsertByVal(SList *phead, ElemType key);
void SListSort(SList *phead);

ElemType SListFront(SList phead);
ElemType SListBack(SList phead);
void SListEraseAll(SList *phead, ElemType key); //同学们先自行完成
void SListClear(SList *phead);
void SListDestroy(SList *phead);
void SListReverse(SList *phead);
*/

///////////////////////////////////////////////////////////////
void SCListInit(SCList *phead)
{
	*phead = NULL;
}

void SCListPushBack(SCList *phead, ElemType x)
{
	assert(phead != NULL);
	SCListNode *s = (SCListNode*)malloc(sizeof(SCListNode));
	assert(s != NULL);
	s->data = x;

	//节点链接
	SCListNode *p = *phead;
	if(p == NULL)
		*phead = s;
	else
	{
		while(p->next != *phead)
			p = p->next;
		p->next = s;
	}
	s->next = *phead;
}

void SCListShow(SCList phead)
{
	SCListNode *p = phead;
	if(p != NULL)
	{
		while (p->next != phead)
		{
			printf("%d->", p->data);
			p = p->next;
		}
		printf("%d->", p->data);
	}
	printf("Over.\n");
}

#endif /* _SC_LIST_H_ */