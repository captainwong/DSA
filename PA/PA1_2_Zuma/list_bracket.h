#pragma once


template <typename T>
T& List<T>::operator[] (Rank r) const
{
	assert(0 <= r && r < size_);
	ListNodePosi(T) p = first();
	while (r--) {
		p = p->succ;
	}
	return p->data;
}
