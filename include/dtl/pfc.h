#pragma once

#include "../util/rand.h"
#include "bintree.h"
#include "vector.h"
#include "bitmap.h"
#include "skiplist.h"

namespace dtl
{

//! prefix-free code 前缀无歧义编码
namespace PFC
{
	//! 使用BinTree实现PFC树
	typedef BinTree<char> PFCTree;

	//! 使用Vector实现PFC森林
	typedef Vector<PFCTree*> PFCForest;

	//! 使用Skiplist词典结构实现PFC编码表，词条格式：key=字符，value=编码串
	typedef Skiplist<char, char*> PFCTable;

	//! 可打印字符 [0x20, 0x80)
	static constexpr auto PRINTABLE_MIN = 0x20;
	static constexpr auto PRINTABLE_MAX = 0x80;
	static constexpr auto PRINTABLE_RANGE = PRINTABLE_MAX - PRINTABLE_MIN;


	//! 创建编码树森林
	static PFCForest* initForest() {
		auto forest = new PFCForest(PRINTABLE_RANGE);
		for (int i = 0; i < PRINTABLE_RANGE; i++) {
			auto tree = new PFCTree();
			tree->insertAsRootNode(PRINTABLE_MIN + i);
			forest->insert(i, tree);
		}
		return forest;
	}

	//! 构造编码树
	static PFCTree* generateTree(PFCForest* forest) {
		srand_time();
		while (1 < forest->size()) {
			auto tree = new PFCTree();
			tree->insertAsRootNode('^');
			auto r1 = rand() % forest->size();
			tree->attachAsLChild(tree->root(), forest->operator[](r1));
			forest->remove(r1);
			auto r2 = rand() % forest->size();
			tree->attachAsRChild(tree->root(), forest->operator[](r2));
			forest->remove(r2);
			forest->insert(forest->size(), tree);
		}
		return forest->operator[](0);
	}

	//! 通过遍历获取各字符的编码
	static void generateCT(Bitmap* code, int length, PFCTable* table, BinNode<char>* v) {
		if (v->isLeaf()) {
			table->put(v->data_, code->toString(length));
			return;
		}

		if (v->hasLChild()) {
			code->clear(length);
			generateCT(code, length + 1, table, v->lChild_);
		}

		if (v->hasRChild()) {
			code->set(length);
			generateCT(code, length + 1, table, v->rChild_);
		}
	};

	//! 由编码树转换为编码表
	static PFCTable* generateTable(PFCTree* tree) {
		auto table = new PFCTable();
		auto code = new Bitmap();
		generateCT(code, 0, table, tree->root());
		release(code);
		return table;
	}

	//! 明文的编码，返回编码长度
	static int encode(PFCTable* table, Bitmap& bmp, const char* plain_text) {
		int n = 0;
		for (size_t m = strlen(plain_text), i = 0; i < m; i++) {
			char** pCharCode = table->get(plain_text[i]);
			if (!pCharCode) {
				pCharCode = table->get(plain_text[i] + 'A' - 'a');
			}
			if (!pCharCode) { // 无法识别的字符统一视作空格
				pCharCode = table->get(' ');
			}
			printf("%s", *pCharCode);
			for (size_t mm = strlen(*pCharCode), j = 0; j < mm; j++) {
				'1' == *(*pCharCode + j) ? bmp.set(n++) : bmp.clear(n++);
			}
			printf("\n");
		}
		return n;
	}

	//! 二进制串的解码
	static void decode(PFCTree* tree, Bitmap& bmp, int n) {
		auto x = tree->root();
		for (int i = 0; i < n; i++) {
			x = bmp.test(i) ? x->rChild_ : x->lChild_;
			if (x->isLeaf()) {
				printf("%c", x->data_);
				x = tree->root();
			}
		}
		if (x != tree->root()) {
			printf(" code seems to be incomplete ...");
		}
		printf("\n");
	}

}

}
