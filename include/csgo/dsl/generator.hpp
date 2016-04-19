#pragma once

#include <csgo/dsl/ir_program.hpp>
#include <sstream>
#include <ostream>

namespace csgo {
	namespace dsl {

		struct generator {
			std::string generate(ir_program& p) {
				std::stringstream sstr;
				generate(p, sstr);
				return sstr.str();
			}

            virtual void generate(ir_program& p, std::ostream& ostr) = 0;
		};

		void generate(ir_program& p, generator& g, std::ostream& ostr) {
			g.generate(p, ostr);
		}

		std::string generate(ir_program& p, generator& g) {
			return g.generate(p);
		}

	}
}
