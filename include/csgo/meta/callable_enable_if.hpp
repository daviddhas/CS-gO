#pragma once

#include "sfinae_types.hpp"

namespace csgo { namespace meta {

	template <typename T, typename TR, typename ... TArgs>
	struct has_callable {
		typedef sfinae_small_t yes;
		typedef sfinae_big_t no;
		
		template<typename C, TR (C::*)( TArgs... ) const> struct SFINAE {};

		template <typename C>
		static yes& test(SFINAE<C, &C::operator()>*);

		template <typename>
		static no& test(...);

		static const bool value = sizeof(test<T>(0)) == sizeof(yes);
	};

}}
