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

static void impl(dtl::List<int>& opnd, int target)
{
	auto read = [&opnd](int size) {
		int n = 0;
		while (size--) {
			n = n * 10 + opnd.first()->data;
			opnd.remove(opnd.first());
		}
		return n;
	};

	for (int i = 1; i < opnd.size(); i++) {
		auto n = read(i);
	}
}

static void calc(int S)
{
	dtl::List<int> opnd = { 0,1,2,3,4,5,6,7,8,9 };

	auto read = [](dtl::List<int> opnd, int size) {
		int n = 0;
		while (size--) {
			n = n * 10 + opnd.first()->data;
			opnd.remove(opnd.first());
		}
		return n;
	};

	char optr[] = "\0+*";

	auto insert_optr = [](dtl::List<int> opnd, int pos, int optr) {
		auto begin = opnd.first();
		while (pos--) { begin = begin->succ; }
		opnd.insert_after(begin, optr);
		return opnd;
	};

	auto evaluate = [](dtl::List<int>& expr) {
		auto p = expr.first(); expr.remove(expr.first());
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			auto expr = insert_optr(opnd, i, optr[j]);

		}
	}
}