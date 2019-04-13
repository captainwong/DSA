#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct village;
typedef village* pvillage;
struct villages
{
	pvillage * vector = new pvillage[2];
	int size = 0;
	int capacity = 2;

	int add(village* v) {
		expand();
		vector[size] = v;
		return size++;
	}

	void expand() {
		if (capacity == size) {
			capacity <<= 1;
			auto old = vector;
			vector = new pvillage[capacity];
			memcpy(vector, old, capacity >> 1);
			delete[] old;
		}
	}

	pvillage operator[](int index) {
		return vector[index];
	}
};

struct village
{
	// 村庄编号
	int v = 0;

	// 可以直接前往的下游村庄
	villages dsts = {};
	int longest_dst_index = -1;

	// 下游最长的道路链长度
	int length = 0;

	// 上游村庄
	villages srcs = {};


	// 添加可以前往的村庄
	int add_village(village* dst) {
		int index = dsts.add(dst);
		if (longest_dst_index == -1) {
			longest_dst_index = 0;
		} else if (dsts[longest_dst_index]->length < dst->length) {
			longest_dst_index = index;
		}

		length = dsts[longest_dst_index]->length + 1;
		
		dst->srcs.add(this);

		return update_srcs_length();
	}

	int update_srcs_length() {
		int longest_src_length = length;
		for (int i = 0; i < srcs.size; i++) {
			auto src = srcs[i];
			if (src->dsts[src->longest_dst_index]->length <= length) {
				for (int j = 0; j < src->dsts.size; j++) {
					if (src->dsts[j] == this) {
						src->longest_dst_index = j;
						longest_src_length = src->length = length + 1;
						break;
					}
				}

				longest_src_length = src->update_srcs_length();
			} 
		}

		return longest_src_length;
	}


};

constexpr int MAX_VILLAGE = 1000000;
village g_villages[MAX_VILLAGE + 10] = {};
//bool g_village_exists[MAX_VILLAGE + 1] = { false };

int main_ac35(int /*argc*/, char** /*argv*/)
{
	int n, m;
	if (scanf("%d %d\n", &n, &m) == EOF)
		return 0;

	// 当前最长通路的起源村庄
	//pvillage longest_root_v = &g_villages[0];

	int length = 0;

	int v1, v2;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d", &v1, &v2) == EOF)
			return 0;

		if (v1 > n || v2 > n) { return 0; }

		auto src = &g_villages[v1];
		src->v = v1;

		auto dst = &g_villages[v2];
		dst->v = v2;

		int len = src->add_village(dst);
		if (length < len) {
			length = len;
		}
	}

	printf("%d\n", length + 1); // 加上自己
	
	return 0;
}

