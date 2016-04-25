#pragma once

#include <csgo/dsl/image_variable.hpp>
#include <csgo/dsl/primitives.hpp>
#include <csgo/optional.hpp>
#include <map>

namespace csgo {
	namespace dsl {

		const uvec3 gl_NumWorkGroups;
		const uvec3 gl_WorkGroupID;
		const uvec3 gl_LocalInvocationID;
		const uvec3 gl_GlobalInvocationID;
		const uint gl_LocalInvocationIndex;

		static optional<const std::string&> is_builtin_variable(const id& vid) {
			static const std::map<id, std::string> names{
				{ gl_NumWorkGroups.variable_id, "gl_NumWorkGroups" },
				{ gl_WorkGroupID.variable_id, "gl_WorkGroupID" },
				{ gl_LocalInvocationID.variable_id, "gl_LocalInvocationID" },
				{ gl_GlobalInvocationID.variable_id, "gl_GlobalInvocationID" },
				{ gl_LocalInvocationIndex.variable_id, "gl_LocalInvocationIndex" }
			};
			auto v = names.find(vid);
			if (v == names.cend())
				return nullopt;
			return v->second;
		}

	}
}
