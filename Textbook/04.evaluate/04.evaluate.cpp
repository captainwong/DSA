// 04.evaluate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "evaluate.h"



int main()
{
	auto test = [](const char* expr, int expect_vaule) {
		dtl::Vector<char> rpn;
		float value;
		bool res = evaluate(expr, rpn, value, dtl::WAIT_NO_WAIT); //求值
		printf("EXPR\t: %s\n", expr); //输出原表达式
		printf("RPN\t: \n"); print(rpn); //输出RPN
		printf("Value\t= %.1f = %d\n", value, (int)value); //输出表达式的值
		assert((int)value == expect_vaule);
	};

	//test("0+(1+23)/4*5*67-8+9", 2011);
	test("(0!+1)*2^(3!+4)-(5!-67-(8+9))", 2012);
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
