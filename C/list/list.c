#ifdef _MSC_VER // 当前编译器是否为 Visual Studio
#define _CRT_SECURE_NO_WARNINGS // 只有在 Visual Studio 下才需要定义此宏
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define myassert(exp) printf("testing %d %s\n", __LINE__, #exp); if(!(exp)) { printf("ERROR! %d %s\n", __LINE__, #exp); exit(1); }



typedef struct Node {
	int val;
	struct Node* next;
}Node;

typedef struct List {
	Node* head;
	Node* tail;
	int len;
}List;

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

// 返回List的Head
Node* listHead(List* l)
{
	return l ? l->head : NULL;
}

// 返回List的Tail
Node* listTail(List* l)
{
	return l ? l->tail : NULL;
}

// 返回List的Length
int listLength(List* l)
{
	return l ? l->len : 0;
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
	if (!l) { return NULL; }
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
	if (!l) return NULL;
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
	if (!l) return NULL;
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
void listRemoveHead(List* l) {
	if (!l) return;
	Node* p = l->head;
	if (p) {
		if (p->next) {
			l->head = p->next;
		} else {
			l->head = l->tail = NULL;
		}
		l->len--;
		free(p);
	}
}

// 删除List的Tail节点
void listRemoveTail(List* l) {
	if (!l) return;
	if (l->len == 0) { return; }
	if (l->len == 1) {
		free(l->tail);
		l->head = l->tail = NULL;
		l->len = 0;
		return;
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
}

// 删除List的第Index个节点
void listRemoveIndex(List* l, int index)
{
	if (!l || !l->head || l->len <= index) { return; }
	if (index == 0) {
		listRemoveHead(l);
		return;
	}
	if (index == l->len - 1) {
		listRemoveTail(l);
		return;
	}
	Node* p = l->head;
	while (p && --index) {
		p = p->next;
	}
	Node* q = p->next;
	p->next = q->next;
	l->len--;
	free(q);
}

void listPrintAllItem(List* l)
{
	Node* p = l ? l->head : NULL;
	printf("[");
	while (p) {
		if (p == l->head) {
			printf("%d", p->val);
		} else {
			printf(", %d", p->val);
		}
		p = p->next;
	}
	printf("]");
}

char* list2string(List* l)
{
	char* s = (char*)malloc(16);
	int capacity = 16;
	int len = 0;
	s[len++] = '[';
	s[len] = '\0';
	
	Node* p = l ? l->head : NULL;	
	while (p) {
		char tmp[16];
		int n = sprintf(tmp, "%s%d", p == l->head ? "" : ", ", p->val);
		if (capacity - len < n + 1) {
			capacity <<= 1;
			s = (char*)realloc(s, capacity);
		}
		strcat(s, tmp);
		len += n;
		p = p->next;
	}

	if (capacity != len + 2) {
		s = (char*)realloc(s, len + 2);
	}
	s[len++] = ']';
	s[len++] = '\0';
	return s;
}

void test()
{
	List* l = listCreate();
	myassert(l->head == l->tail && l->head == NULL && l->len == 0);

	char* s = list2string(l);
	myassert(strcmp(s, "[]") == 0);
	free(s);

	listAppend(l, 1);
	myassert(l->len == 1);
	myassert(l->head == l->tail && l->head && l->head->val == 1);
	myassert(listIndex(l, 0) && listIndex(l, 0)->val == 1);
	myassert(!listIndex(l, 1));

	listAppend(l, 2);
	myassert(l->len == 2);
	myassert(l->head && l->head->val == 1 && l->tail && l->tail->val == 2);

	listAppend(l, 3);
	listAppend(l, 4);
	listAppend(l, 5);
	myassert(l->len == 5);
	myassert(listHead(l) && listHead(l)->val == 1);
	myassert(listTail(l) && listTail(l)->val == 5);
	for (int i = 0; i < 5; i++) {
		myassert(listIndex(l, i)->val == i + 1);
	}
	for (int i = 0; i < 5; i++) {
		Node* p = listSearch(l, i + 1);
		myassert(p && p->val == (i + 1));
	}
	s = list2string(l);
	myassert(strcmp(s, "[1, 2, 3, 4, 5]") == 0);
	free(s);

	listDestroy(l);


	l = listCreate();
	listPrepend(l, 1);
	myassert(l->len == 1);
	myassert(l->head == l->tail && l->head && l->head->val == 1);

	listPrepend(l, 2);
	myassert(l->len == 2);
	myassert(l->head && l->head->val == 2 && l->tail && l->tail->val == 1);

	listPrepend(l, 3);
	listPrepend(l, 4);
	listPrepend(l, 5);
	myassert(l->len == 5);
	myassert(listHead(l) && listHead(l)->val == 5);
	myassert(listTail(l) && listTail(l)->val == 1);
	for (int i = 0; i < 5; i++) {
		myassert(listIndex(l, i)->val == 5 - i);
	}
	for (int i = 0; i < 5; i++) {
		Node* p = listSearch(l, i + 1);
		myassert(p && p->val == (i + 1));
	}
	s = list2string(l);
	myassert(strcmp(s, "[5, 4, 3, 2, 1]") == 0);
	free(s);

	listDestroy(l);


	l = listCreate();
	listInsert(l, 0, 1);
	myassert(l->len == 1);
	myassert(l->head == l->tail && l->head && l->head->val == 1);
	listInsert(l, 0, 2);
	myassert(l->len == 2);
	myassert(l->head && l->head->val == 2 && l->tail && l->tail->val == 1);
	listInsert(l, 2, 3);
	myassert(l->len == 3);
	myassert(l->head && l->head->val == 2 && l->tail && l->tail->val == 3);
	s = list2string(l);
	myassert(strcmp(s, "[2, 1, 3]") == 0);
	free(s);
	listInsert(l, 3, 4);
	s = list2string(l);
	myassert(strcmp(s, "[2, 1, 3, 4]") == 0);
	free(s);
	listInsert(l, 0, 5);
	s = list2string(l);
	myassert(strcmp(s, "[5, 2, 1, 3, 4]") == 0);
	free(s);
	listInsert(l, 4, 6);
	s = list2string(l);
	myassert(strcmp(s, "[5, 2, 1, 3, 6, 4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[2, 1, 3, 6, 4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[1, 3, 6, 4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[3, 6, 4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[6, 4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[4]") == 0);
	free(s);
	listRemoveHead(l);
	s = list2string(l);
	myassert(strcmp(s, "[]") == 0);
	free(s);

	listDestroy(l);


	l = listCreate();
	for (int i = 1; i <= 5; i++) {
		listAppend(l, i);
	}
	listRemoveTail(l);
	s = list2string(l);
	myassert(strcmp(s, "[1, 2, 3, 4]") == 0);
	free(s);

	listRemoveTail(l);
	s = list2string(l);
	myassert(strcmp(s, "[1, 2, 3]") == 0);
	free(s);
	listRemoveTail(l);
	s = list2string(l);
	myassert(strcmp(s, "[1, 2]") == 0);
	free(s);
	listRemoveTail(l);
	s = list2string(l);
	myassert(strcmp(s, "[1]") == 0);
	free(s);
	listRemoveTail(l);
	s = list2string(l);
	myassert(strcmp(s, "[]") == 0);
	free(s);
	listDestroy(l);


	l = listCreate();
	for (int i = 1; i <= 5; i++) {
		listAppend(l, i);
	}
	listRemoveIndex(l, 0);
	s = list2string(l);
	myassert(strcmp(s, "[2, 3, 4, 5]") == 0);
	free(s);
	listRemoveIndex(l, 4);
	s = list2string(l);
	myassert(strcmp(s, "[2, 3, 4, 5]") == 0);
	free(s);
	listRemoveIndex(l, 3);
	s = list2string(l);
	myassert(strcmp(s, "[2, 3, 4]") == 0);
	free(s);
	listRemoveIndex(l, 1);
	s = list2string(l);
	myassert(strcmp(s, "[2, 4]") == 0);
	free(s);
	listRemoveIndex(l, 1);
	s = list2string(l);
	myassert(strcmp(s, "[2]") == 0);
	free(s);
	listRemoveIndex(l, 1);
	s = list2string(l);
	myassert(strcmp(s, "[2]") == 0);
	free(s);
	listRemoveIndex(l, 0);
	s = list2string(l);
	myassert(strcmp(s, "[]") == 0);
	free(s);

	printf("ALL TESTCASE PASSED!\n");
}


int main()
{
	myassert(1 == 1);
	test();
}
