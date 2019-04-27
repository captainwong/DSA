#pragma once

template <typename T>
ListNodePosi(T) List<T>::insert_as_first(T const& e)
{
	size_++;
	return header->insert_as_succ(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_as_last(T const& e)
{
	size_++;
	return trailer->insert_as_pred(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_after(ListNodePosi(T) p, T const& e)
{
	size_++;
	return p->insert_as_succ(e);
}


template <typename T>
ListNodePosi(T) List<T>::insert_before(ListNodePosi(T) p, T const& e)
{
	size_++;
	return p->insert_as_pred(e);
}




