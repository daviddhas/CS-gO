#pragma once

#include <csgo/gl/gl.hpp>

namespace csgo {
	template <typename P>
	struct image2d_io;

	namespace gld {

		template <typename T>
		struct internal_format_of;
		template <typename P>
		struct internal_format_of<image2d_io<P>> : internal_format_of<P> {};
		template <>
		struct internal_format_of<float> : std::integral_constant<GLenum, gl::R32F> {};
		template <>
		struct internal_format_of<int32_t> : std::integral_constant<GLenum, gl::R32I> {};
		template <>
		struct internal_format_of<glm::vec2> : std::integral_constant<GLenum, gl::RG32F> {};
		template <>
		struct internal_format_of<glm::vec3> : std::integral_constant<GLenum, gl::RGB32F> {};
		template <>
		struct internal_format_of<glm::vec4> : std::integral_constant<GLenum, gl::RGBA32F> {};

		template <typename T>
		struct format_of;
		template <typename P>
		struct format_of<image2d_io<P>> : format_of<P> {};
		template <>
		struct format_of<float> : std::integral_constant<GLenum, gl::RED> {};
		template <>
		struct format_of<int32_t> : std::integral_constant<GLenum, gl::RED_INTEGER> {};
		template <>
		struct format_of<glm::vec2> : std::integral_constant<GLenum, gl::RG> {};
		template <>
		struct format_of<glm::vec3> : std::integral_constant<GLenum, gl::RGB> {};
		template <>
		struct format_of<glm::vec4> : std::integral_constant<GLenum, gl::RGBA> {};

		template <typename T>
		struct gl_type_of;
		template <typename P>
		struct gl_type_of<image2d_io<P>> : format_of<P> {};
		template <>
		struct gl_type_of<float> : std::integral_constant<GLenum, gl::FLOAT> {};
		template <>
		struct gl_type_of<int32_t> : std::integral_constant<GLenum, gl::INT> {};
		template <>
		struct gl_type_of<glm::vec2> : gl_type_of<glm::vec2::value_type> {};
		template <>
		struct gl_type_of<glm::vec3> : gl_type_of<glm::vec3::value_type> {};
		template <>
		struct gl_type_of<glm::vec4> : gl_type_of<glm::vec4::value_type> {};

		// invert format_qualifier_for

		struct from_qualifier_to
		{
			static GLenum gl_internal_format(format_qualifier f)
			{
				switch (f)
				{
				case format_qualifier::r8:
					return gl::R8UI;
				case format_qualifier::r32f:
					return gl::R32F;
				case format_qualifier::rg32f:
					return gl::RG32F;
				case format_qualifier::rgba32f:
					return gl::RGBA32F;
				case format_qualifier::r32i:
					return gl::R32I;
				case format_qualifier::rg32i:
					return gl::RG32I;
				case format_qualifier::rgba32i:
					return gl::RGBA32I;
				case format_qualifier::r32ui:
					return gl::R32UI;
				case format_qualifier::rg32ui:
					return gl::RG32UI;
				case format_qualifier::rgba32ui:
					return gl::RGBA32UI;
				default:
					throw std::runtime_error("Invalid format qualifier");
				}
			}

			static GLenum gl_format(format_qualifier f)
			{
				switch (f)
				{
				case format_qualifier::r8:
					return gl::RED_INTEGER;
				case format_qualifier::r32f:
					return gl::RED;
				case format_qualifier::rg32f:
					return gl::RG;
				case format_qualifier::rgba32f:
					return gl::RGBA;

				case format_qualifier::r32i:
				case format_qualifier::r32ui:
					return gl::RED_INTEGER;

				case format_qualifier::rg32i:
				case format_qualifier::rg32ui:
					return gl::RG_INTEGER;

				case format_qualifier::rgba32i:
				case format_qualifier::rgba32ui:
					return gl::RGBA_INTEGER;

				default:
					throw std::runtime_error("Invalid format qualifier");
				}
			}

			static GLenum gl_type(format_qualifier f)
			{
				switch (f)
				{
				case format_qualifier::r8:
					return gl::BYTE;

				case format_qualifier::r32f:
				case format_qualifier::rg32f:
				case format_qualifier::rgba32f:
					return gl::FLOAT;

				case format_qualifier::r32i:
				case format_qualifier::rg32i:
				case format_qualifier::rgba32i:
					return gl::INT;

				case format_qualifier::r32ui:
				case format_qualifier::rg32ui:
				case format_qualifier::rgba32ui:
					return gl::UNSIGNED_INT;

				default:
					throw std::runtime_error("Invalid format qualifier");
				}
			}
		};
	}
}