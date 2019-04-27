#pragma once

template <typename T>
int List<T>::clear()
{
	int old_size = size_;
	while (0 < size_) {
		remove(header->succ);
	}
	return old_size;
}

