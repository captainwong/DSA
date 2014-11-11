#pragma once

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	merge_sort(p, n);
}
