#pragma once

#include <limits.h>
#include "../include/queue.h"

enum class VertexStatus {
	undiscovered,
	discovered,
	visited,
};

enum class EdgeStatus {
	undetermined,
	tree,
	cross,
	forward,
	backward,
};

template <typename Tv, typename Te>
class Graph
{
private:
	void reset()
	{
		for (int i = 0; i < n; i++) {
			status(i) = VertexStatus::undiscovered;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) {
				if (exists(i, j))
					status(i, j) = EdgeStatus::undetermined;
			}
		}
	}

	//! breadth first search
	void BFS(int v, int& clock) {
		Queue<int> queue;
		status(v) = VertexStatus::discovered;
		queue.enqueue(v);
		while (!queue.empty()) {
			int v = queue.dequeue();
			dTime(v) = ++clock;
			for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
				if (status(u) == VertexStatus::undiscovered) {
					status(u) = VertexStatus::discovered;
					queue.enqueue(u);
					status(v, u) = EdgeStatus::tree;
					parent(u) = v;
				} else {
					status(v, u) = EdgeStatus::cross;
				}
			}
			status(v) = VertexStatus::visited;
		}
	}

	//! depth first search
	void DFS(int v, int& clock) {
		dTime(v) = ++clock;
		status(v) = VertexStatus::discovered;
		for (int u = = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
			switch (status(u)) {
				case VertexStatus::undiscovered:
					status(v, u) = EdgeStatus::tree;
					parent(u) = v;
					DFS(u, clock);
					break;
				case VertexStatus::discovered:
					status(v, u) = EdgeStatus::backward;
					break;
				default: // VertexStatus::visited
					status(v, u) = dTime(v) < dTime(u) ? EdgeStatus::forward : EdgeStatus::cross;
					break;
			}
		}

		status(v) = VertexStatus::visited;
		fTime(v) = ++clock;
	}

public:
	int n;	// vetex
	virtual int insert(Tv const&) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	virtual int nextNbr(int) = 0;
	virtual VertexStatus& status(int) = 0;
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;

	int e;	// edge
	virtual bool exists(int, int) = 0;
	virtual void insert(Te const&, int, int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EdgeStatus& status(int, int) = 0;
	virtual int& weight(int, int) = 0;

	// algorithms
	void bfs(int s) {
		reset();
		int clock = 0;
		int v = s;
		do {
			if (VertexStatus::undiscovered == status(v)) {
				BFS(v, clock);
			}
		} while (s != (v = (++v % n)));
	}

	void dfs(int s) {
		reset();
		int clock = 0;
		int v = s;
		do {
			if (VertexStatus::undiscovered == status(v)) {
				DFS(v, clock);
			}
		} while (s != (v = (++v % n)));
	}

};
