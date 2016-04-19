#pragma once

#include <csgo/dsl/variable.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

namespace csgo {
	namespace dsl {

		struct symbol_table {
			std::unordered_map<variable_id, std::size_t> variable_id_indices;
			std::vector<std::string> names;
			std::vector<std::reference_wrapper<variable>> variables;

			symbol_table() {}

			std::pair<const std::string&, const variable&> find(const variable_id& id) const {
				auto varfind = variable_id_indices.find(id);
				if (varfind == variable_id_indices.cend()) {
					throw std::runtime_error("cannot find variable");
				}
				const variable& found = variables[varfind->second];
				const std::string& name = names[varfind->second];
				return { name, found };
			}

			const std::string& give_name( variable& v ) {
				// Check if we have a id collision
				auto varfind = variable_id_indices.find(v.id);
				if (varfind != variable_id_indices.cend()) {
                    variable found = variables[varfind->second];
					if (v.variable_type != found.variable_type) {
						throw std::runtime_error("two variables of differing types share the same id: BAD!");
					}
				}
				// Create a new name
				std::string name;
				// names usually aren't too long: 32 reservation should keep use safe from reallocation
				name.reserve(32);
				name += "_";
				name += std::to_string(v.id.id);
				
				variable_id_indices.insert(varfind, { v.id, variables.size() });
				names.push_back(std::move(name));
				variables.push_back(v);
				return names.back();
			}
		};

	}
}
