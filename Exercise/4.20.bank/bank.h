#pragma once

#include "../../include/util/util.h"
#include "../../include/dtl/queue.h"
#include "../../include/dtl/vector.h"

struct Customer
{
	int window;
	int time;
};

typedef dtl::Queue<Customer> Window;
typedef Window* Windows;

int bestWindow(Windows windows, int nWin)
{
	int minSize = windows[0].size();
	int optiWin = 0;

	for (int i = 1; i < nWin; i++) {
		if (minSize > windows[i].size()) {
			minSize = windows[i].size();
			optiWin = i;
		}
	}

	return optiWin;
}

void displayProgress(Windows windows, int nWin, int now, int wait_ms)
{
	if (wait_ms == dtl::WAIT_PAUSE) { system("cls"); }
	printf("========== Time %4d ===========\n", now);
	for (int i = 0; i < nWin; i++) {
		printf("Window #%c: ", 'A' + i);
		windows[i].traverse([](Customer& c) {
			printf("%4d", c.time);
		});
		printf("\n");
	}
	dtl::wait(wait_ms);
}

void simulate(int nWin, int servTime, int wait_ms = dtl::WAIT_NO_WAIT)
{
	Windows windows = new Window[nWin];

	for (int now = 0; now < servTime; now++) {
		if (rand() % (1 + nWin)) {
			Customer c;
			c.time = 1 + rand() % 98;
			c.window = bestWindow(windows, nWin);
			windows[c.window].enqueue(c);
		}

		for (int i = 0; i < nWin; i++) {
			if (!windows[i].empty()) {
				if (--windows[i].front().time <= 0) {
					windows[i].dequeue();
				}
			}
		}

		displayProgress(windows, nWin, now, wait_ms);
	}

	delete[] windows;
}

void simulate_a(int nWin, int servTime, int wait_ms = dtl::WAIT_NO_WAIT)
{
	Windows windows = new Window[nWin];

	for (int now = 0; now < servTime; now++) {
		if ((now < servTime / 3) ? (rand() % (nWin / 2)) : ((now < servTime * 2 / 3) ? (rand() % nWin) : (rand() % (nWin * 2)))) {
			Customer c;
			c.time = 1 + rand() % 98;
			c.window = bestWindow(windows, nWin);
			windows[c.window].enqueue(c);
		}

		for (int i = 0; i < nWin; i++) {
			if (!windows[i].empty()) {
				if (--windows[i].front().time <= 0) {
					windows[i].dequeue();
				}
			}
		}

		displayProgress(windows, nWin, now, wait_ms);
	}

	delete[] windows;
}

struct accumulator
{
	int total = 0;

	void operator()(const Customer& c) {
		total += c.time;
	}
};

int bestWindow_b(Windows windows, int nWin)
{
	accumulator ac;
	windows[0].traverse(ac);
	int minTotalTime = ac.total;
	int optiWin = 0;

	for (int i = 1; i < nWin; i++) {
		ac.total = 0;
		windows[i].traverse(ac);
		if (minTotalTime > ac.total) {
			minTotalTime = ac.total;
			optiWin = i;
		}
	}

	return optiWin;
}

void simulate_b(int nWin, int servTime, int wait_ms = dtl::WAIT_NO_WAIT)
{
	Windows windows = new Window[nWin];

	for (int now = 0; now < servTime; now++) {
		if ((now < servTime / 3) ? (rand() % (nWin / 2)) : ((now < servTime * 2 / 3) ? (rand() % nWin) : (rand() % (nWin * 2)))) {
			Customer c;
			c.time = 1 + rand() % 98;
			c.window = bestWindow_b(windows, nWin);
			windows[c.window].enqueue(c);
		}

		for (int i = 0; i < nWin; i++) {
			if (!windows[i].empty()) {
				if (--windows[i].front().time <= 0) {
					windows[i].dequeue();
				}
			}
		}

		displayProgress(windows, nWin, now, wait_ms);
	}

	delete[] windows;
}
