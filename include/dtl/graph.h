#pragma once

#include <assert.h>
#include <limits.h> // INT_MAX
#include "queue.h"
#include "stack.h"

namespace dtl 
{

//! 顶点状态
enum class VertexStatus {
	//! 未发现
	undiscovered,
	//! 已发现
	discovered,
	//! 已访问
	visited,
};

//! 边状态
enum class EdgeStatus {
	//! 未处置
	undetermined,
	//! 树边
	tree,
	//! 跨边
	cross,
	//! 前向边
	forward,
	//! 后向边
	backward,
};

//! 图
template <typename Tv, typename Te>
class Graph
{
private:
	//! 所有顶点、边的辅助信息复位
	void reset() {
		for (int i = 0; i < n; i++) {
			status(i) = VertexStatus::undiscovered;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) {
				if (exists(i, j))
					type(i, j) = EdgeStatus::undetermined;
			}
		}
	}

	//! breadth first search
	void BFS(int v, int& clock) {
#if DSA_MODE
		printf("BFS in with v=%d, clock=%d\n", v, clock); 
#endif

		Queue<int> queue;
		status(v) = VertexStatus::discovered;
		queue.enqueue(v);


#if DSA_MODE
		printf("vetex %d", v); print(vertex(v)); printf(" status changed to VertexStatus::discovered\n");
		printf("current Q: "); print(queue);
#endif

		while (!queue.empty()) {
			int v = queue.dequeue();
			dTime(v) = ++clock;

#if DSA_MODE
			printf("visiting vertex v=%d", v); print(vertex(v)); printf("["); print(status(v)); printf("] dTime=%d\n", clock);
#endif

			for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {

#if DSA_MODE
				printf("visiting vertex u=%d", u); print(vertex(u)); printf("["); print(status(u)); printf("]\n");
#endif

				if (status(u) == VertexStatus::undiscovered) {
					status(u) = VertexStatus::discovered;
					queue.enqueue(u);
					type(v, u) = EdgeStatus::tree;
					parent(u) = v;
				} else {
					type(v, u) = EdgeStatus::cross;
				}

#if DSA_MODE
				printf("edge(%d, %d) ", v, u); print(vertex(v)); printf(" ->"); print(vertex(u)); printf(" now is "); print(type(v, u)); printf("\n");
#endif

			}
			status(v) = VertexStatus::visited;

#if DSA_MODE
			printf("vetex v=%d", v); print(vertex(v)); printf(" status changed to VertexStatus::visited\n");
			printf("current Q: "); print(queue);
#endif
		}
	}

	//! depth first search
	void DFS(int v, int& clock) {
		dTime(v) = ++clock;
		status(v) = VertexStatus::discovered;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
			switch (status(u)) {
				case VertexStatus::undiscovered:
					type(v, u) = EdgeStatus::tree;
					parent(u) = v;
					DFS(u, clock);
					break;
				case VertexStatus::discovered:
					type(v, u) = EdgeStatus::backward;
					break;
				default: // VertexStatus::visited
					type(v, u) = dTime(v) < dTime(u) ? EdgeStatus::forward : EdgeStatus::cross;
					break;
			}
		}

		status(v) = VertexStatus::visited;
		fTime(v) = ++clock;
	}

	//! topological sort
	bool TSORT(int v, int& clock, Stack<Tv>* s) {
		assert(0 <= v && v < n);
		
		dTime(v) = ++clock;
		status(v) = VertexStatus::discovered;

		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
			switch (status(u)) {
				case VertexStatus::undiscovered:
					parent(u) = v;
					type(v, u) = EdgeStatus::tree;
					if (!TSORT(u, clock, s)) {
						return false;
					}
					break;
				case VertexStatus::discovered:
					type(v, u) = EdgeStatus::backward;
					return false;
					break;
				default: // visited
					type(v, u) = (dTime(v) < dTime(u)) ? EdgeStatus::forward : EdgeStatus::cross;
					break;
			}
		}

		status(v) = VertexStatus::visited;
		s->push(vertex(v));
		return true;
	}

public:
	//! 顶点总数
	int n;
	//! 插入顶点，返回编号
	virtual int insert(Tv const& v) = 0;
	//! 删除顶点及其关联边，返回该顶点
	virtual Tv remove(int v) = 0;
	//! 顶点数据（该顶点的确存在）
	virtual Tv& vertex(int v) = 0;
	//! 顶点的入度（该顶点的确存在）
	virtual int inDegree(int v) = 0;
	//! 顶点的出度（该顶点的确存在）
	virtual int outDegree(int v) = 0;
	//! 顶点的首个邻接顶点
	virtual int firstNbr(int v) = 0;
	//! 顶点v的（相对于顶点j的）下一个邻接顶点
	virtual int nextNbr(int v, int j) = 0;
	//! 顶点状态
	virtual VertexStatus& status(int v) = 0;
	//! 顶点 discovered time
	virtual int& dTime(int v) = 0;
	//! 顶点 finished time
	virtual int& fTime(int v) = 0;
	//! 顶点在遍历树中的父亲
	virtual int& parent(int v) = 0;
	//! 顶点在遍历树中的优先级
	virtual int& priority(int v) = 0;

	//! 边总数
	int e;
	//! 边(v,u)是否存在
	virtual bool exists(int v, int u) = 0;
	//! 在顶点v、u之间插入权重为w的边e
	virtual void insert(Te const& e, int w, int v , int u) = 0;
	//! 的喊出顶点v、u之间的边e，返回该边信息
	virtual Te remove(int v, int u) = 0;
	//! 边（v，u）的数据（该边的确存在）
	virtual EdgeStatus& type(int v, int u) = 0;
	//! 边（v，u）的权重
	virtual int& weight(int v, int u) = 0;

	//********* algorithms *********************//

	//! 广度优先搜索
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

	//! 深度优先搜索
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

	//! 基于DFS的拓扑排序算法
	Stack<Tv>* tsort(int s) {
		assert(0 <= s && s < n);
		reset();
		int clock = 0, v = s;
		auto S = new Stack<Tv>();
		do {
			if (status(v) == VertexStatus::undiscovered) {
				if (!TSORT(v, clock, S)) {
					S->clear();
					break;
				}
			}
		} while (s != (v = (++v % n)));
		return S;
	}
};

}
