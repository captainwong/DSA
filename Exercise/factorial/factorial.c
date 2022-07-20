#include <stdio.h>


void print_factorial(int n)
{
	if (n < 0 || n > 1000) { printf("Invalid input");  return; }
	int arr[1024] = { 0 };
	int count = 1;
	arr[0] = 1;
	for (int i = 2; i <= n; i++) {
		int carry = 0;
		for (int j = 0; j < count; j++) {
			int m = arr[j] * i + carry;
			arr[j] = m % 10000;
			carry = m / 10000;
		}
		if (carry > 0) {
			arr[count++] = carry;
		}
	}
	printf("%d", arr[count - 1]);
	for (int i = count - 2; i >= 0; i--) {
		printf("%04d", arr[i]);
	}
	printf("\n");
}


int main()
{
	print_factorial(0);
	print_factorial(1000);
}
