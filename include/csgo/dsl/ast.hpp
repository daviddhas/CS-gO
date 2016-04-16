#pragma once

#include <csgo/dsl/program.hpp>
#include <csgo/dsl/symbol_table.hpp>
#include <vector>
#include <algorithm>

namespace csgo {
	namespace dsl {
		// This class gathers and generates relevant information based on
		// expressions and statements in a csgo module.
		// Meant to be consumed by the compiler / program
		struct abstract_syntax_tree {
		public:
			abstract_syntax_tree( program p ) : p(std::move(p)) {
				construct();
			}

		private:
			void construct() {
				expression* expr = p.root.get();
				if (expr == nullptr) {
					return;
				}

			}

			symbol_table table;
			program p;
		};
	}
}
