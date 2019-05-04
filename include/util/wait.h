#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <thread>
#include <chrono>
#include <stdlib.h>

namespace dtl
{

static constexpr int WAIT_PAUSE = -1;
static constexpr int WAIT_NO_WAIT = 0;

// 等待指定时间 gap_ms=-1 pause; gap_ms=0 continue; gap_ms>0 sleep
static void wait(int gap_ms = 1000)
{
	if (gap_ms == WAIT_PAUSE) {
		system("pause");
	} /*else if (gap_ms == 0) {
		
	} */else if (gap_ms > 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
	}
}

}
