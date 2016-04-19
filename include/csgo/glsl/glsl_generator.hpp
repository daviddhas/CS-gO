#pragma once

#include <csgo/dsl/generator.hpp>
#include <csgo/glsl/to_string.hpp>

namespace csgo {
	namespace glsl {

		struct glsl_generator : dsl::generator {
			// TODO: actually use these to control how output looks (waaay later)
			bool pretty_lines = false;
			int indentation_level = 0;

			int binding_index = 0;

			// TODO: implement the internals of writer for actual codegen
			struct writer : dsl::expression_visitor {
				std::ostream& ostr;
				
				writer(std::ostream& ostr) : ostr(ostr) {}

				virtual void visit(dsl::statement&) override {
					
				}

				virtual void visit(dsl::expression&) override {
					
				}

				virtual void visit(dsl::binary_expression& e) override {
					
				}

				virtual void visit(dsl::addition& e) override {
					
				}

				virtual void visit(dsl::subtraction& e) override {
					
				}

				virtual void visit(dsl::division& e) override {
					
				}

				virtual void visit(dsl::multiplication& e) override {
					
				}

				virtual void visit(dsl::variable& v) override {
					
				}

				virtual void visit(dsl::layout_variable& v) override {
				
				}

				virtual void visit(dsl::constant& v) override {

				}
			};

			void preamble(dsl::ir_program& p, std::ostream& ostr) {
				ostr << "#version 430" << "\n\n";
			}

			void uniform_variable(bool isoutput, const std::string& name, const dsl::variable& v, dsl::ir_program& p, std::ostream& ostr) {
				// Do layout bindings
				ostr << "layout(";
				ostr << " binding = " << binding_index++;
				const dsl::layout_variable* lv = dynamic_cast<const dsl::layout_variable*>(&v);
				if (lv != nullptr) {
					const qualifiers& layout = lv->layout;
					ostr << ", " << to_string(layout.format);
				}
				ostr << " )";
				// TODO: respect layout_variable's memory_qualifiers here
				if (isoutput) {
					ostr << " writeonly";
				}
				else {
					ostr << " readonly";
				}
				ostr << " uniform";
				ostr << " " << glsl::to_string(v.variable_type);
				
				// Name it
				ostr << " " << name;
				
				// Check for initialization
				// using lambda to allow early "return" statements
				// while still exiting at the end
				[&]() {
					if (v.initialization == nullptr)
						return;
					dsl::constant* c = dynamic_cast<dsl::constant*>(v.initialization.get());
					if (c == nullptr)
						return;
					ostr << " = ";
					c->write(ostr);
				}(); // immediately call the lambda
				
				// And then close
				ostr << ";";
				ostr << "\n";
			}

			void input(dsl::ir_program& p, std::ostream& ostr) {
				for (std::size_t index = 0; index < p.inputs.size(); ++index ) {
					dsl::uniform_reference& ud = p.inputs[index];
					auto namedvar = p.ast.symbols.find(ud.id);
					const std::string& name = namedvar.first;
					const dsl::variable& v = namedvar.second;
					uniform_variable(false, name, v, p, ostr);
				}
				ostr << "\n";
			}

			void output(dsl::ir_program& p, std::ostream& ostr) {
				for (std::size_t index = 0; index < p.outputs.size(); ++index) {
					dsl::uniform_reference& ud = p.outputs[index];
					auto namedvar = p.ast.symbols.find(ud.id);
					const std::string& name = namedvar.first;
					const dsl::variable& v = namedvar.second;
					uniform_variable(true, name, v, p, ostr);
				}
				ostr << "\n";
			}

			void open(dsl::ir_program& p, std::ostream& ostr) {
				workgroup& wg = p.main.wg;
				// Can only drop end if it is 1, plus things before it are also 1
				bool dropz = wg.z == 1;
				bool dropy = dropz && wg.y == 1;
				bool dropx = dropy && wg.x == 1 && false; // TODO: can you ever drop the local_size_x parameter?
				// TODO: if all equal 1, there's no need for the layout var, so skip entirely if all are true?
				ostr << "layout(";
				if (!dropx) {
					ostr << " local_size_x = " << wg.x;
					if (!dropy) {
						ostr << ", local_size_y = " << wg.y;
						if (!dropz) {
							ostr << ", local_size_z = " << wg.x;
						}
					}
				}
				// TODO: currently 'in' is hardcoded
				// as the variable. Is that OpenGL Spec for it to be named this,
				// or just convention amongst all the examples?
				// if convention, should allow for renaming of some sort?
				ostr << " ) in;\n\n";

				// Now, start main
				ostr << "void main() {\n";
				++indentation_level;
			}

			void close(dsl::ir_program& p, std::ostream& ostr) {
				ostr << "}";
				--indentation_level;
			}

			virtual void generate(dsl::ir_program& p, std::ostream& ostr) override {
				// setup variables
				preamble(p, ostr);
				input(p, ostr);
				output(p, ostr);
				
				// open main
				open(p, ostr);
				
				// Recursive write of the actual ir_program now
				writer mainwriter(ostr);
				p.main.accept(mainwriter);

				// close main
				close(p, ostr);
			}
		};
	}
}