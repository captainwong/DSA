#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h> // __min
#include "bitmap.h"

namespace dtl 
{

/**
* @brief 计算不大于n的所有素数
* @note 埃拉托斯特尼筛法 https://zh.wikipedia.org/zh-cn/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95
* @param n 不大于n
* @param bmp 位图，保存不大于n的所有合数
*/
static void eratosthenes(int n, Bitmap& bmp)
{
	bmp.set(0); bmp.set(1); // 0, 1 都不是素数

	for (int i = 2; i < n; i++) {
		if (!bmp.test(i)) {
			// 46340^2 = 2147395600 未超过int可以表示的范围 2147483647
			// 46341^2 = 2147488281 超过了int可以表示的范围
			// 选用 46340 可以避免整数溢出
			// 位于[2i, i^2)之间的整数，均已经在此前的迭代中被筛除了
			for (int j = __min(i, 46340) * __min(i, 46340); j < n; j += i) {
				bmp.set(j);
			}
		}
	}
}

//! 计算不大于n的所有素数，将不大于n的所有合数（筛子）存入文件
static void eratosthenes_to_file(int n, const char* path)
{
	Bitmap bmp;
	eratosthenes(n, bmp);
	bmp.dump(path);
}

/**
* @brief 计算不小于c：[c, n)内的最小素数
* @param c 不小于c
* @param n 小于n
* @param path 可选，如果传入则从该文件读取筛子，否则计算
* @return 如果计算成功，返回不小于c的最小素数，否则返回0
*/
static int primeNLT(int c, int n, const char* path = nullptr)
{
	Bitmap bmp;
	if (path) {
		bmp.init(path, n);
	} else {
		eratosthenes(n, bmp);
	}
	
	while (c < n) {
		if (bmp.test(c)) { c++; }
		else { return c; }
	}

	return 0;
}

}
