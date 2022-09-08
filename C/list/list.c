#include "list.h"
#include <stdlib.h>

// 创建一个Node并赋初值为val，返回新创建的Node
Node* nodeCreate(int val)
{
	Node* node = (Node*)malloc(sizeof(*node));
	node->val = val;
	node->next = NULL;
	return node;
}

// 创建一个List并初始化，返回List
List* listCreate()
{
	List* l = (List*)malloc(sizeof(*l));
	l->head = l->tail = NULL;
	l->len = 0;
	return l;
}

// 删除一个List，同时删除每个Node
void listDestroy(List* l)
{
	if (!l) return;
	Node* p = l->head;
	while (p) {
		Node* q = p->next;
		free(p);
		p = q;
	}
	free(l);
}

// 返回List的第Index个节点，节点不存在则返回NULL
Node* listIndex(List* l, int index)
{
	Node* p = l ? l->head : NULL;
	if (index == 0) return p;
	while (index-- && p) {
		p = p->next;
	}
	return index == -1 ? p : NULL;
}

// 查找List内值为val的节点，若不存在则返回NULL
Node* listSearch(List* l, int val)
{
	Node* p = l->head;
	while (p) {
		if (p->val == val) { return p; }
		p = p->next;
	}
	return NULL;
}

// 将val插入到List的尾部并返回Node
Node* listAppend(List* l, int val)
{
	Node* p = nodeCreate(val);
	if (l->tail) {
		l->tail->next = p;
		l->tail = p;
	} else {
		l->head = l->tail = p;
	}
	l->len++;
	return p;
}

// 将val插入到List的头部并返回Node
Node* listPrepend(List* l, int val)
{
	Node* p = nodeCreate(val);
	if (l->head) {
		p->next = l->head;
		l->head = p;
	} else {
		l->head = l->tail = p;
	}
	l->len++;
	return p;
}

// 将val插入到List的第Index个位置并返回Node，若位置不存在，返回NULL
Node* listInsert(List* l, int index, int val)
{
	if (index == 0) {
		return listPrepend(l, val);
	} else if (index == l->len) {
		return listAppend(l, val);
	}
	Node* p = listIndex(l, index - 1);
	if (!p) return NULL;
	Node* q = nodeCreate(val);
	q->next = p->next;
	p->next = q;
	l->len++;
	return q;
}

// 删除List的Head节点
int listRemoveHead(List* l) {
	Node* p = l->head;
	if (p->next) {
		l->head = p->next;
	} else {
		l->head = l->tail = NULL;
	}
	l->len--;
	int val = p->val;
	free(p);
	return val;
}

// 删除List的Tail节点
int listRemoveTail(List* l) {
	int val = l->tail->val;
	if (l->len == 1) {
		free(l->tail);
		l->head = l->tail = NULL;
		l->len = 0;
		return val;
	}

	Node* p = l->head;
	while (p) {
		if (p->next == l->tail) {
			break;
		}
		p = p->next;
	}
	p->next = NULL;
	free(l->tail);
	l->len--;
	l->tail = p;
	return val;
}

// 删除List的第Index个节点
int listRemoveIndex(List* l, int index)
{
	if (index == 0) {
		return listRemoveHead(l);
	}
	if (index == l->len - 1) {
		return listRemoveTail(l);
	}
	Node* p = l->head;
	while (p && --index) {
		p = p->next;
	}
	Node* q = p->next;
	p->next = q->next;
	l->len--;
	int val = q->val;
	free(q);
	return val;
}
