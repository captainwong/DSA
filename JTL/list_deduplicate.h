#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	int List<T>::deduplicate()
	{
		if (_size < 2)
			return 0;

		int old_size = _size;
		ListNodePosi(T) p = header;
		Rank r = 0;
		while ((p = p->succ) != trailer) {
			find(p->data, r, p) ? remove(p) : r++;
		}
		return old_size - _size;
	}
};
