#pragma once

#include "bitmap.h"
#include "bintree.h"
#include "list.h"
#include "hashtable.h"


namespace dtl
{
namespace huffman
{

//! �ɴ�ӡ�ַ� [0x20, 0x80)
static constexpr auto PRINTABLE_MIN = 0x20;
static constexpr auto PRINTABLE_MAX = 0x80;
static constexpr auto PRINTABLE_RANGE = PRINTABLE_MAX - PRINTABLE_MIN;
static bool isPrintable(char c) { return PRINTABLE_MIN <= c && c < PRINTABLE_MAX; }

//! Huffman�������ַ�
struct HuffChar
{
	char ch;
	int weight;

	HuffChar(char c = '^', int w = 0)
		: ch(c)
		, weight(w)
	{}

	bool operator<(const HuffChar& rhs) const { return weight > rhs.weight; }
	bool operator>(const HuffChar& rhs) const { return weight < rhs.weight; }
	bool operator==(const HuffChar& rhs) const { return weight == rhs.weight; }
	bool operator!=(const HuffChar& rhs) const { return weight != rhs.weight; }
};


typedef BinTree<HuffChar> HuffTree;
typedef List<HuffTree*> HuffForest;
typedef Hashtable<char, char*> HuffTable;


//! ͳ���ַ�����Ƶ��
static int* statistics(const char* sample_text_file)
{
	int* freq = new int[PRINTABLE_RANGE];
	memset(freq, 0, sizeof(int) * PRINTABLE_RANGE);
	auto f = fopen(sample_text_file, "r");
	for (char ch; 0 < fscanf(f, "%c", &ch);) {
		if (isPrintable(ch)) {
			freq[ch - PRINTABLE_MIN]++;
		}
	}
	fclose(f);
	return freq;
}

//! ��ʼ��Huffmanɭ��
static HuffForest* initForest(int* freq)
{
	auto forest = new HuffForest();
	for (int i = 0; i < PRINTABLE_MAX; i++) {
		auto tree = new HuffTree();
		tree->insertAsRootNode(HuffChar(PRINTABLE_MIN + i, freq[i]));
		forest->insert_as_last(tree);
	}
	return forest;
}

//! Huffman�����㷨 O(n^2)
static HuffTree* generateTree(HuffForest* forest)
{
	//! ��Huffmanɭ�����ҳ�Ȩ����С�ģ������ַ�, O(n)
	static auto minHuffChar = [](HuffForest* forest)
	{
		auto p = forest->first();
		auto minChar = p;
		int minWeight = p->data->root()->data_.weight;
		while (forest->valid(p = p->succ)) {
			if (minWeight > p->data->root()->data_.weight) {
				minWeight = p->data->root()->data_.weight;
				minChar = p;
			}
		}
		return forest->remove(minChar);
	};

	while (1 < forest->size()) {
		auto t1 = minHuffChar(forest);
		auto t2 = minHuffChar(forest);
		auto s = new HuffTree();
		s->insertAsRootNode(HuffChar('^', t1->root()->data_.weight + t2->root()->data_.weight));
		s->attachAsLChild(s->root(), t1);
		s->attachAsRChild(s->root(), t2);
		forest->insert_as_last(s);
	}
	return forest->first()->data;
}

//! ͨ��������ȡ���ַ��ı���
static void generateCT(Bitmap* bmp, int length, HuffTable* table, HuffTree::NodePtr v)
{
	if (v->isLeaf()) {
		table->put(v->data_.ch, bmp->toString(length));
		return;
	}

	if (v->hasLChild()) {
		bmp->clear(length);
		generateCT(bmp, length + 1, table, v->lChild_);
	}

	if (v->hasRChild()) {
		bmp->set(length);
		generateCT(bmp, length + 1, table, v->rChild_);
	}
};

//! ���ɱ���������ַ�����ͳһ������ɢ�б�ʵ�ֵı�����У�
static HuffTable* generateTable(HuffTree* tree)
{
	auto table = new HuffTable();
	Bitmap bmp;
	generateCT(&bmp, 0, table, tree->root());
	return table;
}

//! ���ձ�����bitmap������
static int encode(HuffTable* table, Bitmap* bmp, const char* plain_text)
{
	int n = 0;
	for (size_t m = strlen(plain_text), i = 0; i < m; i++) {
		char** pCharCode = table->get(plain_text[i]);
		if (!pCharCode) {
			pCharCode = table->get(plain_text[i] + 'A' - 'a');
		}
		if (!pCharCode) {
			pCharCode = table->get(' ');
		}
		printf("%s", *pCharCode);
		for (size_t mm = strlen(*pCharCode), j = 0; j < mm; j++) {
			'1' == *(*pCharCode + j) ? bmp->set(n++) : bmp->clear(n++);
		}
	}
	printf("\n");
	return n;
}

//! ���ݱ������Գ�Ϊn��bitmap����Huffman����
static void decode(HuffTree* tree, Bitmap* bmp, int n)
{
	auto x = tree->root();
	for (int i = 0; i < n; i++) {
		x = bmp->test(i) ? x->rChild_ : x->lChild_;
		if (x->isLeaf()) {
			printf("%c", x->data_.ch);
			x = tree->root();
		}
	}
	if (x != tree->root()) {
		printf("...");
	}
	printf("\n");
}

}
}
