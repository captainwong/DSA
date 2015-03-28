#pragma once

JTL_NAMESPACE_BEGIN

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{
	assert(0 <= s && s < n);
	reset();
	int clock = 0;
	int v = s;
	do {
		if (UNDISCOVERED == status(v)) {
			DFS(v, clock);
		}
	} while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
	assert(0 <= v && v < n);
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u)) {
			case UNDISCOVERED:
				type(v, u) = TREE;
				parent(u) = v;
				DFS(u, clock);
				break;
			case DISCOVERED:
				type(v, u) = BACKWARD;
				break;
			default:
				type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
				break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
}


JTL_NAMESPACE_END
