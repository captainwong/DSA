#pragma once

#include "BinNode.h"
#include <algorithm>
#include "../include/stack.h"
#include "../include/queue.h"

template <typename T>
class BinTree
{
public:
	using Node = typename BinNode<T>;
	using NodePtr = typename Node::Ptr;

protected:
	int size_;
	NodePtr root_;

	//! 更新节点 node 的高度
	virtual int updateHeight(NodePtr node) {
		return node->height = 1 + std::max(stature(node->lChild), stature(node->rChild));
	}

	//! 更新节点 node 及其祖先的高度
	void updateHeightAbove(NodePtr node) {
		while (node) {
			updateHeight(node);
			node = node->parent;
		}
	}

public:
	BinTree()
		: size_(0)
		, root_(nullptr)
	{}

	int size() const { return size_; }
	bool empty() const { return !root_; }
	NodePtr root() const { return root_; }

	NodePtr insertAsRootNode(T const& data) {
		size_ = 1;
		return (root_ = new Node(data));
	}

	NodePtr insertAsLeftChild(NodePtr node, T const& data) {
		size_++;
		node->insertAsLeftChild(data);
		updateHeightAbove(node);
		return node->lChild;
	}

	NodePtr insertAsRightChild(NodePtr node, T const& data) {
		size_++;
		node->insertAsRightChild(data);
		updateHeightAbove(node);
		return node->rChild;
	}

	template <typename VST>
	static void visitAlongLeftBranch(NodePtr node, VST& visit, Stack<NodePtr>& stack) {
		while (node) {
			visit(node->data);
			stack.push(node->rChild);
			node = node->lChild;
		}
	}

	template <typename VST>
	void travPreOrder(NodePtr node, VST& visit) {
		Stack<NodePtr> stack;
		while (true) {
			visitAlongLeftBranch(node, visit, stack);
			if (stack.empty()) { break; }
			node = stack.pop();
		}
	}

	static void goAlongLeftBranch(NodePtr node, Stack<NodePtr>& stack) {
		while (node) {
			stack.push(node);
			node = node->lChild;
		}
	}

	template <typename VST>
	void travInOrder(NodePtr node, VST& visit) {
		Stack<NodePtr> stack;
		while (true) {
			goAlongLeftBranch(node, stack);
			if (stack.empty()) { break; }
			node = stack.pop();
			visit(node->data);
			node = node->rChild;
		}
	}

	// go to highest leaf visible from left
	static void goToHLVFL(Stack<NodePtr>& stack) {
		while (auto node = stack.top()) {
			if (node->lChild) {
				if (node->rChild) {
					stack.push(node->rChild);
				}
				stack.push(node->lChild);
			} else {
				stack.push(node->rChild);
			}
		}
		stack.pop();
	}

	template <typename VST>
	void travPostOrder(NodePtr node, VST& visit) {
		Stack<NodePtr> stack;
		if (node) { stack.push(node); }
		while (!stack.empty()) {
			if (stack.top() != node->parent) {
				goToHLVFL(stack);
			}
			node = stack.pop();
			visit(node->data);
		}
	}

	template <typename VST>
	void travLevelOrder(NodePtr node, VST& visit) {
		Queue<NodePtr> queue;
		queue.enqueue(node);
		while (!queue.empty()) {
			node = queue.dequeue();
			visit(node->data);
			if (node->lChild) { queue.enqueue(node->lChild); }
			if (node->rChild) { queue.enqueue(node->rChild); }
		}
	}
};