#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"
#include "../../include/dtl/deque.h"
#include "../../include/dtl/queue.h"
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
static __int64 calc(__int64 a, __int64 b, Operator op)
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
		case Operator::POW: return static_cast<__int64>(pow(a, b));
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

static __int64 read_number(const char*& s)
{
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
	return n;
}

struct Statistics
{
	int candidate = 0;
	int check = 0;
	int solution = 0;
};

// a) 支持 + * 暴力版
static void a_brute_force(int target)
{
	char expr[] = "0 1 2 3 4 5 6 7 8 9";
	char optrs[3] = { ' ', '+', '*' };
	Statistics stat = {};
	
	auto evaluate = [&expr, target]() -> __int64 {
		const char* s = expr;
		dtl::Stack<__int64> opnd;
		dtl::Stack<char> optr; optr.push('\0');

		do {
			if (isdigit(*s)) {
				auto n = read_number(s);
				if (n < 0 || n > target) { // 剪枝 非法数字、过大数字的情况
					return -1;
				}
				opnd.push(n);
			} else {
				auto o1 = optr.top();
				auto o2 = *s;

				switch (compareOperator(o1, o2)) {
					case OperatorPriority::GT:
					{						
						auto b = opnd.pop();
						auto a = opnd.pop();
						opnd.push(calc(a, b, operatorFromChar(o1)));
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
			if (c != ' ') {
				printf("%c", c);
				//if (!isdigit(c)) {
				//	printf(" ");
				//}
			}
		}
		printf("\t=\t%lld", res);
		printf("\n");
	};

	int pos = 1;
	for (auto o0 : optrs) {
		if (o0 == ' ') { continue; } // 剪枝 012... 的情况
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
										stat.candidate++;
										auto res = evaluate();
										//printE(res); 
										if (res == target) {
											printE(res);
											stat.solution++;
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

	printf("a_brute_force, target=%d, %d candidates, %d solutions\n", target, stat.candidate, stat.solution);
}

//! 字符串简单封装，以\0结尾
struct string
{
	char* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	string(int n = 16) {
		capacity = n << 1;
		size = 0;
		data = new char[capacity];
	}

	string(const char* s) {
		size = strlen(s) + 1;
		capacity = size << 1;
		data = new char[capacity];
		memcpy(data, s, size);
	}

	

	~string() { delete[] data; }

	void expand() {
		if ((size << 1) < capacity ) { return; }
		capacity <<= 1;
		auto old = data;
		data = new char[capacity];
		memcpy(data, old, size);
		delete[] old;
	}

	char& at(size_t i) const { return data[i]; }

	void insert(size_t i, char c) {
		expand();
		for (size_t j = size + 1; j > i; j++) {
			data[j] = data[j - 1];
		}
		data[i] = c;
	}
	
	void remove(size_t i) {
		while (i < size) {
			data[i] = data[i + 1];
		}
		size--;
	}
};

// a) 支持 + * 剪枝版
static void a_pruning(int target)
{
	string expr("0123456789");
	char optrs[3] = { ' ', '+', '*' };
	Statistics stat = {};

	

	printf("a_pruning, target=%d, %d candidates, %d solutions\n", target, stat.candidate, stat.solution);
}



// b) 支持 + * ! 暴力版
static void b_brute_force(int target)
{
	char expr[] = "0 1 2 3 4 5 6 7 8 9";
	char optrs[4] = { ' ', '+', '*', '!' };
	Statistics stat = {};

	auto evaluate = [&expr, target]() -> __int64 {
		const char* s = expr;
		dtl::Stack<__int64> opnd;
		dtl::Stack<char> optr; optr.push('\0');

		do {
			if (isdigit(*s)) {
				auto n = read_number(s);
				if (n < 0 || n > target) { // 剪枝 非法数字、过大数字的情况
					return -1;
				}
				opnd.push(n);
			} else {
				auto o1 = optr.top();
				auto o2 = *s;

				switch (compareOperator(o1, o2)) {
					case OperatorPriority::GT:
					{
						auto b = opnd.pop();
						if (o1 == '!') {
							opnd.push(calc(b, Operator::FAC));
						} else {
							auto a = opnd.pop();
							opnd.push(calc(a, b, operatorFromChar(o1)));
						}
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
			if (c != ' ') {
				printf("%c", c);
				//if (!isdigit(c)) {
				//	printf(" ");
				//}
			}
		}
		printf("\t=\t%lld", res);
		printf("\n");
	};

	int pos = 1;
	for (auto o0 : optrs) {
		if (o0 == ' ') { continue; } // 剪枝 012... 的情况
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
										stat.candidate++;
										auto res = evaluate();
										//printE(res); 
										if (res == target) {
											printE(res);
											stat.solution++;
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

	printf("b_brute_force, target=%d, %d candidates, %d solutions\n", target, stat.candidate, stat.solution);
}
