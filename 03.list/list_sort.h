#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::sort(ListNodePosi(T) p, int n)
	{
		merge_sort(p, n);
	}
};
