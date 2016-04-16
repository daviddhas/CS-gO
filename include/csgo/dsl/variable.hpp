#pragma once

#include <csgo/dsl/type.hpp>
#include <csgo/dsl/expression.hpp>
#include <csgo/type_traits.hpp>
#include <glm/glm.hpp>
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

		template <>
		struct type_for<glm::vec2> : std::integral_constant<type, type::single_vector_2> {};

		template <>
		struct type_for<glm::vec3> : std::integral_constant<type, type::single_vector_3> {};

		template <>
		struct type_for<glm::vec4> : std::integral_constant<type, type::single_vector_4> {};

		template <>
		struct type_for<glm::mat2x2> : std::integral_constant<type, type::single_matrix_22> {};

		template <>
		struct type_for<glm::mat2x3> : std::integral_constant<type, type::single_matrix_23> {};

		template <>
		struct type_for<glm::mat2x4> : std::integral_constant<type, type::single_matrix_24> {};

		template <>
		struct type_for<glm::mat3x2> : std::integral_constant<type, type::single_matrix_32> {};

		template <>
		struct type_for<glm::mat3x3> : std::integral_constant<type, type::single_matrix_33> {};

		template <>
		struct type_for<glm::mat3x4> : std::integral_constant<type, type::single_matrix_34> {};

		template <>
		struct type_for<glm::mat4x2> : std::integral_constant<type, type::single_matrix_42> {};

		template <>
		struct type_for<glm::mat4x3> : std::integral_constant<type, type::single_matrix_43> {};

		template <>
		struct type_for<glm::mat4x4> : std::integral_constant<type, type::single_matrix_44> {};

		template <>
		struct type_for<glm::dmat2x2> : std::integral_constant<type, type::double_matrix_22> {};

		template <>
		struct type_for<glm::dmat2x3> : std::integral_constant<type, type::double_matrix_23> {};

		template <>
		struct type_for<glm::dmat2x4> : std::integral_constant<type, type::double_matrix_24> {};

		template <>
		struct type_for<glm::dmat3x2> : std::integral_constant<type, type::double_matrix_32> {};

		template <>
		struct type_for<glm::dmat3x3> : std::integral_constant<type, type::double_matrix_33> {};

		template <>
		struct type_for<glm::dmat3x4> : std::integral_constant<type, type::double_matrix_34> {};

		template <>
		struct type_for<glm::dmat4x2> : std::integral_constant<type, type::double_matrix_42> {};

		template <>
		struct type_for<glm::dmat4x3> : std::integral_constant<type, type::double_matrix_43> {};

		template <>
		struct type_for<glm::dmat4x4> : std::integral_constant<type, type::double_matrix_44> {};

	}
}
