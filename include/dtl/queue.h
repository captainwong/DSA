#pragma once

#include "list.h"

namespace dtl 
{

template <typename T> 
class Queue : public List<T>
{
public:
	void enqueue(T const& e) { this->insert_as_last(e); }
	T dequeue() { return this->remove(this->first()); }
	T& front() { return this->first()->data; }
};

}
