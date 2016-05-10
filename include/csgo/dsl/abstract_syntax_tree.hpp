#pragma once

#include <csgo/dsl/ir_entry_point.hpp>
#include <csgo/dsl/binary_expression.hpp>
#include <csgo/dsl/unary_expression.hpp>
#include <csgo/dsl/access.hpp>
#include <csgo/dsl/built_in.hpp>
#include <csgo/dsl/symbol_table.hpp>
#include <unordered_set>
#include <algorithm>

#include <iostream>

namespace csgo {
	namespace dsl {
		struct abstract_syntax_tree {
			std::vector<id> inputids;
			std::vector<id> outputids;
			symbol_table symbols;
			std::unordered_map<id, std::size_t> expression_indices;
			std::vector<std::reference_wrapper<expression>> flow;

			abstract_syntax_tree(ir_entry_point& main) {
				for (auto& in : main.input_variables) {
					inputids.push_back(in->variable_id);
					symbols.give_name(*in);
				}
				for (auto& out : main.output_variables) {
					outputids.push_back(out->variable_id);
					symbols.give_name(*out);
				}

				tree_builder builder(*this);
				for (auto& s : main.statements) {
					s.accept(builder);
				}
			}

			bool is_input_output( const id& i ) const {
				return std::find(inputids.cbegin(), inputids.cend(), i) != inputids.cend() || std::find(outputids.cbegin(), outputids.cend(), i) != outputids.cend();
			}

			const std::string& name_for(const id& varid) {
				const auto& s = symbols.find(varid);
				return s.first;
			}

			const std::string& input_name(std::size_t idx) {
				return name_for(inputids[idx]);
			}

			const std::string& output_name(std::size_t idx) {
				return name_for(outputids[idx]);
			}

		private:
			struct tree_builder : statement_visitor {
				abstract_syntax_tree& ast;
				std::ostream& ostr;

				tree_builder(abstract_syntax_tree& ast) : ast(ast), ostr(std::cout) {}

				virtual void visit(const statement& s) override {
					for (auto& e : s.expressions) {
						if (e == nullptr)
							continue;
						e->accept(*this);
						ostr << "\n";
					}
				}

				virtual void visit(const expression_reference& e) override {

				}

				virtual void visit(const dot_access& e) override {
					//ostr << "[ ";
					//e.accept(*this);
					//ostr << "." << e.access_name << " ]";
				}

				virtual void visit(const access& e) override {
					//ostr << "[ ." << e.access_name << " ]";
				}

				virtual void visit(const variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					//ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << to_string(v.variable_type) << " ]";
				}

				virtual void visit(const layout_variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					//ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << to_string(v.variable_type) << "<" << to_string(v.layout.format) << ">" << " ]";
				}

				virtual void visit(const image_variable& v) override {
					const std::string& name = ast.symbols.give_name(v);
					//ostr << "[ " << v.variable_id.value << ", '" << name << "' - " << to_string(v.variable_type) << "<" << to_string(v.layout.format) << ">" << " ]";
				}

				virtual void visit(const constant& v) override {
					//ostr << "[ " << v.variable_id.value << " - constant " << to_string(v.variable_type) << " ";
					v.write(ostr);
					//ostr << "]";
				}

				virtual void visit(const addition& e) override {
					//ostr << "( ";
					e.l->accept(*this);
					//ostr << " + ";
					e.r->accept(*this);
					//ostr << " )";
				}

				virtual void visit(const subtraction& e) override {
					//ostr << "( ";
					e.l->accept(*this);
					//ostr << " - ";
					e.r->accept(*this);
					//ostr << " )";
				}

				virtual void visit(const division& e) override {
					//ostr << "( ";
					e.l->accept(*this);
					//ostr << " / ";
					e.r->accept(*this);
					//ostr << " )";
				}

				virtual void visit(const multiplication& e) override {
					//ostr << "( ";
					e.l->accept(*this);
					//ostr << " * ";
					e.r->accept(*this);
					//ostr << " )";
				}

				virtual void visit(const indexing& e) override {

				}

				virtual void visit(const assignment& e) override {

				}

				virtual void visit(const declaration& d) override {
					if (d.vardecl == nullptr)
						return;
					d.vardecl->accept(*this);
				}

				virtual void visit(const declaration_assignment& d) override {
					if (d.l == nullptr)
						return;
					d.l->accept(*this);
					//ostr << " = ";
					d.r->accept(*this);
				}

				virtual void visit(const intrinsic& i) override {

				}
			};
		};
	}
}