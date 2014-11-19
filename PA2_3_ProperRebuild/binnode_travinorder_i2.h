/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2 ( BinNodePosi(T) x, VST& visit ) { //��������������㷨��������#2��
   Stack<BinNodePosi(T)> S; //����ջ
   while ( true )
      if ( x ) {
         S.push ( x ); //���ڵ��ջ
         x = x->lc; //�������������
      } else if ( !S.empty() ) {
         x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
         visit ( x->data ); //���ʸ����Ƚڵ�
         x = x->rc; //�������ȵ�������
      } else
         break; //�������
}