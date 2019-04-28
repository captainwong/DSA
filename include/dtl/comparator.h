#pragma once

namespace dtl
{

// less than
template <typename T>
static bool lt(T* a, T* b) {
	return lt(*a, *b);
}

// less than
template <typename T>
static bool lt(T& a, T& b) {
	return a < b;
}

// equal
template <typename T>
static bool eq(T* a, T* b) {
	return eq(*a, *b);
}

// equal
template <typename T>
static bool eq(T& a, T& b) {
	return a == b;
}

}
