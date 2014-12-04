#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	T& List<T>::operator[] (Rank r) const
	{
		assert(0 <= r && r < _size);
		ListNodePosi(T) p = first();
		while (r--) {
			p = p->succ;
		}
		return p->data;
	}
};