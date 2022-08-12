#include "bst.h"
#include <stdlib.h>

struct BstNode {
	ElementType Element;
	BST Left;
	BST Right;
};

BST bstEmpty(BST t)
{
	if (t) {
		bstEmpty(t->Left);
		bstEmpty(t->Right);
		free(t);
	}
	return NULL;
}

BstPosition bstFind(BST t, ElementType e)
{
	if (t == NULL) return NULL;
	if (e < t->Element)
		return bstFind(t->Left, e);
	else if (e > t->Element)
		return bstFind(t->Right, e);
	else
		return t;
}

BstPosition bstFindMax(BST t)
{
	if (t) {
		while (t->Right) {
			t = t->Right;
		}
	}
	return t;
}

BstPosition bstFindMin(BST t)
{
	if (t) {
		while (t->Left) {
			t = t->Left;
		}
	}
	return t;
}

BST bstInsert(BST t, ElementType e)
{
	if (t == NULL) {
		t = malloc(sizeof(*t));
		if (!t) { return NULL; }
		t->Element = e;
		t->Left = t->Right = NULL;
	} else if (e < t->Element) {
		t->Left = bstInsert(t->Left, e);
	} else if (e > t->Element) {
		t->Right = bstInsert(t->Right, e);
	}
	return t;
}

BST bstDelete(BST t, ElementType e)
{
	if (!t) { return NULL; }
	if (t->Element > e) {
		t->Left = bstDelete(t->Left, e);
	} else if (t->Element < e) {
		t->Right = bstDelete(t->Right, e);
	} else if (t->Left && t->Right) {
		BST tmp = bstFindMin(t->Right);
		t->Element = tmp->Element;
		t->Right = bstDelete(t->Right, t->Element);
	} else {
		BST tmp = t;
		if (t->Left == NULL) {
			t = t->Right;
		} else if (t->Right == NULL) {
			t = t->Left;
		}
		free(tmp);
	}
	return t;
}

ElementType bstRetrieve(BstPosition p)
{
	return p->Element;
}
