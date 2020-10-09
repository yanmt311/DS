#ifndef  _QUEUE_H_
#define  _QUEUE_H_

#include"Common.h"

//链式队列
typedef struct LinkQueueNode
{
	ElemType data;
	struct LinkQueueNode *link;
}LinkQueueNode;

typedef struct LinkQueue
{
	LinkQueueNode *head; // 队头指针
	LinkQueueNode *tail; // 队尾指针
}LinkQueue;

void LinkQueueInit(LinkQueue *pq);
void LinkQueueEn(LinkQueue *pq, ElemType x);
void LinkQueueDe(LinkQueue *pq);
ElemType LinkQueueFront(LinkQueue *pq);
int LinkQueueSize(LinkQueue *pq);
bool LinkQueueEmpty(LinkQueue *pq);
void LinkQueueShow(LinkQueue *pq);
void LinkQueueDestroy(LinkQueue *pq);
/////////////////////////////////////////////////////
void LinkQueueInit(LinkQueue *pq)
{
	assert(pq != NULL);
	pq->head = pq->tail = NULL;
}

void LinkQueueEn(LinkQueue *pq, ElemType x)
{
	assert(pq != NULL);
	LinkQueueNode *node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	assert(node != NULL);
	node->data = x;
	node->link = NULL;
	if(pq->head == NULL)
		pq->head = pq->tail = node;
	else
	{
		pq->tail->link = node;
		pq->tail = node;
	}
}
void LinkQueueDe(LinkQueue *pq)
{
	assert(pq != NULL);
	if(pq->head != NULL)
	{
		LinkQueueNode *p = pq->head;
		if(pq->head == pq->tail)
			pq->head = pq->tail = NULL;
		else
			pq->head = p->link;
		free(p);
	}
}
ElemType LinkQueueFront(LinkQueue *pq)
{
	assert(pq != NULL);
	assert(pq->head != NULL);
	return pq->head->data;  //return pq->tail->data
}
int LinkQueueSize(LinkQueue *pq)
{
	assert(pq != NULL);
	int size = 0;
	LinkQueueNode *p = pq->head;
	while(p != NULL)
	{
		size++;
		p = p->link;
	}
	return size;
}
bool LinkQueueEmpty(LinkQueue *pq)
{
	assert(pq != NULL);
	return pq->head == NULL;
}

void LinkQueueShow(LinkQueue *pq)
{
	assert(pq != NULL);
	LinkQueueNode *p = pq->head;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->link;
	}
	printf("\n");
}

void LinkQueueDestroy(LinkQueue *pq)
{
	assert(pq != NULL);
	LinkQueueNode *p = pq->head;
	while(p != NULL)
	{
		pq->head = p->link;
		free(p);
		p = pq->head;
	}
}

//顺序队列

#define QUEUE_DEFAULT_SIZE 8

typedef struct SeqQueue
{
	ElemType *base;
	int       capacity;
	int       front;
	int       rear;
}SeqQueue;

void SeqQueueInit(SeqQueue *psq, int sz = QUEUE_DEFAULT_SIZE);
void SeqQueueEn(SeqQueue *psq, ElemType x);
void SeqQueueDe(SeqQueue *psq);
ElemType SeqQueueFront(SeqQueue *psq);
int SeqQueueSize(SeqQueue *psq);
bool SeqQueueEmpty(SeqQueue *psq);
void SeqQueueShow(SeqQueue *psq);
void SeqQueueDestroy(SeqQueue *psq);
//////////////////////////////////////////////////
void SeqQueueInit(SeqQueue *psq, int sz)
{
	assert(psq != NULL);
	psq->capacity = sz > QUEUE_DEFAULT_SIZE ? sz : QUEUE_DEFAULT_SIZE;
	psq->base = (ElemType*)malloc(sizeof(ElemType) * psq->capacity);
	psq->front = psq->rear = 0;
}

