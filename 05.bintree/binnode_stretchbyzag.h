/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

//ͨ��zag��ת������������x����������ͨ·
template <typename T> void stretchByZag ( BinNodePosi(T) & x ) {
   /*DSA*/   int c = 0; //��¼��ת����
   int h = 0;
   BinNodePosi(T) p = x; while ( p->rc ) p = p->rc; //���ڵ㣬�����������յĸ�
   while ( x->lc ) x = x->lc; x->height = h++; //ת����ʼ�����ͨ·��ĩ��
   for ( ; x != p; x = x->parent, x->height = h++ ) { //��x�������ѿգ�������һ��
      while ( x->rc ) //���򣬷�����
         /*DSA*/{
         x->zag(); //��xΪ����zag��ת
         /*DSA*/c++;
         /*DSA*/}
   } //ֱ���ִ������ĸ�
   /*DSA*/printf ( "\nh = %d, c = %d\n\n", h, c );
}
