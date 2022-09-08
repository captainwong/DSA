#include "../../include/dtl/stack.h"
#include <stdio.h>

// check if B is A's stack permutation
// A: [0,n), top to base
// B: [0,n), top to base
bool isStackPermutation(int* A, int an, int* B, int bn)
{
	dtl::Stack<int> s;
	for (int k = 0; k < bn; k++) { // ͨ����������B��ջ����ʼ���μ��ÿ��Ԫ��
		for (int i = 0; s.empty() || B[k] != s.top(); i++) { // ֻҪB[k]��δ������Sջ��
			if (i < an) { // �ʹ�ջAȡ����Ԫ�أ����漴ѹ��ջS
				s.push(A[i]); // ֻҪB��ȷ�����κν��Σ������ϵ����Ͳ����ܵ���A�����
			} else { 
				return false; // ��֮����A���������B��Ȼ��������
			}
		}
		if (s.empty() || s.top() != B[k]) { // ���ϵ����˳�ʱ��S��Ȼ�ǿգ���Sջ��Ԫ�ؾ���B[k]
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
