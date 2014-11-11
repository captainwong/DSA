#pragma once

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
	assert(valid(p));

	while (n-- && p != header->succ) {
		if ((p = p->pred)->data <= e) {
			break;
		}
	}
	return NULL;
}

