#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::insertion_sort(ListNodePosi(T) p, int n)
	{
		for (int sorted = 0; sorted < n; sorted++) {
			insert_after(search(p->data, sorted, p), p->data);
			p = p->succ;
			remove(p->pred);
		}
	}
};
