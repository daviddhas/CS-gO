#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/type_traits.hpp>

namespace csgo {
	namespace dsl {

		// Things such as int, float, etc.
		struct constant : variable {
			
			constant(type x) : variable(x) {}

		};

		template <typename T>
		struct typed_constant : constant {
			T value;

			typed_constant(T value) : typed_constant(value, type_for<T>::value) {}
			typed_constant(T value, type x) : constant(x), value(value) {}
		};

		template <typename T>
		struct is_primitive : std::is_arithmetic<meta::unqualified_t<T>> {};

	}
}
