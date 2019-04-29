#pragma once

namespace dtl
{

template <typename T>
struct Increase
{
	virtual void operator()(T& e) {
		e++;
	}
};

}
