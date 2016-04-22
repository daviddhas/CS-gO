#pragma once

#include <csgo/dsl/image_variable.hpp>
#include <csgo/dsl/primitives.hpp>

namespace csgo {
	namespace dsl {

		const uvec3 gl_NumWorkGroups;
		const uvec3 gl_WorkGroupID;
		const uvec3 gl_LocalInvocationID;
		const uvec3 gl_GlobalInvocationID;
		const uint gl_LocalInvocationIndex;

	}
}
