#pragma once

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}