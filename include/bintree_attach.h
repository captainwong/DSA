/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S ) { //x->lc == NULL
   if ( x->lc = S->_root ) x->lc->parent = x; //����
   _size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
   S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC ( BinNodePosi(T) x, BinTree<T>* &S ) { //x->rc == NULL
   if ( x->rc = S->_root ) x->rc->parent = x; //����
   _size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
   S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}