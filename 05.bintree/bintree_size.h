/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> //ͳ�ƶ�����������ģ
int BinTree<T>::size ( BinNodePosi(T) x ) //assert: xΪ�������еĺϷ�λ��
{  return x ? size ( x->lc ) + size ( x->RChild ) : 0;  }
