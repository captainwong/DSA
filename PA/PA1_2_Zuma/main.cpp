// https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1143
/*
祖玛(Zuma)
Description
Let's play the game Zuma!

There are a sequence of beads on a track at the right beginning.All the beads are colored but no three adjacent ones are allowed to be with a same color.You can then insert beads one by one into the sequence.Once three(or more) beads with a same color become adjacent due to an insertion, they will vanish immediately.



Note that it is possible for such a case to happen for more than once for a single insertion.You can't insert the next bead until all the eliminations have been done.

Given both the initial sequence and the insertion series, you are now asked by the fans to provide a playback tool for replaying their games.In other words, the sequence of beads after all possible eliminations as a result of each insertion should be calculated.

Input
The first line gives the initial bead sequence.Namely, it is a string of capital letters from 'A' to 'Z', where different letters correspond to beads with different colors.

The second line just consists of a single interger n, i.e., the number of insertions.

The following n lines tell all the insertions in turn.Each contains an integer k and a capital letter Σ, giving the rank and the color of the next bead to be inserted respectively.Specifically, k ranges from 0 to m when there are currently m beads on the track.

Output
n lines of capital letters, i.e., the evolutionary history of the bead sequence.

Specially, "-" stands for an empty sequence.

Example
Input

ACCBA
5
1 B
0 A
2 B
4 C
0 A
Output

ABCCBA
AABCCBA
AABBCCBA
-
A
Restrictions
0 <= n <= 10 ^ 4

0 <= length of the initial sequence <= 10 ^ 4

Time: 2 sec

Memory : 256 MB

Hints
List

描述
祖玛是一款曾经风靡全球的游戏，其玩法是：在一条轨道上初始排列着若干个彩色珠子，
其中任意三个相邻的珠子不会完全同色。
此后，你可以发射珠子到轨道上并加入原有序列中。一旦有三个或更多同色的珠子变成相邻，
它们就会立即消失。这类消除现象可能会连锁式发生，其间你将暂时不能发射珠子。

开发商最近准备为玩家写一个游戏过程的回放工具。
他们已经在游戏内完成了过程记录的功能，而回放功能的实现则委托你来完成。

游戏过程的记录中，首先是轨道上初始的珠子序列，然后是玩家接下来所做的一系列操作。
你的任务是，在各次操作之后及时计算出新的珠子序列。

输入
第一行是一个由大写字母'A'~'Z'组成的字符串，表示轨道上初始的珠子序列，不同的字母表示不同的颜色。

第二行是一个数字n，表示整个回放过程共有n次操作。

接下来的n行依次对应于各次操作。每次操作由一个数字k和一个大写字母Σ描述，以空格分隔。
其中，Σ为新珠子的颜色。
若插入前共有m颗珠子，则k ∈[0, m]表示新珠子嵌入之后（尚未发生消除之前）在轨道上的位序。

输出
输出共n行，依次给出各次操作（及可能随即发生的消除现象）之后轨道上的珠子序列。

如果轨道上已没有珠子，则以“ - ”表示。

样例
见英文题面

限制
0 ≤ n ≤ 10 ^ 4

0 ≤ 初始珠子数量 ≤ 10 ^ 4

时间：2 sec

内存：256 MB

提示
列表
*/

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
