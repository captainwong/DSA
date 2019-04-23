#pragma once
#include <string.h>
#include <stdio.h>

/**
* @brief 位图
* @note 位图是一种特殊的数据结构，可用以动态地表示由一组（无符号）整数构成的集合。其长度无限，且其中每个元素的取值均为布尔型（初始均为false）
*/
class Bitmap
{
private:
	//! 比特图所存放的空间M[]
	char* M = nullptr;
	//! 空间M的容量为 (N * sizeof(char) * 8) 比特，即 N 个字节
	int N = 0;


public:
	Bitmap(int n = 8) { init(n); }
	Bitmap(const char* path, int n = 8) { init(path, n); }
	~Bitmap() { destroy(); }

	void init(int n) {
		M = new char[N = (n + 7) / 8];
		memset(M, 0, N);
	}

	void init(const char* path, int n) {
		init(n);
		auto f = fopen(path, "r");
		fread(M, sizeof(char), n, f);
		fclose(f);
	}

	void destroy() { if (M) { delete[] M; M = nullptr; } N = 0; }

	void expand(int k) {
		if (k < 8 * N) { return; }
		auto oldN = N;
		auto oldM = M;
		init(2 * k);
		memcpy(M, oldM, oldN);
		delete[] oldM;
	}

	// O(1)
	void set(int k) {
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}

	// O(1)
	void clear(int k) {
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}

	// O(1)
	bool test(int k) {
		expand(k);
		return M[k >> 3] & (0x80 >> (k & 0x07));
	}

	//! 将位图整体导出至指定的文件，以便对此后的新位图批量初始化
	void dump(const char* path) {
		auto f = fopen(path, "w"); 
		fwrite(M, sizeof(char), N, f); 
		fclose(f);
	}

	//! 逐位打印
	void print(int n) {
		expand(n);
		for (int i = 0; i < n; i++) { printf(test(i) ? "1" : "0"); }
	}

	/**
	* @brief 将前n位转换为字符串
	* @return 字符串指针，由调用者负责释放
	*/
	char* toString(int n) {
		expand(n - 1);
		char* s = new char[n + 1]; s[n] = 0;
		for (int i = 0; i < n; i++) { s[i] = test(i) ? '1' : '0'; }
		return s;
	}
};


/**
* @brief 位图2
* @note 仅允许插入、测试，不支持删除
* @note 节省了初始化所有元素的时间
*/
class Bitmap2
{
public:
	typedef size_t Rank;

	Bitmap2(Rank n = 8)
		: N(n)
		, F(new Rank[n])
		, T(new Rank[n])
		, top(0)
	{}

	~Bitmap2() { delete[] F; delete[] T; }

	void set(Rank k) {
		if (test(k)) { return; }
		F[k] = top++; T[F[k]] = k;
	}

	bool test(Rank k) {
		return valid(F[k]) && (k == T[F[k]]);
	}

protected:
	bool valid(Rank r) { return (0 <= r) && (r < top); }

private:
	Rank* F; Rank N; // 规模为N的向量，记录[k]被标记的次序（即其在栈T[]中的秩）
	Rank* T; Rank top; // 容量为N的栈，记录被标记各位秩的栈，以及栈顶指针
};


/**
* @brief 位图3
* @note 允许插入、测试，支持删除
* @note 节省了初始化所有元素的时间
*/
class Bitmap3
{
public:
	typedef size_t Rank;

	Bitmap3(Rank n = 8)
		: N(n)
		, F(new Rank[n])
		, T(new Rank[n])
		, top(0)
	{}

	~Bitmap3() { delete[] F; delete[] T; }

	void set(Rank k) {
		if (test(k)) { return; }
		if (!erased(k)) { F[k] = top++; } // 若系初次标记，创建新校验环
		T[F[k]] = k; // 若系曾经标记后被清除，则恢复原校验环
	}

	void clear(Rank k) {
		if (test(k)) { T[F[k]] = -1 - k; } // 将T[F[k]]取负再减一
	}

	bool test(Rank k) {
		return valid(F[k]) && (k == T[F[k]]);
	}

protected:
	bool valid(Rank r) { return (0 <= r) && (r < top); }

	//! 判断[k]是否曾被标记过，且后来又被清除
	bool erased(Rank k) { return valid(F[k]) && !(T[F[k]] + 1 + k); }

private:
	Rank* F; Rank N; // 规模为N的向量，记录[k]被标记的次序（即其在栈T[]中的秩）
	Rank* T; Rank top; // 容量为N的栈，记录被标记各位秩的栈，以及栈顶指针
};
