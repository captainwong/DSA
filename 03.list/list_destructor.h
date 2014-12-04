#pragma once

namespace JTL // Jack's template library
{
	template <typename T>
	List<T>::~List()
	{
		clear();
		delete header;
		delete trailer;
	}
};
