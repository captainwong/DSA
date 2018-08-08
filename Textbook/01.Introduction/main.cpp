#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "max_.h"
#include "lcs.h"

int main(int argc, char* argv[])
{
	char s1[] = "program";
	char s2[] = "algorithm";
	int ret = lcs_recursive(s1, strlen(s1) - 1, s2, strlen(s2) - 1);
	
	return 0;
}