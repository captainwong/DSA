/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede ( BinNodePosi(T) x ) { //assert: xΪ�������еĺϷ�λ��
   FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
   updateHeightAbove ( x->parent ); //����ԭ�����������ȵĸ߶�
   BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
   S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}