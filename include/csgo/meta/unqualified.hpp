#pragma once

#include <type_traits>

namespace csgo { namespace meta {

	template<typename T>
	struct unqualified {
		typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
	};

	template <typename T>
	using unqualified_t = typename unqualified<T>::type;

}}
