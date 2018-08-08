#include <iostream>

static inline bool is_valid_value(int val)
{
	return val >= 1 && val <= 10000000;
}

int main2(int argc, char* argv[])
{
	int a = 0;
	int b = 0;
	//std::cout << "Enter 2 positive integers:" << std::endl;
	std::cin >> a >> b;
	if (!is_valid_value(a) || !is_valid_value(b)) {
		std::cout << "You must input 2 positive integers." << std::endl;
	} else {
		std::cout << a + b << std::endl;
	}
	return 0;
}