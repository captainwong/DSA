#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "max_.h"
#include "lcs.h"


// 只能演示lcs<10的情况
void print_dp(int** dp, int len1, int len2, const char* s1, const char* s2) 
{
	system("cls");
	printf("    ");
	for (int i = 1; i < len2; i++) {
		printf(" %c", s2[i - 1]);
	}
	printf("\n");

	for (int i = 0; i < len1; i++) {		
		printf("%c ", i == 0 ? ' ' : s1[i - 1]);
		for (int j = 0; j < len2; j++) {
			printf(" %c", dp[i][j]);
		}
		
		printf("\n");
	}
	printf("\n");
}

// 只能计算lcs<10的情况
int lcs(const char* s1, const char* s2)
{
	int len1 = strlen(s1) + 1;
	int len2 = strlen(s2) + 1;
	int** dp = (int**)malloc(len1 * sizeof(int*));
	for (int i = 0; i < len1; i++) {
		dp[i] = (int*)malloc(len2 * sizeof(int));
		memset(dp[i], ' ', len2 * sizeof(int));
	}

	for (int i = 0; i < len1; i++) {
		dp[i][0] = '0';
	}
	for (int i = 0; i < len2; i++) {
		dp[0][i] = '0';
	}
	print_dp(dp, len1, len2, s1, s2);

	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				char lu = dp[i - 1][j - 1];
				dp[i][j] = lu + 1;
			} else {
				char l = dp[i - 1][j]; 
				char u = dp[i][j - 1];
				dp[i][j] = max(l, u);
			}
			print_dp(dp, len1, len2, s1, s2);
		}
	}

	return dp[len1-1][len2-1] - '0';
}

void demonstrate_lcs()
{
	//int ret = lcs("program", "algorithm");
	int ret = lcs("advantage", "didactical");
	printf("lcs=%d\n", ret);

}

int main(int argc, char* argv[])
{
	/*char s1[] = "program";
	char s2[] = "algorithm";
	int ret = lcs_recursive(s1, strlen(s1) - 1, s2, strlen(s2) - 1);*/

	demonstrate_lcs();
	
	return 0;
}