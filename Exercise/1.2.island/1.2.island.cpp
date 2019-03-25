// 1.2.island.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/** 
* @brief 刘徽解法，岛高
* @param d1 后表却步
* @param d2 前表却步
* @param d 表间
* @param h 表高
* @return 岛高
*/
float islandHeight(float d1, float d2, float d, float h)
{
	auto fa = d1 - d2; // 二去表相减为相多，以为法
	auto shi = d * h; // 前后表相去为表间，以表高乘之为实
	return shi / fa + h; // 以法除之，加表高，即是岛高积步
}

/**
* @brief 刘徽解法，前立柱至海岛距离
* @param d1 后表却步
* @param d2 前表却步
* @param d 表间
* @return 前立柱至海岛距离
*/
float islandDistance(float d1, float d2, float d)
{
	auto shi = d2 * d; // 前去表乘表间
	auto fa = d1 - d2; // 以相多为法
	return shi / fa; // 除之
}

int main()
{
	float d1 = 127.0;
	float d2 = 123.0;
	float d = 1000;
	float h = 3;

	auto height = islandHeight(d1, d2, d, h); // 753丈
	auto distance = islandDistance(d1, d2, d); // 30750步

	printf("岛高 %d 丈, 岛去表 %d 步", static_cast<int>(height), static_cast<int>(distance));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
