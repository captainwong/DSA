// 09.hashtable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/hashtable.h"
#include "../../include/util/util.h"

using namespace dtl;

/******************************************************************************************
 * 测试散列表
 ******************************************************************************************/
template <typename K, typename V> //key、value
void testHashtable(int n) {
	Hashtable<K, V> ht(n); print(ht);
	while (ht.size() < 4 * n) {
		printf("\n");
		switch (dice(3)) {
			case 0:
			{ //查找，成功率 <= 33.3%
				K key = dice((K)n * 12); //[0, 3n)范围内的key
				printf("Searching "); print(key); printf("(%04d) :\n", hashCode(key));
				V* pValue = ht.get(key);
				if (pValue) { printf("Found with "); print(*pValue); }
				else { printf("Not found"); }
				printf("\n");
				break;
			}
			case 1:
			{ //删除，成功率 <= 33.3%
				K key = dice((K)n * 12); //[0, 3n)范围内的key
				printf("Removing "); print(key); printf("(%04d) :\n", hashCode(key));
				if (ht.remove(key)) { printf("Done\n"), print(ht); }
				else { printf("Entry not exists\n"); }
				break;
			}
			default:
			{//插入，成功率 == 100%
				K key = dice((K)n * 12); V v = (V) 'A' + dice(26); //在[0, 2n)*['A'~'Z']范围内的词条
				printf("Inserting <"); print(key); printf("(%04d)", hashCode(key)); printf(","); print(v); printf(">\n");
				if (ht.put(key, v)) { printf("Done\n"), print(ht); }
				else { printf("Dup key\n"); }
				break;
			}
		} //switch
	} //while
	while (ht.size() > 0) {
		printf("\n");
		K key = dice((K)n * 12); //[0, 3n)范围内的key
		printf("Removing "); print(key); printf(" :\n");
		if (ht.remove(key)) { printf("Done\n"), print(ht); }
		else { printf("Entry not exists\n"); }
	}
}


int main()
{
	srand_time();
	testHashtable<int, char>(5);
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
