#pragma once

class Fibnacci
{
private:
	int f, g;

public:
	explicit Fibnacci(int n) {
		f = 1;
		g = 0;
		while (g < n) {
			next();
		}
	}

	int get() const { return g; }

	int next() {
		g += f;
		f = g - f;
		return g;
	}

	int prev() {
		f = g - f;
		g -= f;
		return g;
	}
};
