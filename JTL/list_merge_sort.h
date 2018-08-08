#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::merge_sort(ListNodePosi(T)& p, int n)
	{
		if (n < 2)
			return;

		int m = n >> 1;
		ListNodePosi(T) q = p;
		for (int i = 0; i < m; i++) {
			q = q->succ;
		}

		merge_sort(p, m);
		merge_sort(q, n - m);
		merge(p, m, *this, q, n - m);
	}
};
