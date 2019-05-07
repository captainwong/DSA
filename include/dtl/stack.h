#pragma once

#include "list.h"

namespace dtl 
{

//! 栈
template <typename T> 
class Stack : public List<T>
{
public:
	void push(T const& e) { this->insert_as_last(e); }
	T pop() { return this->remove(this->last()); }
	T& top() { return this->last()->data; }
};

}
