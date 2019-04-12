#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define MAX_VAL 4000000
static int preorder[MAX_VAL];
static int postorder[MAX_VAL];
static int g_position_pre[MAX_VAL + 1];
static int g_position_post[MAX_VAL + 1];

void parseSubTree(int p, int* preorder, int *postorder, int n);

int main()
{
	int n;
	if (scanf("%d\n", &n) == EOF)
		return 0;

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
	
	parseSubTree(l, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);

	printf("%d ", p);

	parseSubTree(r, preorder + rpos_in_pre, postorder + 1 + lpos_in_post, rpos_in_post - lpos_in_post);

	return 0;
}

void parseSubTree(int p, int* preorder, int *postorder, int n)
{
	if (n <= 2) {
		printf("%d ", p);
		return;
	}

	int l = preorder[1];
	int r = postorder[n - 2];
	int lpos_in_pre = g_position_pre[l];
	int rpos_in_pre = g_position_pre[r];
	int lpos_in_post = g_position_post[l];
	int rpos_in_post = g_position_post[r];

	parseSubTree(l, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);

	printf("%d ", p);

	parseSubTree(r, preorder + 1 + rpos_in_pre - lpos_in_pre,
				 postorder + rpos_in_pre - lpos_in_pre,
				 rpos_in_post - lpos_in_post);

}

