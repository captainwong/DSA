/*
https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1146

��������ع�(Proper Rebuild)
Description
In general, given the preorder traversal sequence and postorder traversal sequence of a binary tree, we cannot determine the binary tree.


https://dsa.cs.tsinghua.edu.cn/oj/attachment/7c7a/7c7a319cffe20865fa728afcdfccbccac25eeb46.png
Figure 1

In Figure 1 for example, although they are two different binary tree, their preorder traversal sequence and postorder traversal sequence are both of the same.

But for one proper binary tree, in which each internal node has two sons, we can uniquely determine it through its given preorder traversal sequence and postorder traversal sequence.

Label n nodes in one binary tree using the integers in [1, n], we would like to output the inorder traversal sequence of a binary tree through its preorder and postorder traversal sequence.

Input
The 1st line is an integer n, i.e., the number of nodes in one given binary tree,

The 2nd and 3rd lines are the given preorder and postorder traversal sequence respectively.

Output
The inorder traversal sequence of the given binary tree in one line.

Example
Input

5
1 2 4 5 3
4 5 2 3 1
Output

4 2 5 1 3
Restrictions
For 95% of the estimation, 1 <= n <= 1,000,00

For 100% of the estimation, 1 <= n <= 4,000,000

The input sequence is a permutation of {1,2...n}, corresponding to a legal binary tree.

Time: 2 sec

Memory: 256 MB

Hints

https://dsa.cs.tsinghua.edu.cn/oj/attachment/047a/047a8ca961ff072a77e1429242c82031dc92851f.png
Figure 2

In Figure 2, observe the positions of the left and right children in preorder and postorder traversal sequence.

����
һ����˵������������������������кͺ���������У�������ȷ��Ψһȷ���ö�������



��ͼһ��

����ͼһ�е����ö���������Ȼ�����ǲ�ͬ���������������ǵ����򡢺���������ж�����ͬ�ġ�

���Ƕ��ڡ������������ÿ���ڲ��ڵ㶼���������ӵĶ��������������������򡢺����������������ȫȷ�����Ľṹ��

����������n���ڵ���[1, n]�ڵ��������б�ţ�����һ��������������򡢺���������У��������������������С�

����
��һ��Ϊһ������n�����������нڵ�ĸ�����

�ڶ�������Ϊ��֪�����򡢺���������С�

���
��һ�У������������������������С�

����
��Ӣ������

����
����95%�Ĳ�����1 �� n �� 1,000,000

����100%�Ĳ�����1 �� n �� 4,000,000

�����������{1,2...n}�����У��Ҷ�Ӧ��һ�úϷ����������

ʱ�䣺2 sec

�ռ䣺256 MB

��ʾ


�۲����Һ��������򡢺�����������е�λ��

������Ƶ05e5-3
*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "bintree.h"


struct fastio
{
	static const int SZ = 1 << 18;
	char inbuf[SZ];
	char outbuf[SZ];
	fastio()
	{
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}
}io;

#if (_MSC_VER  >= 1800)
template <typename T>
T max(T const& a, T const& b)
{
	return a > b ? a : b;
}
#endif

#define MAX_VAL 4000000
int preorder[MAX_VAL] = { 0 };
int postorder[MAX_VAL] = { 0 };
int g_position_pre[MAX_VAL+1] = { 0 };
int g_position_post[MAX_VAL+1] = { 0 };

int g_print_index = 0;

#define USE_BUFF

#ifdef USE_BUFF
char g_buff[1024 * 1024 * 32] = { 0 };
char g_tmp[32] = { 0 };
int g_bf_pos = 0;
#endif

void visit(int data)
{
#ifdef USE_BUFF
	int len = sprintf(g_tmp, "%d ", data) + 1;
	//strcat(g_buff, g_tmp);
	memcpy(g_buff + g_bf_pos, g_tmp,len );
	g_bf_pos += len;
#else
	printf("%d ", data);
#endif
}



void parseSubTree(BinTree<int>& bintree, BinNodePosi(int) pos, 
				  int* preorder, int *postorder, int n)
{
	if (n <= 2)
		return;

	int l = preorder[1];
	int r = postorder[n - 2];
	int lpos_in_pre = g_position_pre[l];
	int rpos_in_pre = g_position_pre[r];
	int lpos_in_post = g_position_post[l];
	int rpos_in_post = g_position_post[r];
	BinNodePosi(int) lpos = bintree.insertAsLC(pos, l);
	BinNodePosi(int) rpos = bintree.insertAsRC(pos, r);
	parseSubTree(bintree, lpos, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);
	parseSubTree(bintree, rpos, 
				 preorder + 1 + rpos_in_pre - lpos_in_pre, 
				 postorder + rpos_in_pre - lpos_in_pre, 
				 rpos_in_post - lpos_in_post);

	/*while (n > 2) {
		int l = preorder[1];
		int r = postorder[n - 2];
		int lpos_in_pre = g_position_pre[l];
		int rpos_in_pre = g_position_pre[r];
		int lpos_in_post = g_position_post[l];
		int rpos_in_post = g_position_post[r];
		BinNodePosi(int) lpos = bintree.insertAsLC(pos, l);
		BinNodePosi(int) rpos = bintree.insertAsRC(pos, r);
	}*/
}

