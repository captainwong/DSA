#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <limits>


namespace dtl
{

//! 萃取指针类型，转为引用
template <typename T>
static void print(T* x) { if (x) { print(*x); } else { printf(" <NULL>"); } }

template <typename T>
static void print(T& x) { UniPrint::p(x); }

template <typename T>
static void print(const T& x) { UniPrint::p(x); }

static void print(char* x) { printf(" %s", x ? x : "<NULL>"); }
static void print(const char* x) { printf(" %s", x ? x : "<NULL>"); }

}


#include "../dtl/bitmap.h"
#include "../dtl/vector.h"
#include "../dtl/list.h"
#include "../dtl/queue.h"
#include "../dtl/stack.h"
#include "../dtl/graph_matrix.h"
#include "../dtl/bintree.h"
#include "../dtl/huffman.h"
#include "../dtl/graph_matrix.h"
#include "../dtl/hashtable.h"
#include "../dtl/quadlist.h"
#include "../dtl/skiplist.h"
#include "../dtl/complete_heap.h"
#include "../dtl/left_heap.h"


namespace dtl
{

class UniPrint
{
	enum class TreeNodeType
	{
		R_CHILD = -1,
		ROOT = 0,
		L_CHILD = 1,
	};

	static void p(TreeNodeType t) {
		switch (t) {
			case TreeNodeType::R_CHILD: printf("┌─"); break;
			case TreeNodeType::L_CHILD: printf("└─"); break;
			default:printf("──"); break;
		}
	}

public:
	static void p(int e) { printf(" %4d", e); }
	static void p(char e) { printf(" %c", (31 < e) && (e < 128) ? e : '$'); }
	static void p(float e) { printf(" %4.1f", e); }
	static void p(double e) { printf(" %4.1f", e); }
	
	static void p(VertexStatus e) {
		switch (e) {
			case VertexStatus::undiscovered:	printf("U"); break;
			case VertexStatus::discovered:		printf("D"); break;
			case VertexStatus::visited:			printf("V"); break;
			default:							printf("X"); break;
		}
	}

	static void p(EdgeStatus e) {
		switch (e) {
			case EdgeStatus::undetermined:	printf("U"); break;
			case EdgeStatus::tree:			printf("T"); break;
			case EdgeStatus::cross:			printf("C"); break;
			case EdgeStatus::forward:		printf("F"); break;
			case EdgeStatus::backward:		printf("B"); break;
			default:						printf("X"); break;
		}
	}

	//! 萃取指针类型，统一转为引用
	template <typename T>
	static void p(T* s) { if (s) { p(*s); } else { printf(" <NULL>"); } }

	template <typename K, typename V>
	static void p(Entry<K, V>& e) {
		printf("-<"); print(e.key); printf(":"); print(e.value); printf(">-");
	}


	//! BinNode
	template <typename T>
	static void p(BinNode<T>& node) {
		p(node.data_);
		printf("(%-2d)", node.height_);
		printf(((node.lChild_ && &node != node.lChild_->parent_) ||
				(node.rChild_ && &node != node.rChild_->parent_)
				) ? "@" : " ");
		if (node.color_ == RBColor::RB_BLACK) { printf("B"); }

	}

	//! BinTree
	template <typename T>
	static void p(BinTree<T>& tree) {
		printf("%s[0x%p]*%03d\n", typeid(tree).name(), &tree, tree.size());
		Bitmap bmp;
		printBinTree(tree.root(), -1, TreeNodeType::ROOT, &bmp);
		printf("\n");
	}

	//! 二叉树各种派生类的统一打印
	template <typename T>
	static void printBinTree(BinNode<T>* bt, int depth, TreeNodeType type, Bitmap* bType) {
		if (!bt) { return; }
		if (-1 < depth) {
			type == TreeNodeType::R_CHILD ? bType->set(depth) : bType->clear(depth);
		}
		printBinTree(bt->rChild_, depth + 1, TreeNodeType::R_CHILD, bType);
		print(bt); printf(" *");
		for (int i = -1; i < depth; i++) {
			if ((i < 0) || bType->test(i) == bType->test(i + 1)) {
				printf("      ");
			} else {
				printf("│    ");
			}
		}
		p(type);
		print(bt);
		printf("\n");
		printBinTree(bt->lChild_, depth + 1, TreeNodeType::L_CHILD, bType);
	}

	//! HuffChar
	static void p(huffman::HuffChar& e) {
		printf("[%c]:%-5d", e.ch, e.weight);
	}

