#pragma once

#include <csgo/enums.hpp>
#include <csgo/format_qualifier.hpp>
#include <csgo/memory_qualifier.hpp>
#include <csgo/dsl/type.hpp>

namespace csgo {
	namespace glsl {

		const std::string& to_string(dsl::type x) {
			static const std::string strs[] = {
				// scalar types
				"bool",
				"unsupported_byte",
				"unsupported_signed_byte",
				"unsupported_int16",
				"unsupported_uint16",
				"int",
				"uint",
				"float",
				"double",

				"bvec2",
				"bvec3",
				"bvec4",
				"ivec2",
				"ivec3",
				"ivec4",
				"uvec2",
				"uvec3",
				"uvec4",
				"vec2",
				"vec3",
				"vec4",
				"dvec2",
				"dvec3",
				"dvec4",

				"mat2x2",
				"mat2x3",
				"mat2x4",
				"mat3x2",
				"mat3x3",
				"mat3x4",
				"mat4x2",
				"mat4x3",
				"mat4x4",

				"dmat2x2",
				"dmat2x3",
				"dmat2x4",
				"dmat3x2",
				"dmat3x3",
				"dmat3x4",
				"dmat4x2",
				"dmat4x3",
				"dmat4x4",

				// resource types
				"image2D",
				"image2D",
				"image3D",
				"imageCube",
				"image2DRect",
				"image1DArray",
				"image2DArray",
				"imageCubeArray",
				"imageBuffer",
				"image2DMS",
				"image2DMSArray",

				// composite types
				"replace_with_actual_udt_type_name",
			};

			return strs[enums::to_underlying(x)];
		}

	}
}