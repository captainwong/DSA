#pragma once

template <typename T>
T& List<T>::operator[] (Rank r) const
{
	assert(0 <= r && r < _size);
	ListNodePosi(T) p = first();
	while (r--) {
		p = p->succ;
	}
	return p->data;
}

template <typename T>
int List<T>::clear()
{
	int old_size = _size;
	while (0 < _size) {
		remove(header->succ);
	}
	return old_size;
}

template <typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->pred = NULL;
	header->succ = trailer;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template <typename T>
void List<T>::copy_nodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--) {
		insert_as_last(p->data);
		p = p->succ;
	}
}

template <typename T>
List<T>::List(List<T> const& L)
{
	copy_nodes(L.first(), L._size);
}


template <typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
	copy_nodes(L[r], n);
}


template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copy_nodes(p, n);
}

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template <typename T>
ListNodePosi(T) List<T>::insert_as_first(T const& e)
{
	_size++;
	return header->insert_as_succ(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_as_last(T const& e)
{
	_size++;
	return trailer->insert_as_pred(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_after(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insert_as_succ(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_before(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insert_as_pred(e);
}

template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	assert(valid(p));

	while (n--) {
		if ((p = p->pred)->data == e) {
			return p;
		}
	}
	return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
	if (_size == 0)
		return NULL;
	//assert(valid(p));
	assert(0 <= n && n <= _size);

	while (n-- && p != header->succ) {
		if ((p = p->pred)->data <= e) {
			break;
		}
	}
	return p;
}

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

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	merge_sort(p, n);
}

template <typename T>
void List<T>::insertion_sort(ListNodePosi(T) p, int n)
{
	for (int sorted = 0; sorted < n; sorted++) {
		insert_after(search(p->data, sorted, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template <typename T>
ListNodePosi(T) List<T>::select_max(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max_p = p;
	for (ListNodePosi(T) cur = p; 1 < n; n--) {
		if ((cur = cur->succ)->data >= max_p->data) {
			max_p = cur;
		}
	}
	return max_p;
}

template <typename T>
void List<T>::selection_sort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) {
		tail = tail->succ;
	}

	while (1 < n) {
		ListNodePosi(T) max_p = select_max(head->succ, n);
		insert_before(tail, remove(max_p));
		tail = tail->pred;
		n--;
	}
}

template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;
	while (0 < m) {
		if ((0 < n) && p->data <= q->data) {
			if (q == (p = p->succ)) {
				break;
			}
			n--;
		} else {
			insert_before(p, L.remove((q = q->succ)->pred));
			m--;
		}
	}
	p = pp->succ;
}

template <typename T>
void List<T>::merge_sort(ListNodePosi(T)& p, int n)
{
	if (n < 2)
		return;

	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++) {
		q = q->succ;
	}

	merge_sort(p, m);
	merge_sort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template <typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
		return 0;

	int old_size = _size;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while ((p = p->succ) != trailer) {
		find(p->data, r, p) ? remove(p) : r++;
	}
	return old_size - _size;
}

template <typename T>
int List<T>::disordered() const
{
	if (0 == _size) {
		return 0;
	}

	int sum = 0;
	ListNodePosi(T) p = first();
	for (int i = 0; i < _size - 1; p = p->succ, i++) {
		if (p->data > p->succ->data) {
			sum++;
		}
	}

	return sum;
}

template <typename T>
int List<T>::uniquify()
{
	if (_size < 2)
		return 0;

	int old_size = _size;
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;
	while ((q = p->succ) != trailer) {
		if (q->data != p->data) {
			p = q;
		} else {
			remove(q);
		}
	}

	return old_size - _size;
}
















