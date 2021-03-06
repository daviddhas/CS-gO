#pragma once

#include <csgo/dsl/built_in.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>

namespace csgo {
	namespace dsl {

		struct symbol_table {
			std::unordered_map<id, std::size_t> variable_id_indices;
			std::vector<std::string> names;
			std::vector<std::reference_wrapper<const variable>> variables;

			symbol_table() {}

			std::pair<const std::string&, const variable&> find(const id& vid) const {
				auto bltin = is_builtin_variable(vid);
				if (bltin) {
					return *bltin;
				}
				auto varfind = variable_id_indices.find(vid);
				if (varfind == variable_id_indices.cend()) {
					throw std::runtime_error("cannot find variable");
				}
				const variable& found = variables[varfind->second];
				const std::string& name = names[varfind->second];
				return { name, found };
			}

			const std::string& give_name( const variable& v ) {
				// Check if we have a id collision
				auto varfind = variable_id_indices.find(v.variable_id);
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
				name += "_var";
				name += std::to_string(v.variable_id.value);
				
				variable_id_indices.insert(varfind, { v.variable_id, variables.size() });
				names.push_back(std::move(name));
				variables.push_back(v);
				return names.back();
			}
		};

	}
}
