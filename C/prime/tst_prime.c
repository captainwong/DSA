#include <stdio.h>
#include "prime.h"

int main()
{
	for (int i = 0; i < 0xFFFF; ) {
		//i = next_prime(i);
		i = next_4kp3_prime(i);
		printf("%d ", i);
	}
}
