#pragma once
#include <string.h>

/**
* @brief 位图
* @note 位图是一种特殊的数据结构，可用以动态地表示由一组（无符号）整数构成的集合。其长度无限，且其中每个元素的取值均为布尔型（初始均为false）
*/
class Bitmap
{
private:
	//! 比特图所存放的空间M[]
	char* M;
	//! 空间M的容量为 (N * sizeof(char) * 8) 比特，即 N 个字节
	int N;

protected:
	void init(int n) {
		M = new char[N = (n + 7) / 8];
		memset(M, 0, N);
	}

public:
	Bitmap(int n = 8) { init(n); }
	~Bitmap() { delete[] M; }

	void expand(int k) {
		if (k < 8 * N) { return; }
		auto oldN = N;
		auto oldM = M;
		init(2 * k);
		memcpy(M, oldM, oldN);
		delete[] oldM;
	}

	void set(int k) {
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}

	void clear(int k) {
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}

	bool test(int k) {
		expand(k);
		return M[k >> 3] & (0x80 >> (k & 0x07));
	}
};
