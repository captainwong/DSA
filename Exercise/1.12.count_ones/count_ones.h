#pragma once

#include <type_traits>

template <typename UnsignedInteger>
typename std::enable_if_t<std::is_integral_v<UnsignedInteger> && std::is_unsigned_v<UnsignedInteger>, std::size_t>
count_ones(UnsignedInteger n)
{
	for (std::size_t i = 0; i < sizeof(n) * 8; i += 8) {

	}
}