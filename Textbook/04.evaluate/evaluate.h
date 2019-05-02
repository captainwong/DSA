#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/stack.h"
#include "../../include/dtl/vector.h"
#include <stdio.h>
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
	LESS, // <
	EQUAL, // ==
	GREATER, // >
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
		return OperatorPriority::LESS; 
	} else if (p == '>') {
		return OperatorPriority::GREATER;
	} else if (p == '=') {
		return OperatorPriority::EQUAL;
	}else {
		return OperatorPriority::EOP;
	}
}

//! 比较两个运算符的优先级
static OperatorPriority compareOperator(char op1, char op2)
{
	return compareOperator(operatorFromChar(op1), operatorFromChar(op2));
}

//! 阶乘
static __int64 factorial(int n)
{
	__int64 f = 1;
	while (n > 1) {
		f *= n--;
	}
	return f;
}

//! 将起始于p的子串解析为数值，并存入操作数栈
static void readNumber(const char*& p, dtl::Stack<float>& S)
{
	S.push((*p - '0') * 1.0F);
	while (isdigit(*++p)) {
		S.push(S.pop() * 10 + (*p - '0'));
	}
	if ('.' != *p) { return; }
	float fraction = 0.1F;
	while (isdigit(*++p)) {
		S.push(S.pop() + (*p - '0') * fraction);
		fraction *= 0.1F;
	}
}

//! 将操作数接至RPN末尾
static void append2RPN(dtl::Vector<char>& rpn, float operand)
{
	char buf[64] = { 0 };
	if (operand != static_cast<float>(static_cast<int>(operand))) {
		sprintf(buf, "%.2f ", operand);
		
	} else {
		sprintf(buf, "%d ", static_cast<int>(operand));
	}

	for (auto c : buf) {
		if (c == '\0') { break; }
		rpn.insert(c);
	}
}

//! 将运算符接至RPN末尾
static void append2RPN(dtl::Vector<char>& rpn, Operator op)
{
	rpn.insert(' ');
	rpn.insert(opeator2char(op));
	rpn.insert(' ');
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
static float calc(float a, Operator op)
{
	if (op == Operator::FAC) { return static_cast<float>(factorial(static_cast<int>(a))); }
	assert(0);
	return 0;
}

//! 错误处理
static void errorHandler(const char* s)
{

}

//! 显示表达式处理过程
static void displayProgress(const char* expr, const char* pch, dtl::Stack<float>& opnd, dtl::Stack<Operator>& optr, dtl::Vector<char>& rpn, int wait_ms)
{
	system("cls");
	for (const char* p = expr; '\0' != *p; p++) {
		printf(" %c", *p);
	}printf(" $\n");

	for (const char* p = expr; p < pch; p++) {
		printf("  ");
	}

	if ('\0' != *(pch - 1)) {
		for (const char* p = pch; '\0' != *p; p++) {
			printf(" %c", *p);
		}printf(" $");
	}printf("\n");

	for (const char* p = expr; p < pch; p++) {
		printf("--");
	}printf(" ^\n\n");

	print(opnd);
	print(optr);
	print(rpn);
	
	dtl::wait(wait_ms);
}

//! 对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
static bool evaluate(const char* S, dtl::Vector<char>& RPN, float& result, int wait_ms)
{
	auto expr = S;
	dtl::Stack<float> operands;
	dtl::Stack<Operator> operators;
	operators.push(Operator::EOE); // sentinel
	while (!operators.empty()) {
		if (isdigit(*S)) {
			readNumber(S, operands);
			append2RPN(RPN, operands.top());
		} else {
			auto op = operatorFromChar(*S);
			if (op == Operator::EOO) { errorHandler(S); return false; }
			switch (compareOperator(operators.top(), op)) {
				case OperatorPriority::LESS:
					operators.push(op);
					S++;
					break;
				case OperatorPriority::EQUAL:
					operators.pop();
					S++;
					break;
				case OperatorPriority::GREATER:
				{
					auto opCur = operators.pop();
					append2RPN(RPN, opCur);
					if (Operator::FAC == opCur) {
						auto opnd = operands.pop();
						operands.push(calc(opnd, opCur));
					} else {
						auto opnd2 = operands.pop();
						auto opnd1 = operands.pop();
						operands.push(calc(opnd1, opnd2, opCur));
					}
					break;
				}
				default:
					assert(0);
					break;
			}
		}

		displayProgress(expr, S, operands, operators, RPN, wait_ms);
	}

	result = operands.pop();
	return true;
}