	//! 图
	template <typename Tv, typename Te> //顶点类型、边类型
	static void p(GraphMatrix<Tv, Te>& s) { //引用
		int inD = 0; for (int i = 0; i < s.n; i++) inD += s.inDegree(i);
		int outD = 0; for (int i = 0; i < s.n; i++) outD += s.outDegree(i);
		printf("%s[0x%p]*(%d, %d):\n", typeid (s).name(), &s, s.n, s.e); //基本信息
		// 标题行
		print(s.n); printf(" "); print(inD); printf("|");
		for (int i = 0; i < s.n; i++) { print(s.vertex(i)); printf("["); print(s.status(i)); printf("] "); }
		printf("\n");
		// 标题行（续）
		print(outD); printf(" "); print(s.e); printf("|");
		for (int i = 0; i < s.n; i++) { print(s.inDegree(i)); printf(" "); }
		printf("| dTime fTime Parent Weight\n");
		// 水平分隔线
		printf("-----------+"); for (int i = 0; i < s.n; i++) printf("------");
		printf("+----------------------------\n");
		// 逐行输出各顶点
		for (int i = 0; i < s.n; i++) {
			print(s.vertex(i)); printf("["); print(s.status(i)); printf("] "); print(s.outDegree(i)); printf("|");
			for (int j = 0; j < s.n; j++)
				if (s.exists(i, j)) { print(s.edge(i, j)); print(s.type(i, j)); } else printf("     .");
			printf("| "); print(s.dTime(i)); printf(" "); print(s.fTime(i));
			printf("     "); if (0 > s.parent(i)) print("^"); else print(s.vertex(s.parent(i)));
			printf("  "); if (INT_MAX > s.priority(i)) print(s.priority(i)); else print(" INF");
			printf("\n");
		}
		printf("\n");
	}

	//! 四联表
	template <typename T>
	static void p(Quadlist<T>& q) {
		printf("%s[0x%p]*%03d\n", typeid(q).name(), &q, q.size());
		if (q.empty()) { printf("\n"); return; }
		auto curr = q.first()->pred; // 当前层之header
		auto base = q.first(); // 当前节点所在
		while (base->below) { base = base->below; } // 塔底
		while (base->pred) { base = base->pred; } // 底层之header
		for (int i = 0; i < q.size(); i++) { // 对于当前层的每一个节点
			curr = curr->succ;
			auto proj = curr; // 找到与curr对应的
			while (proj->below) { proj = proj->below; } // 塔底节点（投影）
			while ((base = base->succ) != proj) { // 移动base直到proj，期间不断
				printf("------------"); //延长水平联接线
			}
			print(curr->entry); // 最后，输出当前层的当前词条
		}
		printf("\n");
	}

	//! 跳转表
	template <typename K, typename V>
	static void p(Skiplist<K, V>& s) {
		printf("%s[0x%p]*%d*%d\n", typeid(s).name(), &s, s.level(), s.size());
		s.traverse(print);
		printf("\n");
	}

	//! 散列表
	template <typename K, typename V>
	static void p(Hashtable<K, V>& ht) {
		printf("%s[0x%p]*%d/%d\n", typeid (ht).name(), &ht, ht.N, ht.M); //基本信息
		for (int i = 0; i < ht.M; i++) { //输出桶编号
			printf("  %4d  ", i);
		}
		printf("\n");
		for (int i = 0; i < ht.M; i++) { //输出所有元素
			if (ht.buckets[i]) { printf("-<%04d>-", ht.buckets[i]->key); } //演示用，仅适用于int
			else if (ht.lazyRemoval->test(i)) { printf("-<xxxx>-"); }
			else { printf("--------"); }
		}
		printf("\n");
		for (int i = 0; i < ht.M; i++) { //输出所有元素
			if (ht.buckets[i]) { printf("    %c   ", ht.buckets[i]->value); } //演示用，仅适用于char
			// if (ht.ht[i]) printf("%8s", ht.ht[i]->value); //针对Huffman编码中使用的散列表
			else if (ht.lazyRemoval->test(i)) { printf(" <xxxx> "); }
			else { printf("        "); }
		}
		printf("\n");
	}

	//! 完全二叉堆
	template <typename T>
	static void p(CompleteHeap<T>& heap) {
		printf("%s[0x%p]*%d\n", typeid(heap).name(), &heap, heap.size());
		int branchType[256];
		printCompleteHeap(heap, heap.size(), 0, 0, TreeNodeType::ROOT, branchType);
		printf("\n");
	}

	//! 完全二叉堆递归辅助函数(type: 0 root, 1 left-child, -1 right-child
	template <typename T>
	static void printCompleteHeap(Vector<T>& heap, int n, int k, int depth, TreeNodeType type, int* bType) {
		if (k >= n) { return; }
		bType[depth] = type;
		printCompleteHeap(heap, n, CompleteHeap<T>::rChild(k), depth + 1, TreeNodeType::R_CHILD, bType);
		print(heap[k]);
		CompleteHeap<T>::hasParent(k) && (heap[CompleteHeap<T>::parent(k)] < heap[k]) ? printf("X") : printf(" ");
		printf("*");
		for (int i = 0; i < depth; i++) {
			if (bType[i] + bType[i + 1]) {
				printf("      ");
			} else {
				printf("│    ");
			}
		}
		p(type);
		print(heap[k]);
		CompleteHeap<T>::hasParent(k) && (heap[CompleteHeap<T>::parent(k)] < heap[k]) ? printf("X") : printf("*");
		printf("\n");
		printCompleteHeap(heap, n, CompleteHeap<T>::lChild(k), depth + 1, TreeNodeType::L_CHILD, bType);
	}

	//! 左式堆
	template <typename T>
	static void p(LeftHeap<T>& heap) {
		p(static_cast<BinTree<T>&>(heap));
	}

	//! 向量、列表等支持traverse()遍历的线性结构
	template <typename T>
	static void p(T& s) {
		printf("%s[0x%p]*%d\n", typeid(s).name(), &s, s.size());
		s.traverse(print);
		printf("\n");
	}
};

}
