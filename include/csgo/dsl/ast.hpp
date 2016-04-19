#pragma once

#include <csgo/dsl/program.hpp>
#include <csgo/dsl/symbol_table.hpp>
#include <iostream>

namespace csgo {
	namespace dsl {
		// This class gathers and generates relevant information based on
		// expressions and statements in a csgo module.
		// Meant to be consumed by the compiler / program
		struct abstract_syntax_tree {
		public:
			symbol_table symbols;

			abstract_syntax_tree(entry_point& p) {
				expression_namer v(symbols);
				construct(p, v);
			}

		private:
			void construct(entry_point& ep, expression_visitor& v) {
				ep.root.accept(v);
			}

			struct expression_namer : expression_visitor {
				symbol_table& symbols;
				std::ostream& ostr;

				expression_namer(symbol_table& symbols) : symbols(symbols), ostr(std::cout) {}

				virtual void visit(statement& s) {
					for (auto& pexpr : s.expressions) {
						if (pexpr == nullptr)
							continue;
						expression& expr = *pexpr;
						expr.accept(*this);
					}
				}

				virtual void visit(expression&) override {
					ostr << "[ underived expression ]";
				}

				virtual void visit(variable& v) override {
					symbols.give_name(v);
					ostr << "[ " << v.id.id << " - " << to_string(v.variable_type) << " ]";
				}

				virtual void visit(constant& v) override {
					ostr << "[ " << v.id.id << " - constant " << to_string(v.variable_type) << " ";
					switch (v.variable_type) {
					case type::boolean:
						ostr << std::boolalpha << dynamic_cast<typed_constant<bool>&>(v).value;
						break;
					case type::integer:
						ostr << std::boolalpha << dynamic_cast<typed_constant<int32_t>&>(v).value;
						break;
					case type::single_precision:
						ostr << std::boolalpha << dynamic_cast<typed_constant<float>&>(v).value;
						break;
					case type::double_precision:
						ostr << std::boolalpha << dynamic_cast<typed_constant<float>&>(v).value;
						break;
					default:
						throw std::runtime_error("Unhandled variable type for constant");
						break;
					}
					ostr << "]";
				}

				virtual void visit(container_variable& v) override {
					symbols.give_name(v);
					ostr << "[ " << v.id.id << " - " << to_string(v.variable_type) << "<" << to_string(v.contained_type) << "> ]";
				}

				virtual void visit(binary_expression& e) override {
					ostr << "( ";
					e.l->accept(*this);
					ostr << "<underived binary expression>";
					e.r->accept(*this);
					ostr << " )";
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
			};
		};
	}
}
