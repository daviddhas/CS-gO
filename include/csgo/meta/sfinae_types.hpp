#pragma once

#include <array>

namespace csgo { namespace meta {

	typedef std::array<char, 1> sfinae_small_t;
	typedef std::array<char, 2> sfinae_big_t;

}}
