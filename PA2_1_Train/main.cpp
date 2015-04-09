#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"
#include "queue.h"


int B[1600001] = { 0 };
bool g_op[1600001 * 2] = { false };

int main(int argc, char* argv[])
{
	int n, m;
	if (scanf("%d %d", &n, &m) != 2)
		return 0;

	for (int i = 0; i < n; i++) {
		if (scanf("%d", &B[i]) != 1)
			return 0;
	}

	Stack<int> S;
	int op_size = 0;
	for (int i = 0, j = 1; i < n; i++) {
		while (S.empty() || B[i] != S.top()) {
			if (j > n || S.size() == m) {
				printf("No\n");
				return 0;
			}
			S.push(j++);
			g_op[op_size++] = false;
		}

		if (S.empty() || B[i] != S.top()) {
			printf("No\n");
			return 0;
		}

		S.pop();
		g_op[op_size++] = true;
	}

	if (!S.empty()) {
		printf("No\n");
		return 0;
	}

	const char *op_string[] = {
		"push\n",
		"pop\n",
	};

	for (int i = 0; i < op_size; i++) {
		printf(op_string[g_op[i]]);
	}

	return 0;
}
