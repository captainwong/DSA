#pragma once

#include "../util/util.h"
#include "../util/op.h"
#include "../dtl/bintree.h"

namespace dtl
{
namespace test
{

//! 随机生成期望高度为h的二叉树
template <typename T>
bool randomBinTree(BinTree<T>& bt, BinNode<T>* x, int h)
{
	if (h <= 0) { return false; }
	if (dice(h)) {
		randomBinTree(bt, bt.insertAsLeftChild(x, dice((T)h * h * h)), h - 1);
	}
	if (dice(h)) {
		randomBinTree(bt, bt.insertAsRightChild(x, dice((T)h * h * h)), h - 1);
	}
	return true;
}

//! 在二叉树中随机确定一个节点位置
template <typename T>
BinNode<T>* randomPosInBinTree(BinNode<T>* root)
{
	if (!root->hasChild()) { return root; }
	if (!root->hasLChild()) {
		return dice(6) ? randomPosInBinTree(root->rChild_) : root;
	}
	if (!root->hasRChild()) {
		return dice(6) ? randomPosInBinTree(root->lChild_) : root;
	}
	return dice(2) ? randomPosInBinTree(root->lChild_) : randomPosInBinTree(root->rChild_);
}

template <typename T>
void testBinTree(int h, int wait_ms = WAIT_NO_WAIT)
{
	int testID = 0;

	printf("\n  ==== Test %2d. Generate a binTree of height <= %d \n", testID++, h);
	BinTree<T> bt; print(bt);
	bt.insertAsRootNode(dice((T)h * h * h)); print(bt);
	randomBinTree<T>(bt, bt.root(), h); print(bt);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Double and increase all nodes by traversal\n", testID++);
	printf("Double Increase and travPreOrder\n");
	bt.travPreOrder(Double<T>()); bt.travPreOrder(Increase<T>()); print(bt);
	wait(wait_ms);
	printf("Double Increase and travInOrder\n");
	bt.travInOrder(Double<T>()); bt.travInOrder(Increase<T>()); print(bt);
	wait(wait_ms);
	printf("Double Increase and travPostOrder\n");
	bt.travPostOrder(Double<T>()); bt.travPostOrder(Increase<T>()); print(bt);
	wait(wait_ms);
	printf("Double Increase and travLevelOrder\n");
	bt.travLevelOrder(Double<T>()); bt.travLevelOrder(Increase<T>()); print(bt);
	wait(wait_ms);
	printf("Hailstone and travInOrder\n");
	Hailstone<T> he; bt.travInOrder(he); print(bt);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Remove/release subtrees in the Tree\n", testID++);
	while (!bt.empty()) {
		auto p = randomPosInBinTree(bt.root()); //随机选择一个节点
		if (dice(2)) {
			printf("removing "); print(p->data_); printf(" ...\n");
			printf("%d node(s) removed\n", bt.remove(p)); print(bt);
		} else {
			printf("releasing "); print(p->data_); printf(" ...\n");
			BinTree<T>* S = bt.secede(p); print(S);
			printf("%d node(s) released\n", S->size()); release(S); print(bt);
		}
		wait(wait_ms);
	}
}

}
}
