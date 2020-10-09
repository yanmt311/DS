#ifndef _DCLIST_H_
#define _DCLIST_H_

#include"Common.h"

//带头结点的双向循环链表
//定义节点
typedef struct DCListNode
{
	ElemType data;
	struct DCListNode *next;
	struct DCListNode *prev;
}DCListNode;

typedef DCListNode* DCList;

void DCListInit(DCList *phead);
void DCListPushBack(DCList *phead, ElemType x);
void DCListPushFront(DCList *phead, ElemType x);
void DCListShow(DCList phead);
void DCListPopBack(DCList *phead);
void DCListPopFront(DCList *phead);
size_t DCListLength(DCList *phead);
ElemType DCListFront(DCList phead);
ElemType DCListBack(DCList phead);
void DCListClear(DCList *phead);
void DCListDestroy(DCList *phead);
DCListNode* DCListFind(DCList phead, ElemType key);
void DCListEraseByVal(DCList phead, ElemType key);
void DCListSort(DCList phead);
void DCListInsertByVal(DCList phead, ElemType x);
void DCListReverse(DCList phead);
void DCListEraseAll(DCList phead, ElemType key);
/////////////////////////////////////////////////////////////////////
DCListNode* _Buynode(ElemType v = ElemType())
{
	DCListNode *_S = (DCListNode*)malloc(sizeof(DCListNode));
	assert(_S != NULL);
	_S->data = v;
	_S->next = _S->prev = _S;
	return _S;
}
void DCListInit(DCList *phead)
{
	*phead = _Buynode();
}

void DCListPushBack(DCList *phead,  ElemType x)
{
	assert(phead != NULL);
	DCListNode *s = _Buynode(x);
	DCListNode *head = *phead;

	s->prev = head->prev;
	s->next = head;
	head->prev->next = s;  //s->prev->next = s
	head->prev = s;
}

void DCListPushFront(DCList *phead, ElemType x)
{
	assert(phead != NULL);
	DCListNode *s = _Buynode(x);
	DCListNode *head = *phead;

	s->prev = head;
	s->next = head->next;
	s->prev->next = s;
	s->next->prev = s;
}

void DCListShow(DCList phead)
{
	DCListNode *p = phead->next;
	while(p != phead)
	{
		printf("%d->",p->data);
		p = p->next;
	}
	printf("Over.\n");
}

void DCListPopBack(DCList *phead)
{
	assert(phead != NULL);
	DCListNode *head = *phead;
	if(head->next == head) //判空
		return;

	DCListNode *p = head->prev; //最后一个节点
	p->prev->next = head;
	head->prev = p->prev;
	free(p);
}

void DCListPopFront(DCList *phead)
{
	assert(phead != NULL);
	DCListNode *head = *phead;
	if(head->next == head) //判空
		return;

	DCListNode *p = head->next;
	p->next->prev = p->prev;  //p->next->prev = head
	p->prev->next = p->next;  //p->prev->next = head->next
	free(p);
}

size_t DCListLength(DCList phead)
{
	assert(phead != NULL);
	DCListNode *p = phead->next;

	size_t size = 0;
	while(p != phead)
	{
		size++;
		p = p->next;
	}
	return size;
}

ElemType DCListFront(DCList phead)
{
	assert(phead != NULL);
	assert(phead->next != phead);
	return phead->next->data;
}
ElemType DCListBack(DCList phead)
{
	assert(phead != NULL);
	assert(phead->next != phead);
	return phead->prev->data;
}

void DCListClear(DCList *phead)
{
	assert(phead != NULL);
	DCListNode *p = (*phead)->next;
	while(p != *phead)
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
		p = (*phead)->next; //更新p
	}
}

void DCListDestroy(DCList *phead)
{
	assert(phead != NULL);
	DCListClear(phead);
	free(*phead);
	*phead = NULL; //预防野指针
}

DCListNode* DCListFind(DCList phead, ElemType key)
{
	assert(phead != NULL);
	DCListNode *p = phead->next;
	while(p!=phead && p->data!=key)
		p = p->next;
	if(p == phead)
		return NULL;
	return p;
}

void DCListEraseByVal(DCList phead, ElemType key)
{
	assert(phead != NULL);
	DCListNode *p = DCListFind(phead, key);
	if(p == NULL)
		return;

	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

void DCListSort(DCList phead)
{
	assert(phead != NULL);
	if(DCListLength(phead) == 1)
		return;

	DCListNode *p = phead->next;
	DCListNode *q = p->next;
	p->next = phead;
	phead->prev = p;

	while(q != phead)
	{
		p = q;
		q = q->next;

		DCListNode *tmp = phead->next;
		while(tmp!=phead && p->data>tmp->data)
			tmp = tmp->next;
		p->next = tmp;
		p->prev = tmp->prev;
		p->next->prev = p;
		p->prev->next = p;
	}
}

void DCListInsertByVal(DCList phead, ElemType x)
{
	assert(phead != NULL);
	DCListNode *p = phead->next;
	while(p!=phead && x>p->data)
		p = p->next;

	DCListNode *s = _Buynode(x);
	s->next = p;
	s->prev = p->prev;
	s->prev->next = s;
	s->next->prev = s;
}

void DCListReverse(DCList phead)
{
	assert(phead != NULL);
	if(DCListLength(phead) == 1)
		return;
	DCListNode *p = phead->next;
	DCListNode *q = p->next;
	p->next = phead;
	phead->prev = p;

	while(q != phead)
	{
		p = q;
		q = q->next;

		p->next = phead->next;
		p->prev = phead;
		p->next->prev = p;
		p->prev->next = p;
	}
}

#endif /* _DCLIST_H_ */