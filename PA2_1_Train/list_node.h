#pragma once

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T> 
struct ListNode
{
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		: data(e), pred(p), succ(s)
	{}

	ListNodePosi(T) insert_as_pred(T const& e);
	ListNodePosi(T) insert_as_succ(T const& e);
};

#include "list_node_implementaion.h"
