#pragma once

namespace dtl
{

//! 优先级队列接口定义
template <typename T>
struct PriorityQueue
{
	//! 按照比较器确定的优先级次序插入词条
	virtual void insert(T const&) = 0;
	//! 获取优先级最高的词条
	virtual T getMax() = 0;
	//! 删除优先级最高的词条
	virtual T delMax() = 0;
};

}
