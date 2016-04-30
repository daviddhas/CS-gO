#pragma once

#include <csgo/enums.hpp>
#include <glm/glm.hpp>
#include <type_traits>
#include <cstddef>

namespace csgo {

	enum class format_qualifier {
		// floating point image types
		rgba32f,
		rgba16f,
		rg32f,
		rg16f,
		r11f_g11f_b10f,
		r32f,
		r16f,
		rgba16,
		rgb10_a2,
		rgba8,
		rg16,
		rg8,
		r16,
		r8,
		rgba16_snorm,
		rgba8_snorm,
		rg16_snorm,
		rg8_snorm,
		r16_snorm,
		r8_snorm,

		// integer image types
		rgba32i,
		rgba16i,
		rgba8i,
		rg32i,
		rg16i,
		rg8i,
		r32i,
		r16i,
		r8i,

		// unsigned integer image types
		rgba32ui,
		rgba16ui,
		rgb10_a2ui,
		rgba8ui,
		rg32ui,
		rg16ui,
		rg8ui,
		r32ui,
		r16ui,
		r8ui,
	};

	inline const std::string& to_string(format_qualifier f) {
		static const std::string names[] = {
			// floating point image types
			"rgba32f",
			"rgba16f",
			"rg32f",
			"rg16f",
			"r11f_g11f_b10f",
			"r32f",
			"r16f",
			"rgba16",
			"rgb10_a2",
			"rgba8",
			"rg16",
			"rg8",
			"r16",
			"r8",
			"rgba16_snorm",
			"rgba8_snorm",
			"rg16_snorm",
			"rg8_snorm",
			"r16_snorm",
			"r8_snorm",

			// integer image types
			"rgba32i",
			"rgba16i",
			"rgba8i",
			"rg32i",
			"rg16i",
			"rg8i",
			"r32i",
			"r16i",
			"r8i",

			// unsigned integer image types
			"rgba32ui",
			"rgba16ui",
			"rgb10_a2ui",
			"rgba8ui",
			"rg32ui",
			"rg16ui",
			"rg8ui",
			"r32ui",
			"r16ui",
			"r8ui",
		};
		return names[enums::to_underlying(f)];
	}

	template <typename T>
	struct format_qualifier_for;

	template <>
	struct format_qualifier_for<uint8_t> : std::integral_constant<format_qualifier, format_qualifier::r8> {};

	template <>
	struct format_qualifier_for<float> : std::integral_constant<format_qualifier, format_qualifier::r32f> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec1<float, p>> : std::integral_constant<format_qualifier, format_qualifier::r32f> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec2<float, p>> : std::integral_constant<format_qualifier, format_qualifier::rg32f> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec3<float, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32f> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec4<float, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32f> {};

	template <>
	struct format_qualifier_for<int> : std::integral_constant<format_qualifier, format_qualifier::r32i> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec1<int, p>> : std::integral_constant<format_qualifier, format_qualifier::r32i> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec2<int, p>> : std::integral_constant<format_qualifier, format_qualifier::rg32i> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec3<int, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32i> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec4<int, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32i> {};

	template <>
	struct format_qualifier_for<uint32_t> : std::integral_constant<format_qualifier, format_qualifier::r32ui> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec1<uint32_t, p>> : std::integral_constant<format_qualifier, format_qualifier::r32ui> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec2<uint32_t, p>> : std::integral_constant<format_qualifier, format_qualifier::rg32ui> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec3<uint32_t, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32ui> {};

	template <glm::precision p>
	struct format_qualifier_for<glm::tvec4<uint32_t, p>> : std::integral_constant<format_qualifier, format_qualifier::rgba32ui> {};
}
