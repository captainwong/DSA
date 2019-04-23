#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <typeinfo.h>

#include "../dtl/graph.h"
#include "../dtl/hashtable.h"
#include "../dtl/quadlist.h"
#include "../dtl/skiplist.h"

namespace dtl 
{

//! 萃取指针类型，转为引用
template <typename T>
static void print(T* x) { x ? print(*x) : printf(" <NULL>"); }

template <typename T>
static void print(T& x) { UniPrint::p(x); }

template <typename T>
static void print(const T& x) { UniPrint::p(x); }

static void print(char* x) { printf(" %s", x ? x : "<NULL>"); }
static void print(const char* x) { printf(" %s", x ? x : "<NULL>"); }


class UniPrint
{
public:
	static void p(int e) { printf(" %04d", e); }
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

	//! 向量、列表等支持traverse()遍历的线性结构
	template <typename T> 
	static void p(T& s){
		printf("%s[0x%p]*%d:\n", typeid(s).name(), &s, s.size());
		s.traverse(print);
		printf("\n");
	}

	//! 萃取指针类型，统一转为引用
	template <typename T>
	static void p(T* s) { if (s) { p(*s); } else { printf(" <NULL>"); } }

	template <typename K, typename V>
	static void p(Entry<K, V>& e) {
		printf("-<"); print(e.key); printf(":"); print(e.value); printf(">-");
	}

	//! 四联表
	template <typename T>
	static void p(Quadlist<T>& q) {
		printf("%s[0x%p]*%03d: ", typeid(q).name(), &q, q.size());
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
		printf("%s[0x%p]*%d*%d:\n", typeid(s).name(), &s, s.level(), s.size());
		s.traverse(print);
		printf("\n");
	}

	//! 散列表
	template <typename K, typename V>
	static void p(Hashtable<K, V>& ht) {
		printf("%s[0x%p]*%d/%d:\n", typeid (ht).name(), &ht, ht.N, ht.M); //基本信息
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
};

}
