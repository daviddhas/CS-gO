#pragma once

#include <csgo/dsl/generator.hpp>
#include <csgo/glsl/to_string.hpp>
#include <csgo/error.hpp>

namespace csgo {
	namespace glsl {

		struct compute_generator : dsl::generator {
			// TODO: actually use these to control how output looks (waaay later)
			bool pretty_lines = false;
			int indentation_level = 0;

			int binding_index = 0;

			// TODO: implement the internals of writer for actual codegen
			struct writer : dsl::statement_visitor {
				const dsl::ir_program& irp;
				std::ostream& ostr;
				int& indentation_level;

				writer(const dsl::ir_program& p, std::ostream& ostr, int& indentation_level) : irp(p), ostr(ostr), indentation_level(indentation_level) {}

				virtual void visit(const dsl::statement& s) override {
					typedef std::ostream::pos_type pos_type;
					if (s.expressions.empty())
						return;
					for (int i = 0; i < indentation_level; ++i)
						ostr << "\t";
					pos_type start = ostr.tellp();
					for (auto& e : s.expressions) {
						if (e == nullptr)
							continue;
						e->accept(*this);
					}
					if (start != ostr.tellp()) {
						ostr << ";";
					}
					ostr << "\n";
				}

				virtual void visit(const dsl::expression_reference& e) override {

				}

				virtual void visit(const dsl::access& e) override {
					ostr << e.access_name;
				}

				virtual void visit(const dsl::dot_access& e) override {
					auto r = irp.ast.symbols.find(e.access_into);
					r.second.accept(*this);
					ostr << ".";
					visit(static_cast<const dsl::access&>(e));
				}

