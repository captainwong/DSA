// 2.35.rm_dup_ascii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/bitmap.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
#include <vector>
/*****************/

using namespace dtl;


typedef std::vector<char> ascii;

ascii rm_dup_ascii(const ascii& asc)
{
	ascii ret;
	Bitmap bmp;

	for (const auto& c : asc) {
		if (!bmp.test(c)) {
			bmp.set(c);
			ret.push_back(c);
		}
	}

	return ret;
}

int main()
{
	ascii A = { 'a', 'a', 'b', 'b', 'c', 'd' };
	auto B = rm_dup_ascii(A);
	ascii C = { 'a', 'b', 'c', 'd' };
	assert(B.size() == C.size());
	for (size_t i = 0; i < B.size(); i++) {
		assert(B[i] == C[i]);
	}
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
