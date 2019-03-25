// 1.2.island.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/** 
* @brief ���սⷨ������
* @param d1 ���ȴ��
* @param d2 ǰ��ȴ��
* @param d ���
* @param h ���
* @return ����
*/
float islandHeight(float d1, float d2, float d, float h)
{
	auto fa = d1 - d2; // ��ȥ�����Ϊ��࣬��Ϊ��
	auto shi = d * h; // ǰ�����ȥΪ��䣬�Ա�߳�֮Ϊʵ
	return shi / fa + h; // �Է���֮���ӱ�ߣ����ǵ��߻���
}

/**
* @brief ���սⷨ��ǰ��������������
* @param d1 ���ȴ��
* @param d2 ǰ��ȴ��
* @param d ���
* @return ǰ��������������
*/
float islandDistance(float d1, float d2, float d)
{
	auto shi = d2 * d; // ǰȥ��˱��
	auto fa = d1 - d2; // �����Ϊ��
	return shi / fa; // ��֮
}

int main()
{
	float d1 = 127.0;
	float d2 = 123.0;
	float d = 1000;
	float h = 3;

	auto height = islandHeight(d1, d2, d, h); // 753��
	auto distance = islandDistance(d1, d2, d); // 30750��

	printf("���� %d ��, ��ȥ�� %d ��", static_cast<int>(height), static_cast<int>(distance));
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
