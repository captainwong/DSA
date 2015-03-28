#pragma once

JTL_NAMESPACE_BEGIN

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
	assert(0 <= s && s < n);
	reset();
	int clock = 0; 
	int v = s;
	do {
		if (UNDISCOVERED == status(v)) {
			BFS(v, clock);
		}
	} while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock)
{
	assert(0 <= v && v < n);
	Queue<int> q;
	status(v) = DISCOVERED;
	q.enqueue(v);
	while (!q.empty()) {
		int v = q.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u < nextNbr(v, u)) {
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED;
				q.enqueue(u);
				type(v, u) = TREE;
				parent(u) = v;
			} else {
				type(v, u) = CROSS;
			}
		}
		status(v) = VISITED;
	}
}

JTL_NAMESPACE_END
