#ifndef _DLIST_H_
#define _DLIST_H_

#include"Common.h"

typedef struct DListNode
{
	ElemType data;
	struct DCListNode *next;
	struct DCListNode *prev;
}DListNode;

typedef DListNode* DList;

#endif /* _DLIST_H_ */