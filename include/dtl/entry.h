#pragma once

namespace dtl 
{

//! 词条
template <typename K, typename V>
struct Entry
{
	//! 关键码
	K key;
	//! 数值
	V value;

	Entry(K k = K(), V v = V())
		: key(k)
		, value(v)
	{}

	Entry(const Entry& rhs)
		: key(rhs.key)
		, value(rhs.value)
	{}

	bool operator<(const Entry& rhs) { return key < rhs.key; }
	bool operator>(const Entry& rhs) { return key > rhs.key; }
	bool operator==(const Entry& rhs) { return key == rhs.key; }
	bool operator!=(const Entry& rhs) { return key == rhs.key; }
};

}
