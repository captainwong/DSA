#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	int List<T>::clear()
	{
		int old_size = _size;
		while (0 < _size) {
			remove(header->succ);
		}
		return old_size;
	}
};
