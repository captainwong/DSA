// 04.queens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "queens.h"
#include "5queens_brute_force.h"

using namespace dtl;


void test_brute_force_5_queens()
{
	statistics stat = {};
	place_5_queens_brute_force(stat, -1);
}

void test_n_queens_stack(int n)
{
	dtl::Vector<dtl::Stack<Queen>> solutions;
	placeQueens(n, solutions);
	print(solutions);
}


int main()
{
	test_brute_force_5_queens();

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
