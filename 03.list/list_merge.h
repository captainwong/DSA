#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
	{
		ListNodePosi(T) pp = p->pred;
		while (0 < m) {
			if ((0 < n) && p->data <= q->data) {
				if (q == (p = p->succ)) {
					break;
				}
				n--;
			} else {
				insert_before(p, L.remove((q = q->succ)->pred));
				m--;
			}
		}
		p = pp->succ;
	}
};
