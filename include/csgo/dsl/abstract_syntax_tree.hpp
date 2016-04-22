#pragma once

#include <csgo/dsl/ir_entry_point.hpp>
#include <csgo/dsl/binary_expression.hpp>
#include <csgo/dsl/unary_expression.hpp>
#include <csgo/dsl/built_in.hpp>
#include <csgo/dsl/symbol_table.hpp>

#include <iostream>

namespace csgo {
	namespace dsl {
		struct abstract_syntax_tree {
			symbol_table symbols;
			std::unordered_map<id, std::size_t> expression_indices;
			std::vector<std::reference_wrapper<expression>> flow;

			abstract_syntax_tree(ir_entry_point& main) {
				tree_builder builder(*this);
				for (auto& s : main.statements) {
					s.accept(builder);
				}
			}

		private:
			struct tree_builder : statement_visitor {
				abstract_syntax_tree& ast;
				std::ostream& ostr;

				tree_builder(abstract_syntax_tree& ast) : ast(ast), ostr(std::cout) {}

				virtual void visit(statement& s) override {
					for (auto& e : s.expressions) {
						if (e == nullptr)
							continue;
						e->accept(*this);
						ostr << "\n";
					}
				}

				virtual void visit(expression_reference& e) override {

				}

				virtual void visit(variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << " ]";
				}

				virtual void visit(layout_variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << to_string(v.variable_type) << "<" << to_string(v.layout.format) << ">" << " ]";
				}

				virtual void visit(image_variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << to_string(v.variable_type) << "<" << to_string(v.layout.format) << ">" << " ]";
				}

				virtual void visit(constant& v) override {
					ostr << "[ " << v.variable_id.value << " - constant " << to_string(v.variable_type) << " ";
					switch (v.variable_type) {
					case type::boolean:
						ostr << std::boolalpha << dynamic_cast<typed_constant<bool>&>(v).value;
						break;
					case type::integer:
						ostr << dynamic_cast<typed_constant<int32_t>&>(v).value;
						break;
					case type::single_precision:
						ostr << dynamic_cast<typed_constant<float>&>(v).value;
						break;
					case type::double_precision:
						ostr << dynamic_cast<typed_constant<double>&>(v).value;
						break;
					default:
						throw std::runtime_error("Unhandled variable type for constant");
						break;
					}
					ostr << "]";
				}

				virtual void visit(addition& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " + ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(subtraction& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " - ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(division& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " / ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(multiplication& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << " * ";
					e.r->accept(*this);
					ostr << " )";
				}

				virtual void visit(indexing& e) override {

				}

				virtual void visit(assignment& e) override {

				}

				virtual void visit(declaration& d) override {
					if (d.vardecl == nullptr)
						return;
					d.vardecl->accept(*this);
				}

				virtual void visit(declaration_assignment& d) override {
					if (d.vardecl == nullptr)
						return;
					d.vardecl->accept(*this);
					ostr << " = ";
					d.initialization->accept(*this);
				}
			};
		};
	}
}