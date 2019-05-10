#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"
#include "../../include/dtl/deque.h"
#include "../../include/dtl/queue.h"
#include <stdio.h>
#include <ctype.h>

// a) 支持 + *
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

static void calc2(int target)
{
	dtl::Deque<char> Q;
	for (auto c : "0123456789") { Q.push_back(c); }

	auto insert_optr = [](dtl::Deque<char> Q, int pos, char optr) {
		auto p = Q.first();
		while (pos--) { p = p->succ; }
		Q.insert_after(p, optr);
		return Q;
	};



	for (int i = 1; i < 10; i++) {

	}
}

static void calc3(int target)
{
	dtl::Queue<char> Q;
	for (auto c : "0123456789") { Q.enqueue(c); }

	dtl::Stack<char> S;

	S.push(Q.dequeue());

	do {
		for (auto optr : "\0+*") {
			S.push(optr);

		}

	} while (!Q.empty());
}

#include <ctype.h> // isdigit
#include <math.h> // pow

//! 运算符总数
static constexpr auto MAX_OPRATOR = 9;

//! 运算符
enum class Operator : int
{
	ADD, // +
	SUB, // -
	MUL, // *
	DIV, // /
	POW, // ^
	FAC, // ! factorial
	L_P, // ( left parenthesis
	R_P, // ) right parenthesis
	EOE, // \0 end of expression
	EOO, // 9, sentinel, end of operator
};

//! 字符串转为运算符
static Operator operatorFromChar(char c)
{
	switch (c) {
		case '+': return Operator::ADD;
		case '-': return Operator::SUB;
		case '*': return Operator::MUL;
		case '/': return Operator::DIV;
		case '^': return Operator::POW;
		case '!': return Operator::FAC;
		case '(': return Operator::L_P;
		case ')': return Operator::R_P;
		case '\0': return Operator::EOE;
		default: return Operator::EOO;
	}
}

//! 运算符转为字符
static char opeator2char(Operator op)
{
	static constexpr auto cc = "+-*/^!()\0";
	if (op < Operator::EOO) { return cc[(int)op]; }
	return '$';
}

namespace dtl
{
template <>
static void print(Operator& op) { printf("%c", opeator2char(op)); }
}

//! 运算符优先级
enum class OperatorPriority : char
{
	LT, // <
	EQ, // ==
	GT, // >
	EOP, // sentinel, end of priority
};

//! 比较两个运算符的优先级
static OperatorPriority compareOperator(Operator op1, Operator op2)
{
	if (op1 == Operator::EOO || op2 == Operator::EOO) { return OperatorPriority::EOP; }

	static constexpr char TABLE[MAX_OPRATOR][MAX_OPRATOR] = {
		/*              |-------------------- 当 前 运 算 符 --------------------| */
		/*              +      -      *      /      ^      !      (      )      \0 */
		/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
		/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
		/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
		/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
		/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
	};

	auto p = TABLE[(int)op1][(int)op2];
	if (p == '<') {
		return OperatorPriority::LT;
	} else if (p == '>') {
		return OperatorPriority::GT;
	} else if (p == '=') {
		return OperatorPriority::EQ;
	} else {
		return OperatorPriority::EOP;
	}
}

//! 比较两个运算符的优先级
static OperatorPriority compareOperator(char op1, char op2)
{
	return compareOperator(operatorFromChar(op1), operatorFromChar(op2));
}

//! 阶乘
static __int64 factorial(__int64 n)
{
	__int64 f = 1;
	while (n > 1) {
		f *= n--;
	}
	return f;
}

//! 二元计算
static float calc(float a, float b, Operator op)
{
	switch (op) {
		case Operator::ADD: return a + b;
			break;
		case Operator::SUB: return a - b;
			break;
		case Operator::MUL: return a * b;
			break;
		case Operator::DIV:
			if (static_cast<int>(b) == 0) {
				assert(0);
				return 0;
			}
			return a / b;
			break;
		case Operator::POW: return pow(a, b);
			break;
		default:
			assert(0);
			return 0;
			break;
	}
}

//! 一元计算
static __int64 calc(__int64 a, Operator op)
{
	if (op == Operator::FAC) { return factorial((a)); }
	assert(0);
	return 0;
}


static void brute_force(int target)
{
	char expr[] = "0 1 2 3 4 5 6 7 8 9";
	char optrs[3] = { ' ', '+', '*' };
	
	auto evaluate = [&expr]() -> __int64 {
		const char* s = expr;
		dtl::Stack<__int64> opnd;
		dtl::Stack<char> optr; optr.push('\0');

		do {
			if (isdigit(*s)) {
				__int64 n = *s++ - '0';
				while (isdigit(*s) || ' ' == *s) {
					if (' ' == *s) {
						if (n == 0) {
							return -1;
						}
						s++;
						continue;
					}
					
					n = n * 10 + (*s++ - '0');
				}

				opnd.push(n);

			} else {

				auto o1 = optr.top();
				auto o2 = *s;

				switch (compareOperator(o1, o2)) {
					case OperatorPriority::GT:
					{
						auto calc = [](__int64 a, __int64 b, char op) {
							switch (op) {
								case '+': return a + b;
								case '*': return a * b;
								default: return 0LL;
							}
						};
						auto b = opnd.pop();
						auto a = opnd.pop();
						opnd.push(calc(a, b, o1));
						optr.pop();
						break;
					}
					case OperatorPriority::LT:
						optr.push(o2);
						s++;
						break;
					case OperatorPriority::EQ:
						optr.pop();
						s++;
						break;
				}
			}

		} while (!optr.empty());

		return opnd.pop();
	};

	auto printE = [&expr](__int64 res) {
		static int i = 0;
		printf("#%d:\t", i++);
		for (auto c : expr) {
			if (c != ' ') { printf("%c", c); }
		}
		printf("\t=\t%lld", res);
		printf("\n");
	};

	int pos = 1;
	for (auto o0 : optrs) {
		if (o0 == ' ') { continue; }
		expr[pos] = o0;
		for (auto o1 : optrs) {
			expr[pos + 2] = o1;
			for (auto o2 : optrs) {
				expr[pos + 4] = o2;
				for (auto o3 : optrs) {
					expr[pos + 6] = o3;
					for (auto o4 : optrs) {
						expr[pos + 8] = o4;
						for (auto o5 : optrs) {
							expr[pos + 10] = o5;
							for (auto o6 : optrs) {
								expr[pos + 12] = o6;
								for (auto o7 : optrs) {
									expr[pos + 14] = o7;
									for (auto o8 : optrs) {
										expr[pos + 16] = o8; 
										auto res = evaluate();
										//printE(res);
										if (res == target) {
											printE(res);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
