#pragma once

#ifndef _OJ_
#include "../03.list/list.h"
using namespace JTL;
#else
#include "list.h"
#endif

template <typename T> 
class Stack : public List<T>
{
public:
	void push(T const& e) { this->insert_as_last(e); }
	T pop() { return this->remove(this->last()); }
	T& top() { return this->last()->data; }
};


