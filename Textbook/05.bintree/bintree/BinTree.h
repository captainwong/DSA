#pragma once

#include "BinNode.h"
#include <algorithm> // std::max
#include "../../../include/stack.h"
#include "../../../include/queue.h"

template <typename T>
class BinTree
{
public:
	typedef typename BinNode<T> Node;
	typedef typename Node::Ptr NodePtr;

protected:
	int size_;
	NodePtr root_;

	//! 更新节点 node 的高度
	virtual int updateHeight(NodePtr node) {
		return node->height_ = 1 + std::max(stature(node->lChild_), stature(node->rChild_));
	}

	//! 更新节点 node 及其祖先的高度
	void updateHeightAbove(NodePtr node) {
		while (node) {
			updateHeight(node);
			node = node->parent_;
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
	NodePtr& fromParentTo(NodePtr node) {
		return node->isRoot() ? root_ : (node->isLChild() ? node->parent_->lChild_ : node->parent_->rChild_);
	}

	NodePtr insertAsRootNode(T const& data) {
		size_ = 1;
		return (root_ = new Node(data));
	}

	NodePtr insertAsLeftChild(NodePtr node, T const& data) {
		size_++;
		node->insertAsLeftChild(data);
		updateHeightAbove(node);
		return node->lChild_;
	}

	NodePtr insertAsRightChild(NodePtr node, T const& data) {
		size_++;
		node->insertAsRightChild(data);
		updateHeightAbove(node);
		return node->rChild_;
	}

	template <typename VST>
	static void visitAlongLeftBranch(NodePtr node, VST& visit, Stack<NodePtr>& stack) {
		while (node) {
			visit(node->data_);
			stack.push(node->rChild_);
			node = node->lChild_;
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
			node = node->lChild_;
		}
	}

	template <typename VST>
	void travInOrder(NodePtr node, VST& visit) {
		Stack<NodePtr> stack;
		while (true) {
			goAlongLeftBranch(node, stack);
			if (stack.empty()) { break; }
			node = stack.pop();
			visit(node->data_);
			node = node->rChild_;
		}
	}

	// go to highest leaf visible from left
	static void goToHLVFL(Stack<NodePtr>& stack) {
		while (auto node = stack.top()) {
			if (node->lChild_) {
				if (node->rChild_) {
					stack.push(node->rChild_);
				}
				stack.push(node->lChild_);
			} else {
				stack.push(node->rChild_);
			}
		}
		stack.pop();
	}

	template <typename VST>
	void travPostOrder(NodePtr node, VST& visit) {
		Stack<NodePtr> stack;
		if (node) { stack.push(node); }
		while (!stack.empty()) {
			if (stack.top() != node->parent_) {
				goToHLVFL(stack);
			}
			node = stack.pop();
			visit(node->data_);
		}
	}

	template <typename VST>
	void travLevelOrder(NodePtr node, VST& visit) {
		Queue<NodePtr> queue;
		queue.enqueue(node);
		while (!queue.empty()) {
			node = queue.dequeue();
			visit(node->data_);
			if (node->lChild_) { queue.enqueue(node->lChild_); }
			if (node->rChild_) { queue.enqueue(node->rChild_); }
		}
	}
};
