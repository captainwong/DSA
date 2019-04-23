// 09.skiplist.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/skiplist.h"
#include "../../include/util/util.h"


using namespace dtl;

template <typename K, typename V>
void testSkiplist(int n)
{
	Skiplist<K, V> list;
	while (list.size() < n) {
		switch (dice(3)) {
			case 0: // 查找，成功率 <= 33.3%
			{
				K key = dice(static_cast<K>(n) * 3); // [0, 3n)
				printf("Searching for "); print(key); printf(" ... ");
				V* value = list.get(key);
				if (value) {
					printf("found with "), print(*value);
				} else {
					printf("Not found!");
				}
				printf("\n");
				break;
			}
			case 1: // 删除，成功率 <= 33.3%
			{
				K key = dice(static_cast<K>(n) * 3); // [0, 3n)
				printf("Removing "); print(key); printf(" ... ");
				list.remove(key) ? printf("Done\n") : printf("Entry not exists\n");
				print(list);
				break;
			}
			default: // 插入，成功率 == 100%
			{
				K k = dice(static_cast<K>(n) * 3); // [0, 3n)
				V v = static_cast<V>('A' + dice(26)); // [A,Z]
				printf("Inserting <"); print(k); printf(","); print(v); printf(">...");
				list.put(k, v); printf("Done\n");
				print(list);
				break;
			}
		}
	}

	while (!list.empty()) {
		K key = dice(static_cast<K>(n) * 3); // [0, 3n)
		printf("Removing "); print(key); printf(" ... ");
		list.remove(key) ? printf("Done\n") : printf("Entry not exists\n");
		print(list);
	}
}


int main()
{
	srand_time();
	testSkiplist<int, char>(3);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
