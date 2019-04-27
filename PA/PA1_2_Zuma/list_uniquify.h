#pragma once

template <typename T>
int List<T>::uniquify()
{
	if (size_ < 2)
		return 0;

	int old_size = size_;
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;
	while ((q = p->succ) != trailer) {
		if (q->data != p->data) {
			p = q;
		} else {
			remove(q);
		}
	}

	return old_size - size_;
}
