/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

#include <iostream>
using namespace std;

/******************************************************************************************
 * 将binTree各方法的实现部分，简洁地引入binTree.h
 * 效果等同于将这些实现直接汇入binTree.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "bintree_updateheight.h"
#include "bintree_insert.h"
#include "bintree_attach.h"
#include "bintree_remove.h"
#include "bintree_secede.h"
