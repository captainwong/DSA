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
// 返回List的Tail
#define listTail(l) ((l)->tail)
// 返回List的Length
#define listLength(l) ((l)->len)

// 创建一个Node并赋初值为val，返回新创建的Node
Node* nodeCreate(int val);
// 创建一个List并初始化，返回List
List* listCreate();
// 删除一个List，同时删除每个Node
void listDestroy(List* l);
// 返回List的第Index个节点，节点不存在则返回NULL
Node* listIndex(List* l, int index);
// 查找List内值为val的节点，若不存在则返回NULL
Node* listSearch(List* l, int val);
// 将val插入到List的尾部并返回Node
Node* listAppend(List* l, int val);
// 将val插入到List的头部并返回Node
Node* listPrepend(List* l, int val);
// 将val插入到List的第Index个位置并返回Node，若位置不存在，返回NULL
Node* listInsert(List* l, int index, int val);
// 删除List的Head节点
int listRemoveHead(List* l);
// 删除List的Tail节点
int listRemoveTail(List* l);
// 删除List的第Index个节点
int listRemoveIndex(List* l, int index);

#endif
