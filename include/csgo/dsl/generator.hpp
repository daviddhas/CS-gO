#pragma once

#include <csgo/dsl/ir_program.hpp>
#include <csgo/shader_stage.hpp>
#include <sstream>
#include <ostream>

namespace csgo {
	namespace dsl {

		struct generator {
			std::string generate(const ir_program& p) {
				std::stringstream sstr;
				generate(p, sstr);
				std::string code = sstr.str();
				std::cout << code << std::endl;
				return code;
			}

			virtual shader_stage generates_for() const = 0;
			
			virtual void generate(const ir_program& p, std::ostream& ostr) = 0;
		};

		inline void generate(const ir_program& p, generator& g, std::ostream& ostr) {
			g.generate(p, ostr);
		}

		inline std::string generate(const ir_program& p, generator& g) {
			return g.generate(p);
		}

	}
}
