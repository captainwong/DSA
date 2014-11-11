#pragma once


#include "queue.h"

template <typename T> class Deque : public Queue<T>
{
public:
	T remove_rear() { return this->remove(this->last()); }
	T& rear() { return this->last()->data; }
};