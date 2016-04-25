#pragma once

#include <csgo/dsl/var.hpp>

namespace csgo {
	namespace dsl {
		struct vec2 : var<glm::vec2> {
			using var<glm::vec2>::var;
		};
		struct vec3 : var<glm::vec3> {
			using var<glm::vec3>::var;
		};
		struct vec4 : var<glm::vec4> {
			using var<glm::vec4>::var;
		};

		struct uvec2 : var<glm::uvec2> {
			using var<glm::uvec2>::var;
		};
		struct uvec3 : var<glm::uvec3> {
			using var<glm::uvec3>::var;
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
