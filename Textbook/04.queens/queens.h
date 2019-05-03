#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"
#include "../../include/dtl/vector.h"

struct Queen
{
	int x, y;
	Queen(int x = 0, int y = 0)
		: x(x)
		, y(y)
	{}

	bool operator==(const Queen& rhs) {
		return (x == rhs.x)
			|| (y == rhs.y)
			|| (x + y == rhs.x + rhs.y)
			|| (x - y == rhs.x - rhs.y);
	}
};

namespace dtl
{
template <>
void print(Queen& q) {
	printf("[%d,%d]", q.x, q.y);
}
}

void placeQueens(int N, dtl::Vector<dtl::Stack<Queen>>& solutions)
{
	dtl::Stack<Queen> solution;
	Queen cur;

	do {
		if (N <= solution.size() || N <= cur.y) {
			cur = solution.pop(); print(solution);
			cur.y++;
		} else {
			while (cur.y < N && (solution.find(cur))) {
				cur.y++;
			}
			if (cur.y < N) {
				solution.push(cur); print(solution);
				if (solution.size() == N) {
					solutions.insert(solution);
				}
				cur.x++;
				cur.y = 0;
			}
		}
	} while ((0 < cur.x) || (cur.y < N));
}
