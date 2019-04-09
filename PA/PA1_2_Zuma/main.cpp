#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static const int SZ = 1 << 20;
struct fastio
{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio()
	{
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}
}io;
//template <typename T>
//struct list_node
//{
//	int rank;
//	T data;
//	list_node* prev;
//	list_node* next;
//};
//
//template <typename T>
//class list
//{
//private:
//	int _size;
//	list_node* _head;
//	list_node* _tail;
//	//list_node* _v[MAX_VAR];
//public:
//	list() : _size(0), _head(NULL), _tail(NULL)
//	{
//		_head = new list_node();
//		_tail = new list_node();
//		_head->data = NULL;
//		_head->prev = NULL;
//		_head->next = _tail;
//		_tail->data = NULL;
//		_tail->prev = _head;
//		_tail->next = NULL;
//	}
//
//	~list() { clear(); }
//
//	int size() const { return _size; }
//	list_node* begin() { return _head->next; }
//	list_node* end() { return _tail; }
//
//	void clear()
//	{
//		list_node* node = _head;
//		while (node != _tail) {
//			list_node* tmp = node->next;
//			delete node;
//			node = tmp;
//		}
//		_head->next = _tail;
//		_tail->prev = _head;
//		_size = 0;
//	}
//
//	void push_back(T const& data)
//	{
//		list_node* node = new list_node();
//		node->_data = data;
//		node->prev = _tail->prev;
//		node->next = _tail;
//		_tail->prev = node;
//		_size++;
//	}
//
//	list_node* insert(int rank, T const& data)
//	{
//		list_node* node = _v[rank];
//		if (node == NULL) {
//			node = new list_node();
//			node->data = data;
//			node->prev = _head;
//			node->next = _tail;
//			for (int i = rank - 1; i > 0; i--) {
//				if (_v[i]) {
//					node->prev = _v[i];
//					_v[i]->next = node;
//					break;
//				}
//			}
//			for (int i = rank + 1; i < MAX_VAR; i++) {
//				if (_v[i]) {
//					node->next = _v[i];
//					_v[i]->prev = node;
//					break;
//				}
//			}
//		}
//	}
//
//	T remove(list_node* node)
//	{
//		list_node* prev = node->prev;
//		list_node* next = node->next;
//		delete node;
//		prev->next = next;
//		next->prev = prev;
//		_size--;
//	}
//};
//

#define MAX_VAR 10010
#define STR(a) #a

char pearls[MAX_VAR + 1] = { 0 };

static bool is_upper(char c)
{
	return c >= 'A' && c <= 'Z';
}


void print_list(List<char>& list)
{
	int size = list.size();
	if (size == 0) {
		printf("-\n");
	} else {
#ifndef _OJ_
		for (int i = 0; i < 80; i++) {
			printf("%d", i % 10);
		}
		//printf("\n");
#endif
		//int j = 0;
		ListNodePosi(char) p = list.first();
		while (p != list.last()->succ) {
			printf("%c", p->data);
			p = p->succ;
		}
		//for (int i = 0; i < size; i++, p = p->succ) {
		//	printf("%c", p->data);
		//	/*if (i < MAX_VAR) {
		//		pearls[j++] = p->data;
		//	} else {
		//		pearls[MAX_VAR] = '\0';
		//		printf("%s", pearls);
		//		j = 0;
		//	}*/
		//}
		/*if (j > 0) {
			pearls[j] = 0;
			printf("%s", pearls);
		}*/
		printf("\n");
	}
}


bool reduce(List<char>& list, ListNodePosi(char) cur)
{
	if (list.size() < 3 || cur == NULL) {
		return false;
	}

	int before = 0, after = 0;

	ListNodePosi(char) pb;
	for (pb = cur->pred; pb && (pb != list.first()->pred); pb = pb->pred) {
		if (pb->data == cur->data) {
			before++;
		} else {
			break;
		}
	}

	ListNodePosi(char) pa;
	for (pa = cur->succ; pa && (pa != list.last()->succ); pa = pa->succ) {
		if (pa->data == cur->data) {
			after++;
		} else {
			break;
		}
	}

	int total = before + after + 1;
	if (total >= 3) {
		for (int i = 0; i < total; i++) {
			//ListNodePosi(char) p = pb->succ->succ;
			list.remove(pb->succ);
			//pb = p;
		}
#ifndef _OJ_
		//printf("reducing:\n");
		//print_list(list);
#endif
		//if (pb/* && pb != list.first() && pb != list.last()*/)
		return reduce(list, pb);
		//if (pa /*&& pa != list.last()*/)
		//	reduce(list, pa);
		//return true;
	} else {
		return false;
	}
}
//
//template <typename T>
//void reduce(list<T>& l)
//{
//
//}

int main(int argc, char* argv[])
{
	
	//if (scanf("%s"STR(MAX_VAR)"s", pearls) == EOF)
	//	return 0;
	if (NULL == fgets(pearls, MAX_VAR, stdin))
		return 1;
	int length = strlen(pearls);
	List<char> l;
	for (int i = 0; i < length; i++) {
		if (is_upper(pearls[i])) {
			l.insert_as_last(pearls[i]);
		}
	}

	int n = 0;
	if (scanf("%d", &n) == EOF)
		return 1;
	/*if (n < 0 || n > MAX_VAR)
		return 0;*/

#ifndef _OJ_
	print_list(l);
#endif
	

	int K;
	char C;
	for (int i = 0; i < n; i++) {
		//if (scanf("%d %c", &K, &C) == EOF)
		//	return 0;
		scanf("%d", &K);
		do {
			scanf("%c", &C);
		} while (!is_upper(C));
		//if (K < 0 /*|| K > list.size()*/)
		//	return 0;

		ListNodePosi(char) cur = NULL;
		ListNodePosi(char) p = l.first();
		for (int j = 0; j < K; j++) {
			p = p->succ;
		}
		cur = l.insert_before(p, C);

#ifndef _OJ_
		printf("#%d (%d %c)\n", i, K, C);
		//printf("before reduce:\n");
		//print_list(list);
#endif

		reduce(l, cur);

#ifndef _OJ_
		//printf("after reduce:\n");
#endif
		print_list(l);
	}
	return 0;
}
