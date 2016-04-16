#pragma once

#include <csgo/dsl/type.hpp>
#include <csgo/dsl/expression.hpp>
#include <csgo/type_traits.hpp>
#include <cstddef>

namespace csgo {
	namespace dsl {

		struct variable : expression {
			type variable_type;

			variable() : variable_type(type::user_defined_type) {}
			variable(type vartype) : variable_type(vartype) {}

			virtual ~variable() {}
		};

		template <typename T>
		struct is_variable : std::is_base_of<variable, meta::unqualified_t<T>> {};
		
		template <typename T>
		struct is_expression : meta::all<std::is_base_of<expression, meta::unqualified_t<T>>, meta::not_<std::is_base_of<variable, meta::unqualified_t<T>>>> {};

		template <typename T>
		struct type_for : std::integral_constant<type, type::user_defined_type> {};

		template <>
		struct type_for<int32_t> : std::integral_constant<type, type::integer> {};

		template <>
		struct type_for<uint32_t> : std::integral_constant<type, type::unsigned_integer> {};

		template <>
		struct type_for<bool> : std::integral_constant<type, type::boolean> {};

		template <>
		struct type_for<float> : std::integral_constant<type, type::single_precision> {};

		template <>
		struct type_for<double> : std::integral_constant<type, type::double_precision> {};

	}
}
