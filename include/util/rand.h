#pragma once

#include <stdlib.h>
#include <time.h>

//! 用当前时间戳设置随机种子
static void srand_time() { srand(static_cast<unsigned int>(time(nullptr))); }
//! [0, range)中的随机数
static int dice(int range) { return rand() % range; }
//! [lo, hi)中的随机数
static int dice(int lo, int hi) { return lo + rand() % (hi - lo); }
//! ASCII 值 [32, 128)（可打印字符）
static char dice(char range) { return static_cast<char>(32 + rand() % 96); }
