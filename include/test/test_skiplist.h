#pragma once

#include "../util/util.h"
#include "../dtl/skiplist.h"

namespace dtl
{
namespace test
{

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

}
}
