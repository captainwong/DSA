#pragma once

namespace JTL // Jack's template library
{
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


};

