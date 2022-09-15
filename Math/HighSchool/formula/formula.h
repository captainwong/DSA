#pragma once

// (a+b+c)^2 = a^2 + b^2 + c^2 + 2ab + 2bc + 2ca
template <typename T = int>
T three_sum_exp2(T a, T b, T c) {
	return a * a + b * b + c * c + 2 * a * b + 2 * b * c + 2 * c * a;
}

// a^3 + b^3 = (a+b)(a^2 - ab + b^2)
template <typename T = int>
T exp3_add(T a, T b) {
	return (a + b) * (a * a - a * b + b * b);
}

// a^3 - b^3 = (a-b)(a^2 + ab + b^2)
template <typename T = int>
T exp3_sub(T a, T b) {
	return (a - b) * (a * a + a * b + b * b);
}

// (a+b)^3 = a^3 + 3a^2b + 3ab^2 + b^3
template <typename T = int>
T two_sum_exp3(T a, T b) {
	return a * a * a + 3 * a * a * b + 3 * a * b * b + b * b * b;
}

// (a-b)^3 = a^3 - 3a^2b + 3ab^2 - b^3
template <typename T = int>
T two_sub_exp3(T a, T b) {
	return a * a * a - 3 * a * a * b + 3 * a * b * b - b * b * b;
}





