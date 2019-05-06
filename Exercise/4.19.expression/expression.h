#pragma once

#include "../../include/dtl/stack.h"

// a) Ö§³Ö + *
static void program_a(int S)
{
	dtl::Stack<int> opnd;
	for (int i = 9; i >= 0; i--) {
		opnd.push(i);
	}

	auto giveBack = [&opnd](int n) {
		int m = n % 10;
		n /= 10;
		opnd.push(m);
		return n;
	};

	auto a = opnd.pop();

	while (!opnd.empty()) {
		char optrs[] = "+*";
		for (auto optr : optrs) {
			if (optr == '+') {

			} else {

			}
		}
	}
}

static void calc(int S)
{

}