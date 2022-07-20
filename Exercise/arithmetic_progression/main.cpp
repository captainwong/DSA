#include "../testcase.h"


int sum(int n) {
	int s = 0;
	return (1 + n) * n / 2;
}

int main()
{
	system("mkdir testcase");

	if (0) {
		for (int i = 1; i < 10; i++) {
			gen_in_out(i,
					   [i](FILE* f) {
						   fprintf(f, "%d", i);
					   },
					   [i](FILE* f) {
						   fprintf(f, "%d", i);
					   });
		}
	}

	system("cd testcase && del *.in *.out testcase.zip && cd ..");

	int arr[] = { 50,100, 1000, 222,333,10000 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		gen_in_out(i + 1, 
				   [i, arr](FILE* f) {
					   fprintf(f, "%d", arr[i]);
				   },
				   [i, arr](FILE* f) {
					   fprintf(f, "%d", sum(arr[i]));
				   });
	}

	system("cd testcase && zip testcase.zip *.in *.out");
}