				virtual void visit(const dsl::addition& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " + ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(const dsl::subtraction& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " - ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(const dsl::division& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " / ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(const dsl::multiplication& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " * ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(const dsl::variable& v) override {
					auto p = irp.ast.symbols.find(v.variable_id);
					ostr << p.first;
				}

				virtual void visit(const dsl::layout_variable& v) override {
					visit(static_cast<const dsl::variable&>(v));
				}

				virtual void visit(const dsl::image_variable& v) override {
					ostr << "imageLoad( ";
					visit(static_cast<const dsl::layout_variable&>(v));
					ostr << ", ivec2( ";
					visit(dsl::gl_GlobalInvocationID.xy);
					ostr << " ) )";
				}

				virtual void visit(const dsl::constant& v) override {
					v.write(ostr);
				}

				void visit_image_store(const dsl::image_variable& iv, const dsl::assignment& a) {
					ostr << "imageStore( ";
					visit(static_cast<const dsl::layout_variable&>(iv));
					ostr << ", ivec2( ";
					visit(dsl::gl_GlobalInvocationID.xy);
					ostr << " ), ";
					a.r->accept(*this);
					ostr << " )";
				}

				void visit_image_store(const dsl::image_variable& iv, const dsl::indexing& idx, const dsl::assignment& a) {
					ostr << "imageStore( ";
					visit(static_cast<const dsl::layout_variable&>(iv));
					ostr << ", ivec2( ";
					idx.r->accept(*this);
					ostr << " ), ";
					a.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(const dsl::assignment& a) override {
					dsl::expression* pv = a.l.get();
					const dsl::image_variable* piv = dynamic_cast<const dsl::image_variable*>(pv);
					const dsl::indexing* pidx = dynamic_cast<const dsl::indexing*>(pv);
					if (piv != nullptr) {
						// have to format as an image store
						visit_image_store(*piv, a);
						return;
					}
					else if (pidx != nullptr) {
						dsl::image_variable* pidxiv = dynamic_cast<dsl::image_variable*>(pidx->l.get());
						if (pidxiv != nullptr) {
							visit_image_store(*pidxiv, *pidx, a);
							return;
						}
					}
					a.l->accept(*this);
					ostr << " = ";
					a.r->accept(*this);
				}

				virtual void visit(const dsl::indexing& v) override {
					v.l->accept(*this);
					ostr << "[";
					v.r->accept(*this);
					ostr << "]";
				}

				virtual void visit(const dsl::declaration& v) override {
					bool isuniform = irp.ast.is_input_output(v.vardecl->variable_id);
					if (isuniform) {
						return;
					}
					if (dynamic_cast<const dsl::layout_variable*>(v.vardecl.get()) == nullptr) {
						// not an image / layout type
						ostr << glsl::to_string(v.vardecl->variable_type);
						ostr << " ";
					}
					v.vardecl->accept(*this);
				}

				virtual void visit(const dsl::declaration_assignment& a) override {
					const dsl::variable* vl = dynamic_cast<const dsl::variable*>(a.l.get());
					if (vl == nullptr)
						throw error("declaration assignment cannot declare something that is not a variable");
					if (dynamic_cast<const dsl::layout_variable*>(vl) == nullptr) {
						// not an image / layout type
						ostr << glsl::to_string(vl->variable_type);
						ostr << " ";
					}
					visit(static_cast<const dsl::assignment&>(a));
				}

				virtual void visit(const dsl::intrinsic& f) override {
					ostr << f.name << "( ";
					f.param->accept(*this);
					/*for (std::size_t i = 0; i < f.params.size(); ++i) {
						f.params[i]->accept(*this);
						if (i != f.params.size() - 1) {
							ostr << ", ";
						}
					}*/
					ostr << " )";
				}
			};

			void preamble(const dsl::ir_program& p, std::ostream& ostr) {
				ostr << "#version 450 core";
			}

			void uniform_variable(bool isoutput, const std::string& name, const dsl::variable& v, const dsl::ir_program& p, std::ostream& ostr) {
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

				}(); // immediately call the lambda

				// And then close
				ostr << ";";
				ostr << "\n";
			}

			void uniform_variables(bool isoutput, const std::vector<dsl::id>& ids, const dsl::ir_program& p, std::ostream& ostr) {
				for (auto id : ids) {
					auto namedvar = p.ast.symbols.find(id);
					const std::string& name = namedvar.first;
					const dsl::variable& v = namedvar.second;
					uniform_variable(isoutput, name, v, p, ostr);
				}
			}

			void input(const dsl::ir_program& p, std::ostream& ostr) {
				std::vector<dsl::id> ids;
				ids.reserve(p.main.input_variables.size());
				for (auto& v : p.main.input_variables)
					ids.push_back(v->variable_id);
				uniform_variables(false, ids, p, ostr);
			}

			void output(const dsl::ir_program& p, std::ostream& ostr) {
				std::vector<dsl::id> ids;
				ids.reserve(p.main.output_variables.size());
				for (auto& v : p.main.output_variables)
					ids.push_back(v->variable_id);
				uniform_variables(true, ids, p, ostr);
			}

			void open(const dsl::ir_program& p, std::ostream& ostr) {
				const workgroup& wg = p.main.wg;
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
				ostr << "void main() {";
				++indentation_level;
			}

			void close(const dsl::ir_program& p, std::ostream& ostr) {
				ostr << "}";
				--indentation_level;
			}

			virtual void generate(const dsl::ir_program& p, std::ostream& ostr) override {
				// setup variables
				preamble(p, ostr);
				ostr << "\n\n";
				input(p, ostr);
				ostr << "\n";
				output(p, ostr);
				ostr << "\n";

				// open main
				open(p, ostr);
				ostr << "\n";

				// Recursive write of the actual ir_program now
				writer mainwriter(p, ostr, indentation_level);
				for (const dsl::statement& s : p.main.statements) {
					s.accept(mainwriter);
				}

				// close main
				close(p, ostr);
			}

			virtual shader_stage generates_for() const override {
				return shader_stage::compute;
			}
		};
	}
}