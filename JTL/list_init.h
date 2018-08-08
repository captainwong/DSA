#pragma once

namespace JTL // Jack's template library
{
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
};
