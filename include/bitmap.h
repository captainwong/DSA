#pragma once
#include <string.h>

/**
* @brief λͼ
* @note λͼ��һ����������ݽṹ�������Զ�̬�ر�ʾ��һ�飨�޷��ţ��������ɵļ��ϡ��䳤�����ޣ�������ÿ��Ԫ�ص�ȡֵ��Ϊ�����ͣ���ʼ��Ϊfalse��
*/
class Bitmap
{
private:
	//! ����ͼ����ŵĿռ�M[]
	char* M;
	//! �ռ�M������Ϊ (N * sizeof(char) * 8) ���أ��� N ���ֽ�
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
};


/**
* @brief λͼ2
* @note ��������롢���ԣ���֧��ɾ��
* @note ��ʡ�˳�ʼ������Ԫ�ص�ʱ��
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
	Rank* F; Rank N; // ��ģΪN����������¼[k]����ǵĴ��򣨼�����ջT[]�е��ȣ�
	Rank* T; Rank top; // ����ΪN��ջ����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ��
};


/**
* @brief λͼ3
* @note ������롢���ԣ�֧��ɾ��
* @note ��ʡ�˳�ʼ������Ԫ�ص�ʱ��
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
		if (!erased(k)) { F[k] = top++; } // ��ϵ���α�ǣ�������У�黷
		T[F[k]] = k; // ��ϵ������Ǻ��������ָ�ԭУ�黷
	}

	void clear(Rank k) {
		if (test(k)) { T[F[k]] = -1 - k; } // ��T[F[k]]ȡ���ټ�һ
	}

	bool test(Rank k) {
		return valid(F[k]) && (k == T[F[k]]);
	}

protected:
	bool valid(Rank r) { return (0 <= r) && (r < top); }

	//! �ж�[k]�Ƿ�������ǹ����Һ����ֱ����
	bool erased(Rank k) { return valid(F[k]) && !(T[F[k]] + 1 + k); }

private:
	Rank* F; Rank N; // ��ģΪN����������¼[k]����ǵĴ��򣨼�����ջT[]�е��ȣ�
	Rank* T; Rank top; // ����ΪN��ջ����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ��
};
