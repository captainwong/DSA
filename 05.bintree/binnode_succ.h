/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //��λ�ڵ�v��ֱ�Ӻ��
   BinNodePosi(T) s = this; //��¼��̵���ʱ����
   if ( rc ) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
      s = rc; //��������
      while ( HasLChild ( *s ) ) s = s->lc; //�����С���Ľڵ�
   } else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
      while ( IsRChild ( *s ) ) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
      s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
   }
   return s;
}