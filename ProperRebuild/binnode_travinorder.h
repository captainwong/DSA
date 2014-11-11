/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

/*dsa*/#include "stack.h" //����ջģ����
/*dsa*/#include "binnode_travinorder_r.h"
/*dsa*/#include "binnode_travinorder_i1.h"
/*dsa*/#include "binnode_travinorder_i2.h"
/*dsa*/#include "binnode_travinorder_i3.h"
/*dsa*/#include "binnode_travinorder_i4.h"
template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit)
{ //��������������㷨ͳһ���
	travIn_I4(this, visit);
	return;
	//switch (rand() % 5) { //�˴������ѡ���������ԣ�������ѡ��
	//	case 1: travIn_I1(this, visit); break; //������#1
	//	case 2: travIn_I2(this, visit); break; //������#2
	//	case 3: travIn_I3(this, visit); break; //������#3
	//	case 4: travIn_I4(this, visit); break; //������#4
	//	default: travIn_R(this, visit); break; //�ݹ��
	//}
}