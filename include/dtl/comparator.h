#pragma once

template <typename T>
static bool lt(T* a, T* b) {
	return lt(*a, *b);
}

template <typename T>
static bool lt(T& a, T& b) {
	return a < b;
}

template <typename T>
static bool eq(T* a, T* b) {
	return eq(*a, *b);
}

template <typename T>
static bool eq(T& a, T& b) {
	return a == b;
}

