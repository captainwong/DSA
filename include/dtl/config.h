﻿#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

//! 测试编译开关 一些函数有多种实现方法，定义此宏则全部编译调用，未定义则仅编译调用最优解
#define TEST_BUILD 0

//! 演示模式开关
#define DSA_MODE 1

//! 是否使用 std::initializer_list
#define ENABLE_INITIALIZER_LIST 1
