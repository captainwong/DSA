#include "list.h"
#include <stdlib.h>

// ����һ��Node������ֵΪval�������´�����Node
Node* nodeCreate(int val)
{
	Node* node = (Node*)malloc(sizeof(*node));
	node->val = val;
	node->next = NULL;
	return node;
}

// ����һ��List����ʼ��������List
List* listCreate()
{
	List* l = (List*)malloc(sizeof(*l));
	l->head = l->tail = NULL;
	l->len = 0;
	return l;
}

// ɾ��һ��List��ͬʱɾ��ÿ��Node
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

// ����List�ĵ�Index���ڵ㣬�ڵ㲻�����򷵻�NULL
Node* listIndex(List* l, int index)
{
	Node* p = l ? l->head : NULL;
	if (index == 0) return p;
	while (index-- && p) {
		p = p->next;
	}
	return index == -1 ? p : NULL;
}

// ����List��ֵΪval�Ľڵ㣬���������򷵻�NULL
Node* listSearch(List* l, int val)
{
	Node* p = l->head;
	while (p) {
		if (p->val == val) { return p; }
		p = p->next;
	}
	return NULL;
}

// ��val���뵽List��β��������Node
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

// ��val���뵽List��ͷ��������Node
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

// ��val���뵽List�ĵ�Index��λ�ò�����Node����λ�ò����ڣ�����NULL
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

// ɾ��List��Head�ڵ�
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

// ɾ��List��Tail�ڵ�
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

// ɾ��List�ĵ�Index���ڵ�
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
