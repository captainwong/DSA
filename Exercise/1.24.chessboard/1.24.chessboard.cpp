// 1.24.chessboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <bitset>
#include <vector>
#include <string>
#include <assert.h>

namespace textbook
{



}

namespace my
{

template <size_t N>
struct board {
	size_t length = 1 << (N);
	using line = std::bitset<(1 << (N))>;
	std::vector<line> square = {};

	explicit board()
	{
		for (size_t i = 0; i < length; ++i) {
			square.emplace_back(line());
		}

	}

	void print() {
		for (size_t i = 0; i < length; ++i) { printf("-"); }printf("\n");
		for (auto iter = square.rbegin(); iter != square.rend(); ++iter) {
			auto str = iter->to_string(' ', '*');
			std::reverse(str.begin(), str.end());
			printf("%s\n", str.c_str());
		}
		for (size_t i = 0; i < length; ++i) { printf("-"); }printf("\n");
	}

	void place(int x, int y, int dx, int dy) {
		assert(static_cast<size_t>(x) < length);
		assert(static_cast<size_t>(y) < length);
		assert(0 <= static_cast<size_t>(x + dx) && static_cast<size_t>(x + dx) < length);
		assert(0 <= static_cast<size_t>(y + dy) && static_cast<size_t>(y + dy) < length);

		static int g_round = 0;
		printf("\nround#%d x=%d,y=%d,dx=%d,dy=%d\n", g_round++, x, y, dx, dy);

		auto& line = square[y];
		line.set(x);
		line.set(x + dx);

		square[y + dy].set(x);

		printf("\n");
		print();
	}

	void cover(size_t n, int x, int y, int dx, int dy) {
		int s = 1 << (n - 1);
		place(x + dx * (s - 1), y + dy * (s - 1), dx, dy);
		if (n < 2) { return; }

		cover(n - 1, x, y, dx, dy);
		cover(n - 1, x + dx * s, y + dy * s, dx, dy);
		cover(n - 1, x + dx * (2 * s - 1), y, -dx, dy);
		cover(n - 1, x, y + dy * (2 * s - 1), dx, -dy);
	}

	void cover() {
		cover(N, 0, 0, 1, 1);
	}
};

}


int main()
{
	my::board<4> b;
	b.cover();
	//b.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
