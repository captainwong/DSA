// 04.queens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "queens_brute_force.h"
#include "queens_pruning.h"
#include "queens_stack.h"

using namespace dtl;


void test_n_queens_Iter(int wait_ms = WAIT_PAUSE)
{
	auto funcs = {
		place_5_queens_brute_force,
		place_2_queens_pruning,
		place_3_queens_pruning,
		place_4_queens_pruning,
		place_5_queens_pruning,
	};

	for (auto func : funcs) {
		statistics stat = {};
		func(stat, wait_ms);
		wait(wait_ms);
	}
}

void test_n_queens_Recursive(int max_queens = 5, int wait_ms = WAIT_PAUSE)
{
	for (int i = 2; i <= max_queens; i++) {
		statistics stat = {};
		place_n_queens_prunning(i, stat, wait_ms);
		wait(wait_ms);
	}
}

void test_n_queens_stack(int n)
{
	dtl::Vector<dtl::Stack<Queen>> solutions;
	placeQueens(n, solutions);
	print(solutions);
}


int main()
{
	//test_n_queens_Iter();
	test_n_queens_Recursive();
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