int main(int /*argc*/, char** /*argv*/)
{
#ifdef _DEBUG_
	BinTree<int> tree;
	BinNodePosi(int) pp = tree.insertAsRoot(1);
	BinNodePosi(int) pl = tree.insertAsLC(pp, 2);
	BinNodePosi(int) pr = tree.insertAsRC(pp, 3);
	tree.insertAsLC(pr, 4);
	BinNodePosi(int) prp = tree.insertAsRC(pr, 5);
	tree.insertAsLC(prp, 6);
	tree.insertAsRC(prp, 7);
	tree.travPre(print);
	printf("\n");
	tree.travPost(print);
	printf("\n");
	tree.travIn(print);
	printf("\n");
	return 0;
#endif

	int n;
	if (scanf("%d\n", &n) == EOF)
		return 0;

	//int *preorder = new int[n];
	//int *postorder = new int[n];
	//g_position_pre = new int[n + 1];
	//g_position_post = new int[n + 1];
	for (int i = 0; i < n; i++) {
		if (scanf("%d\n", &preorder[i]) == EOF)
			return 0;
		g_position_pre[preorder[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		if (scanf("%d\n", &postorder[i]) == EOF)
			return 0;
		g_position_post[postorder[i]] = i;
	}

	if (n == 0) {
		return 0;
	} else if (n == 1) {
		printf("%d\n", preorder[0]);
		return 0;
	} else if (n == 2) {
		printf("%d %d\n", preorder[0], preorder[1]);
		return 0;
	}

	int p, l, r;
	p = preorder[0];
	l = preorder[1];
	r = postorder[n - 2];
	int lpos_in_pre = g_position_pre[l];
	int rpos_in_pre = g_position_pre[r];
	int lpos_in_post = g_position_post[l];
	int rpos_in_post = g_position_post[r];
	BinTree<int> bintree;
	BinNodePosi(int) pos = bintree.insertAsRoot(p);
	BinNodePosi(int) lpos = bintree.insertAsLC(pos, l);
	BinNodePosi(int) rpos = bintree.insertAsRC(pos, r);
	parseSubTree(bintree, lpos, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);
	parseSubTree(bintree, rpos, preorder + rpos_in_pre, postorder + 1 + lpos_in_post, rpos_in_post - lpos_in_post);

	bintree.travIn(visit);
#ifdef USE_BUFF
	// printf(g_buff);
	//printf("\n");
#endif
	//for (int i = 0; i < g_print_index; i++) {
	//	printf("%d ", g_position_pre[i]);
	//}
	return 0;
}
