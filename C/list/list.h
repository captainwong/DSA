#ifndef __LIST_H__
#define __LIST_H__

#pragma once

typedef struct Node {
	int val;
	struct Node* next;
}Node;

typedef struct List {
	Node* head;
	Node* tail;
	int len;
}List;


#define listHead(l) ((l)->head)
// ����List��Tail
#define listTail(l) ((l)->tail)
// ����List��Length
#define listLength(l) ((l)->len)

// ����һ��Node������ֵΪval�������´�����Node
Node* nodeCreate(int val);
// ����һ��List����ʼ��������List
List* listCreate();
// ɾ��һ��List��ͬʱɾ��ÿ��Node
void listDestroy(List* l);
// ����List�ĵ�Index���ڵ㣬�ڵ㲻�����򷵻�NULL
Node* listIndex(List* l, int index);
// ����List��ֵΪval�Ľڵ㣬���������򷵻�NULL
Node* listSearch(List* l, int val);
// ��val���뵽List��β��������Node
Node* listAppend(List* l, int val);
// ��val���뵽List��ͷ��������Node
Node* listPrepend(List* l, int val);
// ��val���뵽List�ĵ�Index��λ�ò�����Node����λ�ò����ڣ�����NULL
Node* listInsert(List* l, int index, int val);
// ɾ��List��Head�ڵ�
int listRemoveHead(List* l);
// ɾ��List��Tail�ڵ�
int listRemoveTail(List* l);
// ɾ��List�ĵ�Index���ڵ�
int listRemoveIndex(List* l, int index);

#endif
