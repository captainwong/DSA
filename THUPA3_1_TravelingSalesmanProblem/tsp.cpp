#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static const int MAX_VERTEX = 100000;
static const int MAX_EDGE = 1000000;

typedef struct _Vertex
{
	int id;
	int in_degree;
	int out_degree;
	_Vertex() : id(0), in_degree(0), out_degree(0) {}
}Vertex;

typedef struct _Edge
{
	Vertex beg;
	Vertex end;
	int weight;
	_Edge() : beg(), end(), weight(0) {}
}Edge;

Vertex g_vertex[MAX_VERTEX];
Edge g_edge[MAX_EDGE];

int main(int /*argc*/, char** /*argv*/)
{
	int n, m;
	if (scanf("%d %d\n", &n, &m) == EOF)
		return 1;

	int a, b, price;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d %d", &a, &b, &price) == EOF)
			return 1;

	}
	return 0;
}

