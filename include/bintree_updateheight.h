/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x ) //���½ڵ�x�߶�
{ return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) ); } //���������������

template <typename T> void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) //���¸߶�
{ while ( x ) { updateHeight ( x ); x = x->parent; } } //��x�����������������ȡ����Ż�
