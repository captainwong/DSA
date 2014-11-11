/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongLeftBranch ( BinNodePosi(T) x, Stack<BinNodePosi(T)>& S ) {
   while ( x ) { S.push ( x ); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1 ( BinNodePosi(T) x, VST& visit ) { //��������������㷨��������#1��
   Stack<BinNodePosi(T)> S; //����ջ
   while ( true ) {
      goAlongLeftBranch ( x, S ); //�ӵ�ǰ�ڵ������������ջ
      if ( S.empty() ) break; //ֱ�����нڵ㴦�����
      x = S.pop(); visit ( x->data ); //����ջ���ڵ㲢����֮
      x = x->rc; //ת��������
   }
}
