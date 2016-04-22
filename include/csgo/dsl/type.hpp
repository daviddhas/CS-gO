#pragma once

#include <csgo/optional.hpp>
#include <csgo/type_traits.hpp>
#include <csgo/enums.hpp>
#include <csgo/qualifiers.hpp>
#include <glm/glm.hpp>
#include <string>

namespace csgo {
	namespace dsl {

		enum class type {
			// scalar types
			boolean,
			byte,
			signed_byte,
			integer_16,
			unsigned_integer_16,
			integer,
			unsigned_integer,
			single_precision,
			double_precision,

			boolean_vector_2,
			boolean_vector_3,
			boolean_vector_4,
			integer_vector_2,
			integer_vector_3,
			integer_vector_4,
			unsigned_integer_vector_2,
			unsigned_integer_vector_3,
			unsigned_integer_vector_4,
			single_vector_2,
			single_vector_3,
			single_vector_4,
			double_vector_2,
			double_vector_3,
			double_vector_4,

			single_matrix_22,
			single_matrix_23,
			single_matrix_24,
			single_matrix_32,
			single_matrix_33,
			single_matrix_34,
			single_matrix_42,
			single_matrix_43,
			single_matrix_44,

			double_matrix_22,
			double_matrix_23,
			double_matrix_24,
			double_matrix_32,
			double_matrix_33,
			double_matrix_34,
			double_matrix_42,
			double_matrix_43,
			double_matrix_44,

			// resource types
			image_1d,
			image_2d,
			image_3d,
			image_cube,
			image_2d_rect,
			image_1d_array,
			image_2d_array,
			image_cube_array,
			image_buffer,
			image_2d_multisample,
			image_2d_multisample_array,

			// composite types
			user_defined_type,

		};

		const std::string& to_string(type x) {
			static const std::string strs[] = {
				// scalar types
				"boolean",
				"byte",
				"signed_byte",
				"integer_16",
				"unsigned_integer_16",
				"integer",
				"unsigned_integer",
				"single_precision",
				"double_precision",

				"boolean_vector_2",
				"boolean_vector_3",
				"boolean_vector_4",
				"integer_vector_2",
				"integer_vector_3",
				"integer_vector_4",
				"unsigned_integer_vector_2",
				"unsigned_integer_vector_3",
				"unsigned_integer_vector_4",
				"single_vector_2",
				"single_vector_3",
				"single_vector_4",
				"double_vector_2",
				"double_vector_3",
				"double_vector_4",

				"single_matrix_22",
				"single_matrix_23",
				"single_matrix_24",
				"single_matrix_32",
				"single_matrix_33",
				"single_matrix_34",
				"single_matrix_42",
				"single_matrix_43",
				"single_matrix_44",

				"double_matrix_22",
				"double_matrix_23",
				"double_matrix_24",
				"double_matrix_32",
				"double_matrix_33",
				"double_matrix_34",
				"double_matrix_42",
				"double_matrix_43",
				"double_matrix_44",

				// resource types
				"image_1d",
				"image_2d",
				"image_3d",
				"image_cube",
				"image_2d_rect",
				"image_1d_array",
				"image_2d_array",
				"image_cube_array",
				"image_buffer",
				"image_2d_multisample",
				"image_2d_multisample_array",

				// composite types
				"user_defined_type",
			};

			return strs[enums::to_underlying(x)];
		}

		struct type_result {
			type result;
			optional<qualifiers> layout;
		};

		inline bool is_image_type(type t) {
			switch (t) {
			case type::image_1d:
			case type::image_1d_array:
			case type::image_2d:
			case type::image_2d_array:
			case type::image_2d_multisample:
			case type::image_2d_multisample_array:
			case type::image_2d_rect:
			case type::image_buffer:
			case type::image_cube:
			case type::image_cube_array:
				return true;
			default:
				return false;
			}
		}

		inline bool is_vector_type(type t) {
			switch (t) {
			case type::boolean_vector_2:
			case type::boolean_vector_3:
			case type::boolean_vector_4:
			case type::single_vector_2:
			case type::single_vector_3:
			case type::single_vector_4:
			case type::integer_vector_2:
			case type::integer_vector_3:
			case type::integer_vector_4:
			case type::unsigned_integer_vector_2:
			case type::unsigned_integer_vector_3:
			case type::unsigned_integer_vector_4:
			case type::double_vector_2:
			case type::double_vector_3:
			case type::double_vector_4:
				return true;
			default:
				return false;
			}
		}

		inline bool is_matrix_type(type t) {
			switch (t) {
			case type::double_matrix_22:
			case type::double_matrix_23:
			case type::double_matrix_24:
			case type::double_matrix_32:
			case type::double_matrix_33:
			case type::double_matrix_34:
			case type::double_matrix_42:
			case type::double_matrix_43:
			case type::double_matrix_44:
			case type::single_matrix_22:
			case type::single_matrix_23:
			case type::single_matrix_24:
			case type::single_matrix_32:
			case type::single_matrix_33:
			case type::single_matrix_34:
			case type::single_matrix_42:
			case type::single_matrix_43:
			case type::single_matrix_44:
				return true;
			default:
				return false;
			}
		}

		template <typename T>
		struct type_for : std::integral_constant<type, type::user_defined_type> {};

		template <>
		struct type_for<int8_t> : std::integral_constant<type, type::signed_byte> {};

		template <>
		struct type_for<uint8_t> : std::integral_constant<type, type::byte> {};

		template <>
		struct type_for<int16_t> : std::integral_constant<type, type::integer_16> {};

		template <>
		struct type_for<uint16_t> : std::integral_constant<type, type::unsigned_integer_16> {};

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
		struct type_for<glm::dvec2> : std::integral_constant<type, type::double_vector_2> {};

		template <>
		struct type_for<glm::dvec3> : std::integral_constant<type, type::double_vector_3> {};

		template <>
		struct type_for<glm::dvec4> : std::integral_constant<type, type::double_vector_4> {};

		template <>
		struct type_for<glm::ivec2> : std::integral_constant<type, type::integer_vector_2> {};

		template <>
		struct type_for<glm::ivec3> : std::integral_constant<type, type::integer_vector_3> {};
		
		template <>
		struct type_for<glm::ivec4> : std::integral_constant<type, type::integer_vector_4> {};

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

		template <typename T>
		struct name_for { static const std::string value; };

		template <typename T>
		const std::string name_for<T>::value = to_string(type_for<T>::value);

	}
}
