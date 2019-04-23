#include <stdio.h>
#include "../include/dtl/stack.h"

/***测试用******/
#include <assert.h>
/*****************/

using namespace dtl;

namespace chapter_4_3_1
{

/**
* @brief 进制转换
* @param S 输出栈，即转换进制后的字符串
* @param n 十进制数
* @param base 要转换为的进制[2,16]
*/
void convert(Stack<char>&S, __int64 n, int base)
{
	static const char digits[] = "0123456789ABCDEF";
	if (0 < n) {
		char c = digits[n % base];
		S.push(c);
		convert(S, n / base, base);
	}
}

/**
* @brief 进制转换（迭代版）
* @param S 输出栈，即转换进制后的字符串
* @param n 十进制数
* @param base 要转换为的进制[2,16]
*/
void convert_I(Stack<char>&S, __int64 n, int base)
{
	static const char digits[] = "0123456789ABCDEF";
	while (0 < n) {
		char c = digits[n % base];
		S.push(c);
		n /= base;
	}
}

void test_convert()
{
	const char expect[] = "30071";

	Stack<char> s;
	convert(s, 12345, 8);
	assert(s.size() == 5);
	for (int i = 0; i < 5; i++) {
		assert(s.pop() == expect[i]);
	}

	convert_I(s, 12345, 8);
	assert(s.size() == 5);
	for (int i = 0; i < 5; i++) {
		auto c = s.pop();
		assert(c == expect[i]);
	}
}

}

int main(int argc, char* argv[])
{
	chapter_4_3_1::test_convert();
	return 0;
}