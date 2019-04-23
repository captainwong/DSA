#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "dictionary.h"
#include "list.h"
#include "quadlist.h"
#include <stdlib.h> // rand

namespace dtl 
{

//! 跳转表
template <typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
public:
	typedef Entry<K, V> EntryType;
	typedef QuadlistNode<EntryType> QuadlistNodeType;
	typedef QuadlistNodeType* QuadlistNodePtr;
	typedef Quadlist<EntryType> QuadlistType;
	typedef QuadlistType* QuadlistPtr;
	typedef ListNode<QuadlistPtr> ListNodeType;
	typedef ListNodeType* ListNodePtr;
	typedef List<QuadlistPtr> ListType;

protected:
	/**
	* @brief 词条查找
	* @param qlist 顶层列表
	* @param p qlist的首节点
	* @param k 要查找的目标词条关键码
	* @return 若成功，p为命中关键码所属塔的顶部节点，qlist为所属列表
	*		  若失败，p为所属塔的基座，该塔对应于不大于k的最大且最靠右关键码，qlist为空
	* @note 多个词条命中时，沿四联表取最靠右者
	*/
	bool skipSearch(ListNodePtr& qlist, QuadlistNodePtr& p, K& k) {
		while (true) { // 在每一层
			while (p->succ && (p->entry.key <= k)) { // 从前向后查找
				p = p->succ; // 直到出现更大的key或溢出至trailer
			}
			p = p->pred; // 此时倒回一步，即可判断是否
			if (p->pred && (k == p->entry.key)) { return true; } // 命中
			qlist = qlist->succ; // 否则转入下一层
			if (!qlist->succ) { return false; } // 若已穿透底层，则意味着失败
			p = (p->pred) ? p->below : qlist->data->first(); // 否则转至当前塔的下一节点
		}
	}

public:
	//! 底层Quadlist的规模
	int size() const { return ListType::empty() ? 0 : ListType::last()->data->size(); }
	//! 层高 == #Quadlist
	int level() { return ListType::size(); }

	//! 插入（与Map有区别 —— Skiplist允许词条重复，故必然成功）
	bool put(K k, V v) {
		auto entry = EntryType(k, v); // 待插入的词条，将被随机地插入多个副本
		if (ListType::empty()) { ListType::insert_as_first(new QuadlistType()); } // 插入首个entry
		ListNodePtr qlist = ListType::first(); // 从顶层四联表的
		QuadlistNodePtr p = qlist->data->first(); // 首节点出发
		if (skipSearch(qlist, p, k)) { // 查找适当的插入位置（不大于关键码k的最后一个节点p
			while (p->below) { p = p->below; } // 若已有雷同词条，则需强制转到塔底
		}
		qlist = ListType::last(); // 以下，紧邻于p的右侧，一座新塔将自底而上逐层生长
		QuadlistNodePtr b = qlist->data->insertAfterAbove(entry, p); // 新节点b即新塔基座
		while (rand() & 1) { // 经投掷硬币，若确定新塔需要再长高一层，则
			while (qlist->data->valid(p) && !p->above) { p = p->pred; } // 找出不低于此高度的最近前驱
			if (!qlist->data->valid(p)) { // 若该前驱是header
				if (qlist == ListType::first()) { // 且当前已是最顶层，则意味着必须
					ListType::insert_as_first(new QuadlistType()); // 首先创建新的一层，然后
				}
				p = qlist->pred->data->first()->pred; // 将p转至上一层skiplist的header
			} else { // 否则，可径自
				p = p->above; // 将p提升至该高度
			}
			qlist = qlist->pred; // 上升一层，并在该层
			b = qlist->data->insertAfterAbove(entry, p, b); // 将新节点插入p之后、b之上
		}
		return true;
	}

	//! 读取（有多个命中时靠后者优先）
	V* get(K k) {
		if (ListType::empty()) { return nullptr; }
		ListNodePtr qlist = ListType::first(); // 从定长Quadlist开始
		QuadlistNodePtr p = qlist->data->first(); // 首节点开始
		return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr; // 查找并报告
	}

	//! 删除
	bool remove(K k) {
		if (ListType::empty()) { return false; }
		ListNodePtr qlist = ListType::first(); // 从顶层Quadlist的
		QuadlistNodePtr p = qlist->data->first(); // 首节点开始
		if (!skipSearch(qlist, p, k)) { return false; } // 目标词条不存在
		do { // 若目标词条存在，则逐层拆除与之对应的塔
			QuadlistNodePtr lower = p->below; // 记住下一层节点，并
			qlist->data->remove(p); // 删除当前节点，再
			p = lower; qlist = qlist->succ; // 转入下一层
		} while (qlist->succ); // 如上不断重复，直到塔基
		while (!ListType::empty() && ListType::first()->data->empty()) { // 逐一地
			ListType::remove(ListType::first()); // 清除已可能不含词条的顶层Quadlist
		}
		return true;
	}
};

}
