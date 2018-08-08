#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
	{
		assert(valid(p));

		while (n--) {
			if ((p = p->pred)->data == e) {
				return p;
			}
		}
		return NULL;
	}

};
