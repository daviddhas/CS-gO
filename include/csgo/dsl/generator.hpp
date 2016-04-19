#pragma once

#include <csgo/dsl/program.hpp>
#include <sstream>
#include <ostream>

namespace csgo {
	namespace dsl {

		struct generator {
			std::string generate(program& p) {
				std::stringstream sstr;
				generate(p, sstr);
				return sstr.str();
			}

			virtual void generate(program& p, std::ostream& ostr) = 0;
		};

		void generate(program& p, generator& g, std::ostream& ostr) {
			g.generate(p, ostr);
		}

		std::string generate(program& p, generator& g) {
			return g.generate(p);
		}

	}
}
