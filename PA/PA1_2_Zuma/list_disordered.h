#pragma once

template <typename T>
int List<T>::disordered() const
{
	if (0 == size_) {
		return 0;
	}

	int sum = 0;
	ListNodePosi(T) p = first();
	for (int i = 0; i < size_ - 1; p = p->succ, i++) {
		if (p->data > p->succ->data) {
			sum++;
		}
	}

	return sum;
}
