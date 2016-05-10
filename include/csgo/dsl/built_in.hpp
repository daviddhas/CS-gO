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

		static optional<std::pair<const std::string&, const variable&>> is_builtin_variable(const id& vid) {
			typedef std::pair<std::string, std::reference_wrapper<const variable>> var_pair;
			static const std::map<id, var_pair> names {
				{ gl_NumWorkGroups.variable_id, var_pair{ "gl_NumWorkGroups", gl_NumWorkGroups } },
				{ gl_WorkGroupID.variable_id, var_pair{ "gl_WorkGroupID", gl_WorkGroupID } },
				{ gl_LocalInvocationID.variable_id, var_pair{ "gl_LocalInvocationID", gl_LocalInvocationID } },
				{ gl_GlobalInvocationID.variable_id, var_pair{ "gl_GlobalInvocationID", gl_GlobalInvocationID } },
				{ gl_LocalInvocationIndex.variable_id, var_pair{ "gl_LocalInvocationIndex", gl_LocalInvocationIndex } }
			};
			auto v = names.find(vid);
			if (v == names.cend())
				return nullopt;
			return optional<std::pair<const std::string&, const variable&>>(in_place, v->second.first, v->second.second);
		}

	}
}
