/*
https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1145

�г�����(Train)
Description
Figure 1 shows the structure of a station for train dispatching.


https://dsa.cs.tsinghua.edu.cn/oj/attachment/03bc/03bc70595803464554b5f6b69a21962beb038264.png
Figure 1

In this station, A is the entrance for each train and B is the exit. S is the transfer end. All single tracks are one-way, which means that the train can enter the station from A to S, and pull out from S to B. Note that the overtaking is not allowed. Because the compartments can reside in S, the order that they pull out at B may differ from that they enter at A. However, because of the limited capacity of S, no more that m compartments can reside at S simultaneously.

Assume that a train consist of n compartments labeled {1, 2, ��, n}. A dispatcher wants to know whether these compartments can pull out at B in the order of {a1, a2, ��, an} (a sequence). If can, in what order he should operate it?

Input
Two lines:

1st line: two integers n and m;

2nd line: n integers separated by spaces, which is a permutation of {1, 2, ��, n}. This is a compartment sequence that is to be judged regarding the feasibility.

Output
If the sequence is feasible, output the sequence. ��Push�� means one compartment goes from A to S, while ��pop�� means one compartment goes from S to B. Each operation takes up one line.

If the sequence is infeasible, output a ��no��.

Example 1
Input

5 2
1 2 3 5 4
Output

push
pop
push
pop
push
pop
push
push
pop
pop
Example 2
Input

5 5
3 1 2 4 5
Output

No
Restrictions
1 <= n <= 1,600,000

0 <= m <= 1,600,000

Time: 2 sec

Memory: 256 MB

����
ĳ�г�����վ���������ӽṹ��Figure 1��ʾ��

���У�AΪ��ڣ�BΪ���ڣ�SΪ��תä�ˡ�����������Ϊ���쵥��ʽ���г���ʻ�ķ���ֻ���Ǵ�A��S���ٴ�S��B�����⣬������������Ϊ�������S��פ�����������Ǵ�B��ʻ���Ĵ��򣬿������A��ʻ��Ĵ���ͬ������S���������ޣ�ͬʱפ���ĳ��᲻�ó���m�ڡ�

��ĳ�г��ɱ������Ϊ{1, 2, ..., n}��n�ڳ�����ɡ�����Աϣ��֪�����������Ͻ�ͨ������Щ�����ܷ���{a1, a2, ..., an}�Ĵ����������к��B��ʻ����������У�Ӧ��������

�Ĵ������?

����
�����С�

��һ��Ϊ��������n��m��

�ڶ���Ϊ�Կո�ָ���n����������֤Ϊ{1, 2, ..., n}��һ�����У���ʾ���жϿ����Ե�ʻ������{a1��a2��...��an}��

���
��ʻ�����п��У�������������У�����push��ʾ�����A����S��pop��ʾ�����S����B��ÿ������ռһ�С�

�������У������No��

����
��Ӣ������

����
1 �� n �� 1,600,000

0 �� m �� 1,600,000

ʱ�䣺2 sec

�ռ䣺256 MB

*/


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
