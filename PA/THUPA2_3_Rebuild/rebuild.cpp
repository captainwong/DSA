#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "bintree.h"

//int *g_preorder = NULL;
//int *g_inorder = NULL;
//int *g_pos_pre = NULL;
//int *g_pos_in = NULL;

static const int MAX_VAR = 500000;
int g_preorder[MAX_VAR];
int g_inorder[MAX_VAR];
int g_pos_pre[MAX_VAR+1];
int g_pos_in[MAX_VAR+1];
int g_postorder[MAX_VAR];

bool rebuild(/*BinTree<int>& tree, */int* preorder, int* inorder, int* postorder, int n, int& round);

int main(int /*argc*/, char** /*argv*/)
{
	int n;
	if (scanf("%d\n", &n) == EOF)
		return 0;

	/*g_preorder = new int[n];
	g_inorder = new int[n];
	g_pos_pre = new int[n + 1];
	g_pos_in = new int[n + 1];*/

	//int * postorder = new int[n];
	

	for (int i = 0; i < n; i++) {
		if (scanf("%d", &g_preorder[i]) == EOF)
			return 0;
		g_pos_pre[g_preorder[i]] = i;
	}

	for (int i = 0; i < n; i++) {
		if (scanf("%d", &g_inorder[i]) == EOF)
			return 0;
		g_pos_in[g_inorder[i]] = i;
	}

	/*if (n == 1) {
		return false;
	} else if (n == 2) {
		int p = g_preorder[0];
		int l = g_preorder[1];
		printf("%d %d\n", l, p);
		return 0;
	}*/

	//BinTree<int> tree;
	int round = 0;
	if (rebuild(g_preorder, g_inorder, g_postorder, n, round)) {
		//postorder[round] = g_preorder[0];
		for (int i = 0; i < n; i++) {
			printf("%d ", g_postorder[i]);
		}
	} else {
		printf("-1\n");
	}
	return 0;
}

bool rebuild(/*BinTree<int>& tree, */int* preorder, int* inorder, int* postorder, int n, int& round)
{
	//int p = 0;// , l = 0;
	//static int round = 0;
	
	if (n == 1) {
		postorder[round++] = preorder[0];
		return true;
	}

	//p = preorder[0];
	//l = preorder[1];
	int p_in_in = g_pos_in[preorder[0]];
	int lc_len = p_in_in - (inorder - g_inorder);
	int rc_len = n - 1 - lc_len;

	//if (lc_len < 1 || rc_len < 1) {
	//	return false;
	//}

	if (lc_len == 1 && (preorder[1] != inorder[0])) {
		return false;
	}

	//int r_in_pre = 1 + lc_len;
	//r = preorder[r_in_pre];

	//bool pass = true;
	if (lc_len > 0 && !rebuild(preorder + 1, inorder, postorder, lc_len, round)){
		return false;
	}

	if (rc_len > 0 && !rebuild(preorder + 1 + lc_len, inorder + lc_len + 1, postorder, rc_len, round)){
		return false;
	}
	//postorder[round++] = l;
	//postorder[round++] = r;
	postorder[round++] = preorder[0];

	return true;
}