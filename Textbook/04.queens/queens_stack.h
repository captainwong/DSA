#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"
#include "../../include/dtl/vector.h"
#include "queen.h"

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

void placeQueens(int N, dtl::Vector<dtl::Stack<Queen>>& solutions, statistics& stat, int wait_ms)
{
	dtl::Stack<Queen> solution;
	Queen cur;

	do {
		if (N <= solution.size() || N <= cur.y) {
			cur = solution.pop();// print(solution);
			cur.y++;
		} else {
			while (cur.y < N && (solution.find(cur))) {
				cur.y++;
				stat.check++;
			}
			if (cur.y < N) {
				solution.push(cur); //print(solution);
				if (solution.size() == N) {
					solutions.insert(solution);
					stat.solution++;					
				}
				cur.x++;
				cur.y = 0;
			}
		}

		[](int N, dtl::Stack<Queen>& solu, const statistics& stat, int wait_ms) {
			system("cls");
			auto trav = [N](Queen& queen) {
				printf("%2d,%2d: ", queen.x, queen.y);
				int i = 0;
				while (i++ < queen.y) { printf("[]"); }
				printf("█");
				while (i++ < N) { printf("[]"); }
				printf("\n");
			};
			solu.traverse(trav);
			printf("%d solution(s) found after %d check(s)\n", stat.solution, stat.check);
			dtl::wait(wait_ms);
		}(N, solution, stat, wait_ms);
	} while ((0 < cur.x) || (cur.y < N));
}
