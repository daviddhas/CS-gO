#pragma once

#include "types.hpp"
#include "unqualified.hpp"
#include <functional>

namespace csgo { namespace meta {

	template <typename T>
	struct unwrap {
		typedef T type;
	};

	template <typename T>
	struct unwrap<std::reference_wrapper<T>> {
		typedef T& type;
	};

	template <typename T>
	using unwrap_t = invoke_t<unwrap<T>>;

	template <typename T>
	struct unqualified_unwrap {
		typedef unqualified_t<unwrap_t<unqualified_t<T>>> type;
	};

	template <typename T>
	using unqualified_unwrap_t = invoke_t<unqualified_unwrap<T>>;

}}
