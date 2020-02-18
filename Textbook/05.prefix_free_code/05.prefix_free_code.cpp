// 05.prefix_free_code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/util/util.h"
#include "../../include/dtl/pfc.h"

using namespace dtl;


int main()
{
	auto forest = PFC::initForest(); //print(forest);
	auto tree = PFC::generateTree(forest); 
	release(forest);
	print<BinTree<char>>(tree);
	auto table = PFC::generateTable(tree);
	for (int i = 0; i < PFC::PRINTABLE_RANGE; i++) {
		printf(" %c: %s\n", i + PFC::PRINTABLE_MIN, *(table->get(i + PFC::PRINTABLE_MIN)));
	}

	auto msg = "Hello world!";
	printf("\nEncoding: %s\n", msg);

	Bitmap bmp;
	int n = PFC::encode(table, bmp, msg);
	printf("%s\n", bmp.toString(n));
	printf("Decoding: ");
	PFC::decode(tree, bmp, n);

	release(table);
	release(tree);

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
