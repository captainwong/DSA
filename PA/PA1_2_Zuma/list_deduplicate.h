#pragma once

template <typename T>
int List<T>::deduplicate()
{
	if (size_ < 2)
		return 0;

	int old_size = size_;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while ((p = p->succ) != trailer) {
		find(p->data, r, p) ? remove(p) : r++;
	}
	return old_size - size_;
}
