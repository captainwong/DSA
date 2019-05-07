#pragma once

#include "../../include/dtl/stack.h"

/***������******/
#include <assert.h>
/*****************/


namespace chapter_4_3_1
{

/**
* @brief ����ת��
* @param S ���ջ����ת�����ƺ���ַ���
* @param n ʮ������
* @param base Ҫת��Ϊ�Ľ���[2,16]
*/
void convert(dtl::Stack<char>&S, __int64 n, int base)
{
	static const char digits[] = "0123456789ABCDEF";
	if (0 < n) {
		char c = digits[n % base];
		S.push(c);
		convert(S, n / base, base);
	}
}

/**
* @brief ����ת���������棩
* @param S ���ջ����ת�����ƺ���ַ���
* @param n ʮ������
* @param base Ҫת��Ϊ�Ľ���[2,16]
*/
void convert_I(dtl::Stack<char>&S, __int64 n, int base)
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

	dtl::Stack<char> s;
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
