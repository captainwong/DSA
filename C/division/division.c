/*
https://pintia.cn/problem-sets/14/problems/2990

7-37 整数分解为若干项之和
分数 20
作者 DS课程组
单位 浙江大学
将一个正整数N分解成几个正整数相加，可以有多种分解方法，例如7=6+1，7=5+2，7=5+1+1，…。
编程求出正整数N的所有整数分解式子。

输入格式：
每个输入包含一个测试用例，即正整数N (0<N≤30)。

输出格式：
按递增顺序输出N的所有整数分解式子。递增顺序是指：
对于两个分解序列N1 ={n1,n2,⋯}和N2={m1,m2,⋯}，
若存在i使得n1=m1,⋯,ni=mi，但是ni+1<mi+1,
则N1序列必定在N2序列之前输出。
每个式子由小到大相加，式子间用分号隔开，且每输出4个式子后换行。

输入样例：
7

输出样例：
7=1+1+1+1+1+1+1;7=1+1+1+1+1+2;7=1+1+1+1+3;7=1+1+1+2+2
7=1+1+1+4;7=1+1+2+3;7=1+1+5;7=1+2+2+2
7=1+2+4;7=1+3+3;7=1+6;7=2+2+3
7=2+5;7=3+4;7=7

代码长度限制16 KB
时间限制800 ms
内存限制64 MB
*/

#ifdef _MSC_VER // 当前编译器是否为 Visual Studio
#define _CRT_SECURE_NO_WARNINGS // 只有在 Visual Studio 下才需要定义此宏
#endif

#include <stdio.h>
#include <stdlib.h>

#define ver 3



#if ver == 4

#elif ver == 3

int s[32];
int t = -1;
int sum = 0;
int count = 0;
int N;

void print()
{
	printf("%d=", N);
	for (int i = 0; i <= t; i++) {
		printf("%s%d", i == 0 ? "" : "+", s[i]);
	}
	printf("%s", (++count % 4 == 0 || s[t] == N) ? "\n" : ";");
}

void dfs(int i)
{
	int d[32] = { 0 };
	int dt = -1;
	for (int i = N; i > 0; i--) {
		d[++dt] = i;
	}
	//d[++dt] = 1;

	int rewhile = 0;
	while (dt >= 0) {
		int begin = d[dt];
		if (!rewhile) {
			dt--;
		}
		for (int j = begin; j <= N; j++) {
			s[++t] = j;
			sum += j;
			if (sum == N) {
				print();
			} else if (sum < N) {
				d[++dt] = j;
				rewhile = 1;
				break;
			}
			t--;
			sum -= j;
		}
		if (rewhile) {
			continue;
		}


	}


	
	for (int j = i; j <= N; j++) {
		s[++t] = j;
		sum += j;
		if (sum == N) {
			print();
		} else if (sum < N) {
			dfs(j);
		}
		t--;
		sum -= j;
	}
}

int main()
{
	N = 7;

	dfs(1);
}

#elif ver == 2

typedef struct Context {
	int stack[32];
	int top;
	int base;
	int N;
	int sum;
	int lines;
}Context;

void print(Context* ctx) {
	printf("%d=", ctx->N);
	for (int i = 0; i <= ctx->top; i++) {
		printf("%s%d", i == 0 ? "" : "+", ctx->stack[i]);
	}
	if (++ctx->lines % 4 == 0 || ctx->stack[ctx->top] == ctx->N) {
		printf("\n");
	} else {
		printf(";");
	}
}

int main()
{
	Context ctx;
	ctx.base = -1;
	ctx.top = -1;
	ctx.sum = 0;
	ctx.lines = 0;
	ctx.stack[0] = 0;
	//scanf("%d", &ctx.N);
	ctx.N = 3;
	int begin = 1;

	while (1) {
		for (int i = begin; i <= ctx.N; i++) {
			ctx.stack[++ctx.top] = i;
			ctx.sum += i;
			if (ctx.sum == ctx.N) {
				print(&ctx);
				ctx.top--;
				ctx.sum -= i;
			} else if (ctx.sum < ctx.N) {
				begin = i;
				break;
			} else {
				ctx.top--;
				ctx.sum -= i;
				break;
			}
		}
	}

	while (ctx.stack[0] != ctx.N) {

	}

	for (int i = 1; i <= ctx.N; i++) {
		ctx.stack[++ctx.top] = 1;
		ctx.sum += i;
		if (ctx.sum < ctx.N) {

		}
	}
	ctx.sum = ctx.N;

	while (ctx.top >= 0) {
		if (ctx.sum == ctx.N) {
			print(&ctx);
			ctx.sum -= ctx.stack[ctx.top--];
			ctx.base = ctx.top;
			ctx.stack[ctx.top]++;
			ctx.sum++;
		} else if (ctx.sum < ctx.N) {
			ctx.stack[++ctx.top] = 1;
			ctx.sum++;
		} else {
			ctx.sum -= ctx.stack[ctx.top--];
		}
	}

}

#elif ver == 1

typedef struct Context {
	int stack[32];
	int top;
	int N;
	int sum;
	int lines;
}Context;

void print(Context* ctx) {
	printf("%d=", ctx->N);
	for (int i = 0; i <= ctx->top; i++) {
		printf("%s%d", i == 0 ? "" : "+", ctx->stack[i]);
	}
	if (++ctx->lines % 4 == 0 || ctx->stack[ctx->top] == ctx->N) {
		printf("\n");
	} else {
		printf(";");
	}
}

void division(Context* ctx, int begin)
{
	for (int i = begin; i <= ctx->N; i++) {
		ctx->stack[++ctx->top] = i;
		ctx->sum += i;
		if (ctx->sum == ctx->N) {
			print(ctx);
			ctx->top--;
			ctx->sum -= i;
			return;
		} else if (ctx->sum < ctx->N) {
			division(ctx, i);
			ctx->top--;
			ctx->sum -= i;
		} else {
			ctx->top--;
			ctx->sum -= i;
			return;
		}
	}
}

int main()
{
	Context ctx;
	ctx.top = -1;
	ctx.sum = 0;
	ctx.lines = 0;
	//scanf("%d", &ctx.N);
	ctx.N = 7;
	division(&ctx, 1);

}

#endif
