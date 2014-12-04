#pragma once 

namespace JTL // Jack's template library
{
	template <typename T>
	void List<T>::copy_nodes(ListNodePosi(T) p, int n)
	{
		init();
		while (n--) {
			insert_as_last(p->data);
			p = p->succ;
		}
	}



};
