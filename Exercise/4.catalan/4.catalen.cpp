#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ver2
#include <string>
#include <vector>
#include <algorithm>
// ver2--end


namespace ver1 {

#define MAX_N 1024

typedef unsigned long long ull;
ull a[MAX_N * 2 + 1] = { 0 };

ull catalan(ull n)
{
	a[0] = a[1] = 1;
	for (ull i = 2; i <= 2 * n; i++) {
		a[i] = a[i - 1] * i;
	}
	return a[2 * n] / a[n + 1] / a[n];
}

void print_catalan(ull n)
{
	a[0] = a[1] = 1;
	for (ull i = 2; i <= 2 * n; i++) {
		a[i] = a[i - 1] * i;
	}

	for (ull i = 1; i <= n; i++) {
		printf("catalan(%llu)=%llu\n", i, a[2 * i] / a[i + 1] / a[i]);
	}

}

}


// TODO
namespace ver2 {

// 无符号大整数
struct BigUNumber {
	static constexpr int BASE = 10000;
	std::vector<int> v{};

	BigUNumber(int n = 0) {
		if (n == 0) {
			v.push_back(0);
			return;
		}
		
		while (n > BASE) {
			v.push_back(n % BASE);
			n /= BASE;
		}
		std::reverse(v.begin(), v.end());
	}

	std::string toString() const {
		std::string s = std::to_string(v[0]);
		char buf[5];
		for (size_t i = 1; i < v.size(); i++) {
			sprintf(buf, "%04d", v[i]);
			s += buf;
		}
		return s;
	}



	BigUNumber& operator+=(const BigUNumber& rhs) {

	}
};

}

int main()
{
	//printf("catalan(%d)=%d\n", 4, catalan(4));

	ver1::print_catalan(10);
}
