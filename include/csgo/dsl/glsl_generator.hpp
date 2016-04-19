#pragma once

#include <csgo/dsl/generator.hpp>

namespace csgo {
	namespace dsl {
		struct glsl_generator : generator {
			bool pretty_lines = false;
			int indentation_level = 0;

			struct uniform_writer : expression_visitor {
				const std::string& name;
				std::ostream& ostr;
				
				uniform_writer(const std::string& name, std::ostream& ostr) : name(name), ostr(ostr) {}

				virtual void visit(statement&) {
					throw std::runtime_error("uniform_writer somehow visited a statement");
				}

				virtual void visit(expression&) {
					throw std::runtime_error("uniform_writer somehow visited an expression");
				}

				virtual void visit(binary_expression& e) {
					visit(static_cast<expression&>(e));
				}

				virtual void visit(addition& e) {
					visit(static_cast<expression&>(e));
				}

				virtual void visit(subtraction& e) {
					visit(static_cast<expression&>(e));
				}

				virtual void visit(division& e) {
					visit(static_cast<expression&>(e));
				}

				virtual void visit(multiplication& e) {
					visit(static_cast<expression&>(e));
				}

				virtual void visit(variable& v) {
					ostr << to_string(v.variable_type);
					// using lambda to allow early "return" statements
					// while still exiting at the end
					[&]() {
						if (v.initialization == nullptr)
							return;
						constant* c = dynamic_cast<constant*>(v.initialization.get());
						if (c == nullptr)
							return;
						c->write(ostr);
					}();
					ostr << ";";
				}

				virtual void visit(container_variable& v) {
				
				}

				virtual void visit(constant& v) {

				}
			};

			void preamble(program& p, std::ostream& ostr) {
				ostr << "#version 430 core" << "\n\n";
			}

			void input(program& p, std::ostream& ostr) {
				for (uniform_descriptor& ud : p.inputs) {
					auto namedvar = p.ast.symbols.find(ud.id);
					const std::string& name = namedvar.first;
					const variable& v = namedvar.second;

				}
			}

			void output(program& p, std::ostream& ostr) {
				for (uniform_descriptor& ud : p.outputs) {

				}
			}

			virtual void generate(program& p, std::ostream& ostr) override {
				preamble(p, ostr);
				input(p, ostr);
				output(p, ostr);
			}
		};
	}
}