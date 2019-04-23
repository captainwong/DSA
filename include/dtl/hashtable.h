#pragma once

#include "bitmap.h"
#include "dictionary.h"
#include "entry.h"
#include "release.h"

namespace dtl 
{

//! 散列表
template <typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
public:
	typedef Dictionary<K, V> DictionaryType;
	typedef Entry<K, V> EntryType;
	typedef EntryType* Bucket;
	typedef Bucket* Buckets;

	Hashtable(int c = 5) 
		: M(c)
		, N(0)
	{
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
	int size() const { return N; }
	//! 插入（禁止雷同词条，故可能失败）
	bool put(K const& k, V const& v);
	//! 读取
	V* get(K const& k);
	//! 删除
	bool remove(K const& k);

protected:
	//! 沿关键码k对应的查找链，找到词条匹配的桶
	int probe4Hit(const K& k);
	//! 沿关键码k对应的查找链，找到首个可用空桶
	int probe4Free(const K& k);
	//! 重散列算法：扩充桶数组，保证装填因子在警戒线以下
	void rehash();

	//bool lazilyRemoved()

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
