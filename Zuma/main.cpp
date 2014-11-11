#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


#define MAX_VAR 10000
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
		int j = 0;
		ListNodePosi(char) p = list.first();
		for (int i = 0; i < size; i++, p = p->succ) {
			if (i < MAX_VAR) {
				pearls[j++] = p->data;
			} else {
				pearls[MAX_VAR] = '\0';
				printf("%s", pearls);
				j = 0;
			}
		}
		if (j > 0) {
			pearls[j] = 0;
			printf("%s", pearls);
		}
		printf("\n");
	}
}


bool reduce(List<char>& list, ListNodePosi(char) cur)
{
	if (list.size() < 3) {
		return false;
	}

	int before = 0, after = 0;

	ListNodePosi(char) pb;
	for (pb = cur; pb && (pb->pred) && (pb != list.first()); pb = pb->pred) {
		if (pb->pred->data == cur->data) {
			before++;
		} else {
			break;
		}
	}

	ListNodePosi(char) pa;
	for (pa = cur; pa && pa->succ && (pa != list.last()); pa = pa->succ) {
		if (pa->succ->data == cur->data) {
			after++;
		} else {
			break;
		}
	}

	int total = before + after + 1;
	if (total > 2) {
		for (int i = 0; i < total; i++) {
			list.remove((pb = pb->succ)->pred);
		}
#ifndef _OJ_
		//printf("reducing:\n");
		//print_list(list);
#endif
		if (pb)
			reduce(list, pb);
		return true;
	} else {
		return false;
	}
}


int main(int argc, char* argv[])
{
	
	//if (scanf("%s"STR(MAX_VAR)"s", pearls) == EOF)
	//	return 0;
	if (NULL == fgets(pearls, MAX_VAR, stdin))
		return 0;
	int length = strlen(pearls);
	List<char> list;
	if (length == 1) {
		
	} else {
		for (int i = 0; i < length-1; i++) {
			if (!is_upper(pearls[i]))
				return 0;
			list.insert_as_last(pearls[i]);
		}
	}
	int n = 0;
	if (scanf("%d", &n) == EOF)
		return 0;
	if (n < 0 || n > MAX_VAR)
		return 0;

#ifndef _OJ_
	print_list(list);
#endif
	

	int K;
	char C;
	for (int i = 0; i < n; i++) {
		//if (scanf("%d %c", &K, &C) == EOF)
		//	return 0;
		scanf("%d %c", &K, &C);
		if (!is_upper(C))
			return 0;
		if (K < 0 /*|| K > list.size()*/)
			return 0;

		ListNodePosi(char) cur = NULL;
		if (K > list.size()) {
			return 0;
			//list.insert_as_last(C);
			//cur = list.last();
		}else if (K == 0) {
			list.insert_as_first(C);
			cur = list.first();
		} else if (K == list.size()) {
			list.insert_as_last(C);
			cur = list.last();
		} else {
			ListNodePosi(char) p = list.first();
			for (int j = 0; j < K; j++) {
				p = p->succ;
			}
			cur = list.insert_before(p, C);
		}

#ifndef _OJ_
		printf("#%d (%d %c)\n", i, K, C);
		//printf("before reduce:\n");
		//print_list(list);
#endif

		reduce(list, cur);

#ifndef _OJ_
		//printf("after reduce:\n");
#endif
		print_list(list);
	}
	return 0;
}
