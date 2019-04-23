#pragma once

#include "quadlist_node.h"

namespace dtl 
{

//! 四联表
template <typename T>
class Quadlist
{
public:
	typedef QuadlistNode<T> Node;
	typedef Node* NodePtr;

private:
	//! 规模
	int size_;
	//! 头哨兵
	NodePtr header;
	//! 尾哨兵
	NodePtr trailer;

protected:
	//! 创建时的初始化
	void init() {
		header = new Node();
		trailer = new Node();
		header->succ = trailer;
		trailer->pred = header;
		size_ = 0;
	}

	//! 清除所有节点
	int clear() {
		int oldSize = size_;
		while (size_ > 0) { remove(header->succ); }
		return oldSize;
	}

public:
	Quadlist() { init(); }
	~Quadlist() { clear(); delete header; delete trailer; }

	/******readonly******/
	int size() const { return size_; }
	bool empty() const { return size_ <= 0; }
	NodePtr first() const { return header->succ; }
	NodePtr last() const { return trailer->pred; }
	bool valid(NodePtr p) { return p && (trailer != p) && (header != p); }

	/******mutable******/
	//! 删除（合法）位置p处的节点，返回被删除节点的值
	T remove(NodePtr p) {
		p->pred->succ = p->succ; p->succ->pred = p->pred;
		size_--; auto e = p->entry; delete p; return e;
	}

	//! 将e作为p的后继、b的上邻插入
	NodePtr insertAfterAbove(T const& e, NodePtr p, NodePtr b = nullptr) {
		size_++; return p->insertAsSuccAbove(e, b);
	}


	/******traverse******/
	//! 遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
	void traverse(void(*visit)(T&)) {
		auto p = header;
		while ((p = p->succ) != trailer) { visit(p->entry); }
	}

	//! 遍历各节点，依次实施指定操作（函数对象，可全局性修改节点
	template <typename VST>
	void traverse(VST& visit) {
		auto p = header;
		while ((p = p->succ) != trailer) { visit(p->entry); }
	}
};

}
