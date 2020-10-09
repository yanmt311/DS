#ifndef _HASH_H_
#define _HASH_H_

#include"Common.h"
//Hash() 除留余数法
//冲突   链地址法

#define P 7

typedef struct HashNode
{
	ElemType data;
	struct HashNode *link;
}HashNode;

typedef HashNode* HashTable[P];

void HashInit(HashTable pht);
void HashInsert(HashTable pht, ElemType x);
HashNode* HashFind(HashTable pht, ElemType key);
void HashRemove(HashTable pht, ElemType key);
void HashShow(HashTable pht);
/////////////////////////////////////////////////////////

int Hash(ElemType key)
{
	return key % P;
}

void HashInit(HashTable pht)
{
	for(int i=0; i<P; ++i)
		pht[i] = NULL;
}

void HashInsert(HashTable pht, ElemType x)
{
	int index = Hash(x);
	HashNode *node = (HashNode*)malloc(sizeof(HashNode));
	assert(node != NULL);
	node->data = x;

	node->link = pht[index];
	pht[index] = node;
}

void HashShow(HashTable pht)
{
	for(int i=0; i<P; ++i)
	{
		printf("%d : ", i);
		HashNode *p = pht[i];
		while(p != NULL)
		{
			printf("%d->", p->data);
			p = p->link;
		}
		printf("Nil.\n");
	}
}

#endif /* _HASH_H_ */