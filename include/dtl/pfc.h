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


	//! 创建编码树森林
	static PFCForest* initForest() {
		auto forest = new PFCForest();
		for (int i = 0; i < (0x80 - 0x20); i++) { // 可打印字符 [0x20, 0x80)
			auto tree = new PFCTree();
			tree->insertAsRootNode(0x20 + i);
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
			
		}
	}

	//! 由编码树转换为编码表
	static PFCTable* generateTable(PFCTree* tree);

	//! 明文的编码，返回编码长度
	static int encode(PFCTable* table, Bitmap& bmp, const char* plain_text);

	//! 二进制串的解码
	static void decode(PFCTree* tree, Bitmap& bmp, int);

}

}
