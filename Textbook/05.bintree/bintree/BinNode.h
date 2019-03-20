#pragma once

template <typename T>
struct BinNode
{
	using Ptr = typename BinNode<T>*;

	T data;
	Ptr parent;
	Ptr lChild;
	Ptr rChild;
	int height;

	BinNode()
		: data()
		, parent(nullptr)
		, lChild(nullptr)
		, rChild(nullptr)
		, height(-1)
	{}

	BinNode(const T& data, Ptr parent = nullptr)
		: data(data)
		, parent(parent)
		, lChild(nullptr)
		, rChild(nullptr)
		, height(0)
	{
	}

	int size() const {
		int s = 1;
		if (lChild) { s += lChild->size(); }
		if (rChild) { s += rChild->size(); }
		return s;
	}

	Ptr insertAsLeftChild(const T& data) {
		return (lChild = new BinNode(data, this));
	}

	Ptr insertAsRightChild(const T& data) {
		return (rChild = new BinNode(data, this));
	}
};

template <typename T>
int stature(BinNode<T>* node)
{
	return node ? node->height : -1;
}