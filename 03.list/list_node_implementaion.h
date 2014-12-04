#pragma once 

namespace JTL // Jack's template library
{
	template <typename T>
	ListNodePosi(T) ListNode<T>::insert_as_pred(T const& e)
	{
		ListNodePosi(T) pos = new ListNode(e, pred, this);
		pred->succ = pos;
		pred = pos;
		return pos;
	}


	template <typename T>
	ListNodePosi(T) ListNode<T>::insert_as_succ(T const& e)
	{
		ListNodePosi(T) pos = new ListNode<T>(e, this, succ);
		succ->pred = pos;
		succ = pos;
		return pos;
	}

};
