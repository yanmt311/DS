#ifndef _STACK_H_
#define _STACK_H_

#include"Common.h"

#define STACK_DEFAULT_SIZE 8

//˳��ջ + �������ݿ���
typedef struct SeqStack
{
	ElemType *base; //ջ�ռ�
	size_t    capacity;
	int       top; //ջ��ָ��
}SeqStack;

void SeqStackInit(SeqStack *pst, int sz = STACK_DEFAULT_SIZE);
void SeqStackPush(SeqStack *pst, ElemType x);
void SeqStackPop(SeqStack *pst);
ElemType SeqStackTop(SeqStack *pst); //ȡջ��Ԫ��
void SeqStackTop(SeqStack *pst, ElemType *top_val);
void SeqStackShow(SeqStack *pst);
void SeqStackDestroy(SeqStack *pst);
int  SeqStackSize(SeqStack *pst);
//////////////////////////////////////////////////////////////

bool SeqStackIsFull(SeqStack *pst)
{
	assert(pst != NULL);
	return pst->top >= pst->capacity;
}
bool SeqStackIsEmpty(SeqStack *pst)
{
	assert(pst != NULL);
	return pst->top == 0;
}

void SeqStackInit(SeqStack *pst, int sz)
{
	assert(pst != NULL);
	pst->capacity = sz > STACK_DEFAULT_SIZE ? sz : STACK_DEFAULT_SIZE;
	pst->base = (ElemType*)malloc(sizeof(ElemType) * pst->capacity);
	pst->top = 0;
}

void SeqStackPush(SeqStack *pst, ElemType x)
{
	assert(pst != NULL);
	if(SeqStackIsFull(pst))
	{
		printf("ջ������%d ������ջ.\n", x);
		return;
	}
	pst->base[pst->top++] = x;
}

void SeqStackPop(SeqStack *pst)
{
	assert(pst != NULL);
	if(SeqStackIsEmpty(pst))
	{
		printf("ջ�ѿգ� ���ܳ�ջ.\n");
		return;
	}
	pst->top--;
}

ElemType SeqStackTop(SeqStack *pst)
{
	assert(pst != NULL);
	assert(!SeqStackIsEmpty(pst));

	return pst->base[pst->top-1];
}

void SeqStackTop(SeqStack *pst, ElemType *top_val)//��� //����
{
	assert(pst != NULL);
	if(SeqStackIsEmpty(pst))
	{
		printf("ջ�ѿգ� ����ȡջ��Ԫ��.\n");
		return;
	}

	*top_val =  pst->base[pst->top-1];
}

void SeqStackShow(SeqStack *pst)
{
	assert(pst != NULL);
	for(int i=pst->top-1; i >=0; --i)
		printf("| %d |\n", pst->base[i]);
	printf(" --  \n");
}

void SeqStackDestroy(SeqStack *pst)
{
	assert(pst != NULL);
	free(pst->base);
	pst->base = NULL;
	pst->capacity = pst->top = 0;
}

int  SeqStackSize(SeqStack *pst)
{
	assert(pst != NULL);
	return pst->top;
}

//��ջ
typedef struct LinkStackNode
{
	ElemType data;
	struct LinkStackNode *link;
}LinkStackNode;

typedef LinkStackNode* LinkStack;
void LinkStackInit(LinkStack *pst);
void LinkStackPush(LinkStack *pst, ElemType x);
void LinkStackPop(LinkStack *pst);
ElemType LinkStackTop(LinkStack *pst);
void LinkStackShow(LinkStack *pst);
int LinkStackSize(LinkStack *pst);
void LinkStackDestroy(LinkStack *pst);
/////////////////////////////////////////////////////

void LinkStackInit(LinkStack *pst)
{
	assert(pst != NULL);
	*pst = NULL;
}

void LinkStackPush(LinkStack *pst, ElemType x)
{
	assert(pst != NULL);
	LinkStackNode *node = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	assert(node != NULL);
	node->data = x;

	node->link = *pst;
	*pst = node;
}
void LinkStackPop(LinkStack *pst)
{
	assert(pst != NULL);
	if(*pst != NULL)
	{
		LinkStackNode *p = *pst;
		*pst = p->link;
		free(p);
	}
}
ElemType LinkStackTop(LinkStack *pst)
{
	assert(pst != NULL && *pst != NULL);
	return (*pst)->data;
}
void LinkStackShow(LinkStack *pst)
{
	assert(pst != NULL);
	LinkStackNode *p = *pst;
	while(p != NULL)
	{
		printf("| %d |\n", p->data);
		p = p->link;
	}
	printf(" --  \n");
}
int LinkStackSize(LinkStack *pst)
{
	assert(pst != NULL);
	int size = 0;
	LinkStackNode *p = *pst;
	while(p != NULL)
	{
		size++;
		p = p->link;
	}
	return size;
}

void LinkStackDestroy(LinkStack *pst)
{
	assert(pst != NULL);
	LinkStackNode *p = *pst;
	while(p != NULL)
	{
		*pst = p->link;
		free(p);
		p = *pst;
	}
}

#endif