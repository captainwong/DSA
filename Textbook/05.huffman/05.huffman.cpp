// 05.huffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/huffman.h"
#include "../../include/util/util.h"

using namespace dtl;


int main()
{
	auto sample_text_file = "../../_input/Huffman/huffman-text-0.txt";
	auto msg = "Hellow World!";

	auto freq = huffman::statistics(sample_text_file);
	auto forest = huffman::initForest(freq); release(freq);
	auto tree = huffman::generateTree(forest); release(forest);
	print(tree);

	auto table = huffman::generateTable(tree);
	for (int i = 0; i < huffman::PRINTABLE_RANGE; i++) {
		printf(" %c: %s\n", i + huffman::PRINTABLE_MIN, *(table->get(i + huffman::PRINTABLE_MIN)));
	}

	auto test = [&table, &tree](const char* msg) {
		printf("\nEncoding: %s\n", msg);
		auto bmp = new Bitmap();
		int n = huffman::encode(table, bmp, msg);
		printf("%s\n", bmp->toString(n));
		printf("Decoding: ");
		huffman::decode(tree, bmp, n);
		release(bmp);
	};

	test(msg);

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
