#ifdef _MSC_VER // 当前编译器是否为 Visual Studio
#define _CRT_SECURE_NO_WARNINGS // 只有在 Visual Studio 下才需要定义此宏
#endif
#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define myassert(exp) printf("testing %d %s\n", __LINE__, #exp); if(!(exp)) { printf("ERROR! %d %s\n", __LINE__, #exp); exit(1); }



void listPrintAllItem(List * l)
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

char* list2string(List * l)
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
