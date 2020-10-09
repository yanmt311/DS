#ifndef _SLIST_H_
#define _SLIST_H_

#include"Common.h"
typedef struct SListNode
{
	ElemType data;
	struct SListNode *next;
}SListNode;

//不带头结点的单链表
typedef SListNode* SList;


void SListInit(SList *phead);
bool SListEmpty(SList *phead);
void SListPushBack(SList *phead, ElemType x);
void SListPushFront(SList *phead, ElemType x);
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
/////////////////////////////////////////////////////////////////////

void SListInit(SList *phead)
{
	assert(phead != NULL);
	*phead = NULL;
}

bool SListEmpty(SList *phead)
{
	return *phead == NULL;
}

void SListPushBack(SList *phead, ElemType x)
{
	assert(phead != NULL);
	SListNode *s = (SListNode *)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;

	//链接节点
	SListNode *p = *phead;
	if(p == NULL)  //插入的节点为第一个节点
		*phead = s;
	else
	{
		while(p->next != NULL)
			p = p->next;
		p->next = s;
	}
}

void SListPushFront(SList *phead, ElemType x)
{
	assert(phead != NULL);
	SListNode *s = (SListNode *)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = x;

	//链接节点
	s->next = *phead;
	*phead = s;
}

void SListPopBack(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	SListNode *prev = NULL;

	if(p != NULL)
	{
		while (p->next != NULL)
		{
			prev = p;
			p = p->next;
		}

		//需要考虑释放的节点是否为最后一个节点
		if(prev == NULL)
			*phead = NULL;
		else
			prev->next = NULL;
		free(p);
	}
}
void SListPopFront(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	if(p != NULL)
	{
		*phead = p->next;
		free(p);
	}
}

void SListShow(SList phead)
{
	//assert(phead != NULL);
	SListNode *p = phead;
	while(p != NULL)
	{
		printf("%d->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

size_t SListLength(SList phead)
{
	//assert(phead != NULL);
	size_t size = 0;
	SListNode *p = phead;
	while(p != NULL)
	{
		size++;
		p = p->next;
	}
	return size;
}

SListNode* SListFind(SList phead, ElemType key)
{
#if 0
	SListNode *p = phead;
	while(p != NULL)
	{
		if(p->data == key)
			return p;
		p = p->next;
	}
	return NULL;
#endif

	SListNode *p = phead;
	while(p!=NULL && p->data!=key)
		p = p->next;
	return p;
}

void SListEraseByVal(SList *phead, ElemType key)
{
#if 0
	assert(phead != NULL);
	SListNode *p = SListFind(*phead, key);
	if(p == NULL)
		return;

	if(p->next == NULL) //删除的是末尾节点
		SListPopBack(phead);
	else
	{
		SListNode *q = p->next;
		p->data = q->data;
		p->next = q->next;
		free(q);
	}
#endif

	assert(phead != NULL);
	SListNode *p = SListFind(*phead, key);
	if(p == NULL)
		return;

	SListNode *prev = *phead;
	while(prev!=p && prev->next!=p)
		prev = prev->next;
	if(prev == p)
		*phead = p->next;
	else
		prev->next = p->next;
	free(p);
}

void SListInsertByVal(SList *phead, ElemType key)
{
	assert(phead != NULL);
	SListNode *p = *phead, *prev = NULL;
	while(p!=NULL && key>p->data)
	{
		prev = p;
		p = p->next;
	}

	SListNode *s = (SListNode*)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = key;

	if(prev == NULL)
	{
		s->next = *phead;
		*phead = s;
	}
	else
	{
		s->next = prev->next;
		prev->next = s;
	}
}

void SListSort(SList *phead)
{
	assert(phead != NULL);
	if(SListLength(*phead) <= 1)
		return;

	SListNode *tmp = *phead, *prev=NULL;
	SListNode *p = *phead;
	SListNode *q = p->next;
	p->next = NULL;

	while(q != NULL)
	{
		p = q;
		q = q->next;

		//寻找插入的位置
		while(tmp!=NULL && p->data>tmp->data)
		{
			prev = tmp;
			tmp = tmp->next;
		}

		if(prev == NULL)
		{
			p->next = *phead;
			*phead = p;
		}
		else
		{
			p->next = prev->next;
			prev->next = p;
		}

		tmp = *phead;
		prev = NULL;
	}
}

ElemType SListFront(SList phead)
{
	assert(phead != NULL);
	return phead->data;
}
ElemType SListBack(SList phead)
{
	assert(phead != NULL);
	SListNode *p = phead;
	while(p->next != NULL)
		p = p->next;
	return p->data;
}
void SListEraseAll(SList *phead, ElemType key) //同学们先自行完成
{}

void SListClear(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = NULL;
	while(*phead != NULL)
	{
		p = *phead;
		*phead = p->next;
		free(p);
	}
}

void SListDestroy(SList *phead)
{
	SListClear(phead);
}

void SListReverse(SList *phead)
{
	assert(phead != NULL);
	SListNode *p = *phead;
	SListNode *q = p->next;

	p->next = NULL;
	while(q != NULL)
	{
		p = q;
		q = q->next;
		p->next = *phead;
		*phead = p;
	}
}

#endif /* _SLIST_H_ */