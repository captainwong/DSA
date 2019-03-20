#pragma once

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

