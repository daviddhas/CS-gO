#pragma once

#include "types.hpp"
#include "unqualified.hpp"

namespace csgo { namespace meta {

	template<typename T>
	struct bare_naked {
		typedef std::remove_cv_t<std::remove_all_extents_t<unqualified_t<std::remove_pointer_t<unqualified_t<T>>>>> type;
	};

	template<typename T>
	struct bare_naked<std::reference_wrapper<T>> {
		typedef std::remove_all_extents_t<unqualified_t<std::remove_pointer_t<T>>> type;
	};

	template<typename T>
	using bare_naked_t = invoke_t<bare_naked<T>>;

}}
