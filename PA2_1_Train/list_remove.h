#pragma once

template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	assert(valid(p));
	T data = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return data;
}

