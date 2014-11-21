/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once
#include "release.h"
#include "binnode.h" //����������ڵ���
template <typename T> class BinTree { //������ģ����
protected:
   int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
   virtual int updateHeight ( BinNodePosi(T) x ); //���½ڵ�x�ĸ߶�
   void updateHeightAbove ( BinNodePosi(T) x ); //���½ڵ�x�������ȵĸ߶�
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
   ~BinTree() { if ( 0 < _size ) remove ( _root ); } //��������
   int size() const { return _size; } //��ģ
   bool empty() const { return !_root; } //�п�
   BinNodePosi(T) root() const { return _root; } //����
   BinNodePosi(T) insertAsRoot ( T const& e ); //������ڵ�
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e��Ϊx�����ӣ�ԭ�ޣ�����
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
   BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* & ); //T��Ϊx����������
   BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* & ); //T��Ϊx����������
   int remove ( BinNodePosi(T) x ); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
   BinTree<T>* secede ( BinNodePosi(T) x ); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
   template <typename VST> //������
   void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //��α���
   template <typename VST> //������
   void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //�������
   template <typename VST> //������
   void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //�������
   template <typename VST> //������
   void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //�������
   bool operator< ( BinTree<T> const& t ) //�Ƚ������������в��䣩
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //�е���
   { return _root && t._root && ( _root == t._root ); }
   /*DSA*/
   /*DSA*/void stretchToLPath() { stretchByZag ( _root ); } //����zag��ת��ת��Ϊ������
   /*DSA*/void stretchToRPath() { stretchByZig ( _root, _size ); } //����zig��ת��ת��Ϊ������
}; //BinTree

#include "bintree_implementation.h"