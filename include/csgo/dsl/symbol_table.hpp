#pragma once

#include <csgo/dsl/variable.hpp>
#include <vector>
#include <string>

namespace csgo {
	namespace dsl {

		struct symbol_table {
			std::vector<std::string> names;
			std::vector<std::reference_wrapper<variable>> variables;

			symbol_table() {}
		};

	}
}
