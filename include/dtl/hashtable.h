#pragma once

#include "bitmap.h"
#include "dictionary.h"
#include "entry.h"

//! ɢ�б�
template <typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
public:
	typedef Dictionary<K, V> DictionaryType;
	typedef Entry<K, V> EntryType;
	typedef EntryType* Bucket;
	typedef Bucket* Buckets;

	Hashtable(int c = 5);
	~Hashtable();

	//! ��ǰ������Ŀ
	int size() const { return N; }
	//! ���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
	bool put(K const& k, V const& v);
	//! ��ȡ
	V* get(K const& k);
	//! ɾ��
	bool remove(K const& k);

protected:
	//! �عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
	int probe4Hit(const K& k);
	//! �عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
	int probe4Free(const K& k);
	//! ��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
	void rehash();

	//bool lazilyRemoved()

private:
	//! Ͱ���飬��Ŵ���ָ��
	Buckets buckets;
	//! Ͱ��������
	int M;
	//! ��������
	int N;
	//! ����ɾ�����
	Bitmap* lazyRemoval;

};
