#include "../../include/dtl/stack.h"
#include <stdio.h>

// check if B is A's stack permutation
// A: [0,n), top to base
// B: [0,n), top to base
bool isStackPermutation(int* A, int an, int* B, int bn)
{
	dtl::Stack<int> s;
	for (int k = 0; k < bn; k++) { // 通过迭代，从B的栈顶开始依次检查每个元素
		for (int i = 0; s.empty() || B[k] != s.top(); i++) { // 只要B[k]仍未出现在S栈顶
			if (i < an) { // 就从栈A取出顶元素，并随即压入栈S
				s.push(A[i]); // 只要B的确不含任何禁形，则以上迭代就不可能导致A的溢出
			} else { 
				return false; // 反之，若A已溢出，则B必然包含禁形
			}
		}
		if (s.empty() || s.top() != B[k]) { // 以上迭代退出时，S必然非空，且S栈顶元素就是B[k]
			return false;
		}
		s.pop();
	}
	return s.empty();
}

int main()
{
	int A[4] = { 1,2,3,4 };
	int B[4] = { 3,1,2,4 };
	printf("%d", isStackPermutation(A, 4, B, 4));
}
