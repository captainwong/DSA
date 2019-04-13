#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

constexpr int MAX_VILLAGE = 1000000;

// 顶点/村庄
struct node {
	int v = -1;
	node* next = nullptr;
};

// 边/通路
struct edge {
	int in_degree = 0;
	int length = 0;

	node* first_node = nullptr;
};

node nodes[MAX_VILLAGE] = {}; int nodes_top = 0;
edge edges[MAX_VILLAGE] = {}; // 下标就是顶点
int stack[MAX_VILLAGE] = {};

inline int max(int a, int b) { return a < b ? b : a; }

int main()
{
	int n, m;
	if (scanf("%d %d\n", &n, &m) == EOF)
		return 0;

	int length = 0;

	int v1, v2;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d", &v1, &v2) == EOF)
			return 0;

		if (v1 > n || v2 > n) { return 0; }

		--v1; --v2;

		//nodes[v1].v = v1;
		//nodes[v2].v = v2;


		auto node_ = &nodes[nodes_top++];
		node_->v = v2;
		edges[v2].in_degree++;
		node_->next = edges[v1].first_node;
		edges[v1].first_node = node_;
		
	}

	int top = 0;
	for (int i = 0; i < n; i++) {
		if (edges[i].in_degree == 0) {
			stack[++top] = i;
		}
	}

	while (top) {
		int v = stack[top--];
		for (auto node = edges[v].first_node; node; node = node->next) {
			edges[node->v].length = max(edges[v].length + 1, edges[node->v].length);
			length = max(length, edges[node->v].length);
			if (--edges[node->v].in_degree == 0) {
				stack[++top] = node->v;
			}
		}
	}

	printf("%d\n", length + 1);

	return 0;
}