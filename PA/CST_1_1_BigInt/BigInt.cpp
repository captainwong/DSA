#if !defined(_OJ_)
#define  _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <string.h>

#define MAX_VAR 0x7FFFFFFFL

#define DEFAULT_CAPACITY (64 * 1024)
template <typename T>
class vector
{
private:
	T* _elem;
	int _capacity;
	int _size;
public:
	vector() : _capacity(DEFAULT_CAPACITY), _size(0) { _elem = new T[_capacity]; }
	~vector() { delete[] _elem; }
	void expand()
	{
		if ((_size << 1) < _capacity)
			return;
		if (_size == _capacity) {
			T* old = _elem;
			_elem = new T[_capacity <<= 1];
			memcpy(_elem, old, _size * sizeof(T));
			delete old;
		}
	}
	void push_back(T const& data) { expand(); _elem[_size++] = data; }
	T& operator[](int rank) { return _elem[rank]; }
	int size() const { return _size; }
	void clr() { _size = 0; _elem[0] = 0; }
};

//typedef struct BigInt {
//	int v[1000];
//	int pos;
//	void clr() { memset(this, 0, sizeof(BigInt)); }
//	BigInt() { clr(); }
//}BigInt;
//
//BigInt a, b;
//
//#define BF_SIZE (128 * 1024 * 1024)
//char bf[BF_SIZE] = { 0 };

int main(int argc, char* argv[])
{
	int n = 0;
	if (scanf("%d\n", &n) != 1)
		return 0;

	char c;
	long long t;
	//BigInt r;
	//fread(bf, 1, BF_SIZE, stdin);
	//int pos = 0;
	vector<char> a, b, res;
	for (int i = 0; i < n; i++) {
		//a.pos = 0; b.pos = 0;
		//
		//a.v[0] = 0;
		//while (scanf("%c", &c) == 1) {
		//	if (c == ' ') break;
		//	c -= '0';
		//	t = (long long)a.v[a.pos] * 10 + c;
		//	if (t >= MAX_VAR) {
		//		a.v[++a.pos] = c;
		//	} else {
		//		a.v[a.pos] = t & 0xFFFFFFFF;
		//	}
		//}
		//
		//b.v[0] = 0;
		//while (scanf("%c", &c) == 1) {
		//	if (c == '\r' || c == '\n') break;
		//	c -= '0';
		//	t = (long long)b.v[b.pos] * 10 + c;
		//	if (t >= MAX_VAR) {
		//		b.v[++b.pos] = c;
		//	} else {
		//		b.v[b.pos] = t & 0xFFFFFFFF;
		//	}
		//}
		//
		// /*r.clr();*/ r.v[0] = 0; r.v[1] = 0; r.pos = 1;
		//while (a.pos >= 0) {
		//	t = a.v[a.pos--];
		//	int bpos = b.pos;
		//	for (int j = 0; j < t; j++) {
		//		while (b.pos >= 0) {
		//			long long v = (long long)r.v[0] + (long long)b.v[b.pos--];
		//			if (v >= MAX_VAR) {
		//				r.v[0] = (v - MAX_VAR) & 0xFFFFFFFF;
		//				long long u = r.v[r.pos] + 1;
		//				if (u >= MAX_VAR) {
		//					r.v[r.pos] = (u - MAX_VAR) & 0xFFFFFFFF;
		//					r.v[++r.pos] = 1;
		//				} else {
		//					r.v[r.pos] = u & 0xFFFFFFFF;
		//				} 
		//			} else {
		//				r.v[0] = v & 0xFFFFFFFF;
		//			}
		//		}
		//		b.pos = bpos;
		//	}
		//}
		// 
		//int top = r.v[r.pos--];
		//if (top > 0) {
		//	printf("%d", top);
		//	while (r.pos >= 0) {
		//		printf("%010d", r.v[r.pos--]);
		//	}
		//} else {
		//	printf("%d", r.v[0]);
		//}
		//
		//printf("\n");
		a.clr();
		while (scanf("%c", &c) == 1) {
			if (c == ' ' || c == '\r' || c == '\n') break;
			c -= '0';
			a.push_back(c);
		}

		b.clr();
		while (scanf("%c", &c) == 1) {
			if (c == ' ' || c == '\r' || c == '\n') break;
			c -= '0';
			b.push_back(c);
		}

		res.clr();
		res.push_back(0);
		for (int i = a.size() - 1; i >= 0; i--) {
			for (int j = 0; j < a[i]; j++) {
				for (int k = b.size() - 1; k >= 0; k--) {
					char r = res[res.size() - 1] + b[k];
					if (r < 10) {
						res[res.size() - 1] = r;
					} else {
						res.push_back(b[k]);
					}
				}
			}
		}

		for (int i = res.size() - 1; i >= 0; i--) {
			printf("%d", res[i]);
		}
		printf("\n");
	}

	return 0;
}

