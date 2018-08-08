#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::selection_sort(ListNodePosi(T) p, int n)
	{
		ListNodePosi(T) head = p->pred;
		ListNodePosi(T) tail = p;
		for (int i = 0; i < n; i++) {
			tail = tail->succ;
		}

		while (1 < n) {
			ListNodePosi(T) max_p = select_max(head->succ, n);
			insert_before(tail, remove(max_p));
			tail = tail->pred;
			n--;
		}
	}
};
