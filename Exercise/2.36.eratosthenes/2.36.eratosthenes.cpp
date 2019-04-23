// 2.36.eratosthenes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/prime.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
#include <vector>
#include <time.h>
/*****************/

// 计算不大于10^8的所有素数（埃拉托斯特尼筛法）
// https://zh.wikipedia.org/zh-cn/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95
std::vector<int> eratosthenes_to_vec(int n)
{
	std::vector<int> primes;

	Bitmap bmp;
	eratosthenes(n, bmp);

	for (int i = 2; i < n; i++) {
		if (!bmp.test(i)) {
			primes.push_back(i);
		}
	}

	return primes;
}

int main()
{
	eratosthenes_to_file(1048576, "../../_input/prime-1048576-bitmap.txt");

	printf("cacl 1000...\n");
	auto t = clock();
	auto ret = eratosthenes_to_vec(1000);
	printf("cacl 1000 elapsed %lf ms, primes are:\n", (clock() - t) * 1000.0 / CLOCKS_PER_SEC);
	for (auto p : ret) {
		printf("%d ", p);
	}
	printf("\n");

	printf("cacl 1000000...\n");
	t = clock();
	ret = eratosthenes_to_vec(1000000);
	printf("cacl 1000000 elapsed %lf ms\n", (clock() - t) * 1000.0 / CLOCKS_PER_SEC);
	printf("\n");

	printf("cacl 100000000...\n");
	t = clock();
	ret = eratosthenes_to_vec(100000000);
	printf("cacl 100000000 elapsed %lf ms\n", (clock() - t) * 1000.0 / CLOCKS_PER_SEC);
	printf("\n");

}


/*******测试结果******/

/*

cacl 1000...
cacl 1000 elapsed 1.000000 ms, primes are:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 
167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 
347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 
523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 
727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 
937 941 947 953 967 971 977 983 991 997

cacl 1000000...
cacl 1000000 elapsed 447.000000 ms

cacl 100000000...
cacl 100000000 elapsed 43098.000000 ms

*/






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
