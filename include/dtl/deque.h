#pragma once

#include "config.h"
#include "list.h"

namespace dtl
{

//! 双端队列（习题[4-22]）
template <typename T>
class Deque : public List<T>
{
public:
	//! 读取首元素
	T& front() { return first()->data; }
	//! 读取末元素
	T& back() { return last()->data; }
	//! 插入至队列前端
	void push_front(const T& e) { insert_as_first(e); }
	//! 插入至队列末端
	void push_back(const T& e) { insert_as_last(e); }
	//! 删除首元素
	T pop_front() { T data = first()->data; remove(first()); return data; }
	//! 删除末元素
	T pop_back() { T data = last()->data; remove(last()); return data; }
};

}
