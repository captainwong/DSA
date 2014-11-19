/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I4 ( BinNodePosi(T) x, VST& visit ) { //���������������������#4������ջ���־λ��
   while ( true )
      if ( HasLChild ( *x ) ) //��������������
         x = x->lc; //�������������
      else { //����
         visit ( x->data ); //���ʵ�ǰ�ڵ㣬��
         while ( !HasRChild ( *x ) ) //���ϵ������ҷ�֧��
            if ( ! ( x = x->succ() ) ) return; //������ֱ�Ӻ�̣���û�к�̵�ĩ�ڵ㴦��ֱ���˳���
            else visit ( x->data ); //�����µĵ�ǰ�ڵ�
         x = x->rc; //��ֱ�����ҷ�֧����ת��ǿյ�������
      }
}