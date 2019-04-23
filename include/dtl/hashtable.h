#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "bitmap.h"
#include "dictionary.h"
#include "entry.h"
#include "prime.h"
#include "release.h"
#include <string.h> // strlen, memset

namespace dtl 
{

/**************散列函数*************/

//! 通用散列函数模板
template <typename T>
inline size_t hashCode(T t) { return static_cast<size_t>(t); }

//! long long 偏特化
template <>
inline size_t hashCode(long long i) { return static_cast<size_t>((i >> 32) + static_cast<int>(i)); }

//! 字符串偏特化
template <>
inline size_t hashCode(const char* s) {
	int h = 0;
	for (size_t n = strlen(s), i = 0; i < n; i++) {
		h = (h << 5) | (h >> 27); // 散列码循环左移5位
		h += static_cast<int>(s[i]); // 再累加当前字符
	}
	return static_cast<size_t>(h); // 如此所得的散列码，实际上可理解为近似的“多项式散列码”
} // 对于英语单词，"循环左移5位"是实验统计得出的最佳值



//! 散列表
template <typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
	friend class UniPrint;
public:
	typedef Dictionary<K, V> DictionaryType;
	typedef Entry<K, V> EntryType;
	typedef EntryType* Bucket;
	typedef Bucket* Buckets;

	Hashtable(int c = 5)
	{
		M = primeNLT(c, 1048576);
		N = 0;
		buckets = new Bucket[M];
		memset(buckets, 0, sizeof(Bucket) * M);
		lazyRemoval = new Bitmap(M);
	}

	~Hashtable() {
		for (int i = 0; i < M; i++) {
			if (buckets[i]) { release(buckets[i]); }
		}
		release(buckets);
		release(lazyRemoval);
	}

	//! 当前词条数目
	virtual int size() const override { return N; }

	//! 插入（禁止雷同词条，故可能失败）
	virtual bool put(K const& k, V const& v) override {
		if (buckets[probe4Hit(k)]) { return false; } // 雷同元素不必重复插入
		int r = probe4Free(k); // 为新词条找个空桶（只要装填因子控制得当，必然成功）
		buckets[r] = new EntryType(k, v); ++N; // 插入（注意：懒惰删除标记无需复位）
		if (N * 2 > M) { rehash(); } // 装填因子高于50%后重散列
		return true;
	}

	//! 读取
	virtual V* get(K const& k) override {
		int r = probe4Hit(k);
		return buckets[r] ? &(buckets[r]->value) : nullptr;
	}

	//! 删除
	virtual bool remove(K const& k) override {
		int r = probe4Hit(k); if (!buckets[r]) { return false; } // 对应词条不存在时，无法删除
		release(buckets[r]); buckets[r] = nullptr; // //否则释放桶中词条，设置懒惰删除标记，并更新词条总数
		markAsRemoved(r); --N; return true;
	}

protected:
	//! 沿关键码k对应的查找链，找到词条匹配的桶（供查找和删除词条时调用）
	int probe4Hit(const K& k) { // 试探策略多种多样，可灵活选取；这里仅以线性试探策略为例
		int r = hashCode(k) % M; // 从起始桶（按除余法确定）出发
		while ((buckets[r] && (k != buckets[r]->key)) || (!buckets[r] && lazilyRemoved(r))) {
			r = (r + 1) % M; // 沿查找链线性试探：跳过所有冲突的桶，以及带懒惰删除标记的桶
		}
		return r; // 调用者根据ht[r]是否为空，即可判断查找是否成功
	}

	//! 沿关键码k对应的查找链，找到首个可用空桶
	int probe4Free(const K& k) { // 试探策略多种多样，可灵活选取；这里仅以线性试探策略为例
		int r = hashCode(k) % M; // 从起始桶（按除余法确定）出发
		while (buckets[r]) { r = (r + 1) % M; } // 沿查找链逐桶试探，直到首个空桶（无论是否带有懒惰删除标记）
		return r; // 为保证空桶总能找到，装填因子及散列表长需要合理设置
	}

	/**
	* @brief 重散列算法：扩充桶数组，保证装填因子在警戒线以下
	* @note 装填因子过大时，采取“逐一取出再插入”的朴素策略，对桶数组扩容
	*	不可简单地（通过memcpy()）将原桶数组复制到新桶数组（比如前端），否则存在两个问题：
	*	1）会继承原有冲突；
	*	2）可能导致查找链在后端断裂——即便为所有扩充桶设置懒惰删除标志也无济于事
	*/
	void rehash() {
		int oldM = M; Buckets oldBuckets = buckets;
		M = primeNLT(2 * M, 1048576);
		N = 0;
		buckets = new Bucket[M];
		memset(buckets, 0, sizeof(Bucket) * M);
		lazyRemoval->destroy();
		lazyRemoval->init(M);
		for (int i = 0; i < oldM; i++) {
			if (oldBuckets[i]) {
				put(oldBuckets[i]->key, oldBuckets[i]->value);
			}
		}
		release(oldBuckets);
	}

	bool lazilyRemoved(int r) const { return lazyRemoval->test(r); }
	void markAsRemoved(int r) { lazyRemoval->set(r); }

private:
	//! 桶数组，存放词条指针
	Buckets buckets;
	//! 桶数组容量
	int M;
	//! 词条数量
	int N;
	//! 懒惰删除标记
	Bitmap* lazyRemoval;

};

}
