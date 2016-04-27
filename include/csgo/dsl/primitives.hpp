#pragma once

#include <csgo/dsl/var.hpp>
#include <csgo/dsl/access.hpp>

namespace csgo {
	namespace dsl {
		struct vec2 : var<glm::vec2> {
			using var<glm::vec2>::var;
			dot_access x{ *this, "x"};
			dot_access y{ *this, "y"};
			dot_access xy{ *this, "xy"};
		};
		struct vec3 : var<glm::vec3> {
			using var<glm::vec3>::var;
		};
		struct vec4 : var<glm::vec4> {
			using var<glm::vec4>::var;
			dot_access x{ *this, "x" };
			dot_access y{ *this, "y" };
			dot_access z{ *this, "z" };
			dot_access w{ *this, "w" };

			dot_access xy{ *this, "xy" };
			dot_access xz{ *this, "xz" };
			dot_access xw{ *this, "xw" };
			dot_access yx{ *this, "yx" };
			dot_access yz{ *this, "yz" };
			dot_access yw{ *this, "yw" };
			dot_access zx{ *this, "zx" };
			dot_access wy{ *this, "wy" };
			dot_access wz{ *this, "wz" };

			dot_access xyz{ *this, "xyz" };
			dot_access xyw{ *this, "xyw" };
			dot_access xzw{ *this, "xzw" };
		};

		struct uvec2 : var<glm::uvec2> {
			using var<glm::uvec2>::var;
			dot_access x{ *this, "x" };
			dot_access y{ *this, "y" };
			dot_access z{ *this, "z" };
			dot_access xy{ *this, "xy" };
			dot_access yz{ *this, "yz" };
		};
		struct uvec3 : var<glm::uvec3> {
			using var<glm::uvec3>::var;
			dot_access x { *this, "x"};
			dot_access y { *this, "y"};
			dot_access z{ *this, "z"};
			dot_access xy{ *this, "xy"};
			dot_access yz { *this, "yz"};
		};
		struct uvec4 : var<glm::uvec4> {
			using var<glm::uvec4>::var;
		};

		struct ivec2 : var<glm::ivec2> {
			using var<glm::ivec2>::var;
		};
		struct ivec3 : var<glm::ivec3> {
			using var<glm::ivec3>::var;
		};
		struct ivec4 : var<glm::ivec4> {
			using var<glm::ivec4>::var;
		};

		struct uint : var<uint32_t> {
			using var<uint32_t>::var;
		};
	}
}
