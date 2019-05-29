#pragma once


#include "../util/util.h"
#include "../dtl/graph_matrix.h"

namespace dtl
{
namespace test
{

template <typename Tv, typename Te>
void randomGraph(GraphMatrix<Tv, Te>& g, int n, int e, int wait_ms)
{
	while (g.n < n || g.e < e) {
		if (g.n < n) {
			if (dice(100) < 65) {
				auto vertex = static_cast<Tv>('A' + dice(26));
				printf("Inserting vertext "); print(vertex); printf(" ...");
				g.insert(vertex);
				printf("done\n");
			} else {
				if (g.n < 1) { continue; }
				int i = dice(g.n);
				printf("Removing vertex %d ...", i);
				Tv v = g.remove(i);
				printf(" done with "); print(v); printf("\n");
			}
		}

		if (1 < g.n && g.e < e) {
			if (dice(100) < 65) {
				int i = dice(g.n), j = dice(g.n);
				Te e = dice(static_cast<Te>(3 * n));
				printf("Inserting edge (%d, %d) = ", i, j); print(e); printf("...");
				if (g.exists(i, j)) {
					printf("already exists\n");
				} else {
					g.insert(e, e, i, j); printf("done\n");
				}
			} else {
				int i = dice(g.n), j = dice(g.n);
				printf("Removing edge (%d, %d) ...", i, j);
				if (g.exists(i, j)) {
					Te e = g.remove(i, j);
					printf("done with "); print(e); printf("\n");
				} else {
					printf("not exists\n");
				}
			}
		}

		print(g);
		wait(wait_ms);
	}

	wait(wait_ms);
	for (int i = 0; i < n; i++) {
		g.vertex(i) = 'A' + i;
	}
	print(g);
}

void importGraph(GraphMatrix<char, int>& g, const char* file, int wait_ms)
{
	auto f = fopen(file, "r");
	if (!f) { printf("error while opening file\n"); exit(-1); }
	int n;
	fscanf(f, "%d\n", &n);
	printf("%d vertices\n", n);

	for (int i = 0; i < n; i++) {
		char vertex;
		fscanf(f, "%c", &vertex);
		printf("Inserting vertex"); print(vertex); printf("...");
		g.insert(vertex);
		printf("done\n");
		print(g);
		wait(wait_ms);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int edge;
			fscanf(f, "%d", &edge);
			if (edge < 0) { continue; }
			printf("Inserting edge (%d, %d) = ", i, j); print(edge); printf("...");
			g.insert(edge, edge, i, j);
			printf("done\n");
			print(g);
			wait(wait_ms);
		}
	}

	fclose(f);
}

void _test(GraphMatrix<char, int>& g, int wait_ms)
{
	printf("\n"); print(g);

	printf("\n====== BFS ======\n"); g.bfs(0); print(g); wait(wait_ms);
	//printf("=== BFS (PFS)\n"); g.pfs(0, BfsPU<char, int>()); print(g);wait(wait_ms);
	printf("\n====== DFS ======\n"); g.dfs(0); print(g); wait(wait_ms);
	//printf("=== DFS (PFS)\n"); g.pfs(0, DfsPU<char, int>()); print(g);wait(wait_ms);
	printf("\n====== TopoSort ======\n"); Stack<char>* ts = g.tsort(0); print(ts); print(g); release(ts); wait(wait_ms);
	//printf("=== BCC\n"); g.bcc(0); print(g); wait(wait_ms);
	//printf("=== Prim\n"); g.prim(0); print(g); wait(wait_ms);
	//printf("=== Prim (PFS)\n"); g.pfs(0, PrimPU<char, int>()); print(g); wait(wait_ms);
	//printf("=== Dijkstra\n"); g.dijkstra(0); print(g); wait(wait_ms);
	//printf("=== Dijkstra (PFS)\n"); g.pfs(0, DijkstraPU<char, int>()); print(g); wait(wait_ms);
}

void testGraph(int n, int e, int wait_ms = WAIT_NO_WAIT)
{
	srand_time();
	GraphMatrix<char, int> g;
	randomGraph<char, int>(g, n, e, wait_ms);
	_test(g, wait_ms);
}

void testGraph(const char* file, int wait_ms = WAIT_NO_WAIT)
{
	GraphMatrix<char, int> g;
	importGraph(g, file, wait_ms);
	_test(g, wait_ms);
}

}
}
