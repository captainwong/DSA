/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

/*dsa*/#include "stack.h" //����ջģ����
/*dsa*/#include "binnode_travpreorder_r.h"
/*dsa*/#include "binnode_travpreorder_i1.h"
/*dsa*/#include "binnode_travpreorder_i2.h"
template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travPre ( VST& visit ) { //��������������㷨ͳһ���
	travPre_I2(this, visit);
   //switch ( rand() % 3 ) { //�˴������ѡ���������ԣ�������ѡ��
   //   case 1: travPre_I1 ( this, visit ); break; //������#1
   //   case 2: travPre_I2 ( this, visit ); break; //������#2
   //   default: travPre_R ( this, visit ); break; //�ݹ��
	//}
}