void SeqQueueEn(SeqQueue *psq, ElemType x)
{
	assert(psq != NULL);
	if(psq->rear >= psq->capacity)
	{
		printf("队列已满，%d 不能入队.\n", x);
		return;
	}
	psq->base[psq->rear++] = x;
}
void SeqQueueDe(SeqQueue *psq)
{
	assert(psq != NULL);
	if(SeqQueueEmpty(psq))
	{
		printf("队列已空， 不能出队.\n");
		return;
	}
	psq->front++;
}
ElemType SeqQueueFront(SeqQueue *psq)
{
	assert(psq != NULL);
	assert(!SeqQueueEmpty(psq));
	return psq->base[psq->front];
}
int SeqQueueSize(SeqQueue *psq)
{
	assert(psq != NULL);
	return (psq->rear - psq->front);
}
bool SeqQueueEmpty(SeqQueue *psq)
{
	assert(psq != NULL);
	return psq->front == psq->rear;
}
void SeqQueueShow(SeqQueue *psq)
{
	assert(psq != NULL);
	for(int i=psq->front; i<psq->rear; ++i)
		printf("%d ",psq->base[i]);
	printf("\n");
}
void SeqQueueDestroy(SeqQueue *psq)
{
	assert(psq != NULL);
	free(psq->base);
	psq->base = NULL;
	psq->capacity = psq->front = psq->rear = 0;
}

//循环队列
typedef struct CycleSeqQueue
{
	ElemType *base;
	int       capacity;
	int       front;
	int       rear;
}CycleSeqQueue;

void CycleSeqQueueInit(CycleSeqQueue *pcq, int sz = QUEUE_DEFAULT_SIZE);
void CycleSeqQueueEn(CycleSeqQueue *pcq, ElemType x);
void CycleSeqQueueDe(CycleSeqQueue *pcq);
ElemType CycleSeqQueueFront(CycleSeqQueue *psq);
int CycleSeqQueueSize(CycleSeqQueue *psq);
bool CycleSeqQueueEmpty(CycleSeqQueue *psq);
void CycleSeqQueueShow(CycleSeqQueue *psq);
void CycleSeqQueueDestroy(CycleSeqQueue *psq);
/////////////////////////////////////////////////////////
bool IsFull(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return ((pcq->rear+1)%(pcq->capacity+1)) == pcq->front;
}
bool IsEmpty(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return pcq->front == pcq->rear;
}
void CycleSeqQueueInit(CycleSeqQueue *pcq, int sz)
{
	assert(pcq != NULL);
	pcq->capacity = sz > QUEUE_DEFAULT_SIZE ? sz : QUEUE_DEFAULT_SIZE;
	pcq->base = (ElemType*)malloc(sizeof(ElemType) * (pcq->capacity + 1));
	pcq->front = pcq->rear = 0;
}

void CycleSeqQueueEn(CycleSeqQueue *pcq, ElemType x)
{
	assert(pcq != NULL);
	if(IsFull(pcq))
	{
		printf("队列已满， %d 不能入队.\n", x);
		return;
	}
	pcq->base[pcq->rear] = x;
	pcq->rear = (pcq->rear+1) % (pcq->capacity+1);
}

void CycleSeqQueueDe(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	if(IsEmpty(pcq))
	{
		printf("队列以空, 不能出队.\n");
		return;
	}

	pcq->front = (pcq->front+1) % (pcq->capacity+1);
}

ElemType CycleSeqQueueFront(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	assert(!IsEmpty(pcq));
	return pcq->base[pcq->front];
}
int CycleSeqQueueSize(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	int size = 0;
	for(int i=pcq->front; i!=pcq->rear;)
	{
		size++;
		i = (i+1) %(pcq->capacity+1);
	}
	return size;
}
bool CycleSeqQueueEmpty(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	return IsEmpty(pcq);
}
void CycleSeqQueueShow(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	for(int i=pcq->front; i!=pcq->rear;)
	{
		printf("%d ", pcq->base[i]);
		i = (i+1) %(pcq->capacity+1);
	}
	printf("\n");
}
void CycleSeqQueueDestroy(CycleSeqQueue *pcq)
{
	assert(pcq != NULL);
	free(pcq->base);
	pcq->base = NULL;
	pcq->capacity = pcq->front = pcq->rear = 0;
}

#endif /* _QUEUE_H_ */