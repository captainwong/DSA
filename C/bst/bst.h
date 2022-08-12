#ifndef __BST_H__
#define __BST_H__

#pragma once

typedef int ElementType;

struct BstNode;
typedef struct BstNode* BstPosition;
typedef struct BstNode* BST;

BST bstEmpty(BST t);
BstPosition bstFind(BST t, ElementType e);
BstPosition bstFindMax(BST t);
BstPosition bstFindMin(BST t);
BST bstInsert(BST t, ElementType e);
BST bstDelete(BST t, ElementType e);
ElementType bstRetrieve(BstPosition p);

#endif
