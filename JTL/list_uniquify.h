#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	int List<T>::uniquify()
	{
		if (_size < 2)
			return 0;

		int old_size = _size;
		ListNodePosi(T) p = first();
		ListNodePosi(T) q;
		while ((q = p->succ) != trailer) {
			if (q->data != p->data) {
				p = q;
			} else {
				remove(q);
			}
		}

		return old_size - _size;
	}
};
