#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	ListNodePosi(T) List<T>::select_max(ListNodePosi(T) p, int n)
	{
		ListNodePosi(T) max_p = p;
		for (ListNodePosi(T) cur = p; 1 < n; n--) {
			if ((cur = cur->succ)->data >= max_p->data) {
				max_p = cur;
			}
		}
		return max_p;
	}

};
