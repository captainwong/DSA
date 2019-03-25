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
