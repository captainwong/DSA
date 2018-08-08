#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
	{
		if (_size == 0)
			return NULL;
		//assert(valid(p));
		assert(0 <= n && n <= _size);

		while (n-- && p != header->succ) {
			if ((p = p->pred)->data <= e) {
				break;
			}
		}
		return p;
	}

};
