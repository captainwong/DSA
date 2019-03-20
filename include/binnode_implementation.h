/******************************************************************************************
 * data structures in c++
 * isbn: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * junhui deng, deng@tsinghua.edu.cn
 * computer science & technology, tsinghua university
 * copyright (c) 2006-2013. all rights reserved.
 ******************************************************************************************/

#pragma once

/******************************************************************************************
 * 将binnode各方法的实现部分，简洁地引入binnode.h
 * 效果等同于将这些实现直接汇入binnode.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "binnode_macro.h"
#include "binnode_size.h" //后代数目
#include "binnode_insert.h" //插入
#include "binnode_succ.h" //取节点后继
#include "binnode_travpreorder.h" //先序遍历
#include "binnode_travinorder.h" //中序遍历
#include "binnode_travpostorder.h" //后序遍历
#include "binnode_travlevel.h" //层次遍历
#include "binnode_zig.h" //顺时针旋转
#include "binnode_zag.h" //逆时针旋转
#include "binnode_stretchbyzig.h"
#include "binnode_stretchbyzag.h"