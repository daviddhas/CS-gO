#pragma once

#include <csgo/type_traits.hpp>
#include <csgo/dsl/type.hpp>
#include <csgo/dsl/id.hpp>

namespace csgo {
	namespace dsl {
		struct statement;

		struct expression_reference;

		struct variable;
		struct layout_variable;
		struct image_variable;
		struct constant;

		struct addition;
		struct division;
		struct subtraction;
		struct multiplication;

		struct assignment;
		struct indexing;

		struct declaration;
		struct declaration_assignment;

		struct statement_visitor {
			virtual void visit(statement& s) = 0;

			virtual void visit(expression_reference& e) = 0;

			virtual void visit(declaration& d) = 0;
			virtual void visit(declaration_assignment& d) = 0;

			virtual void visit(addition& e) = 0;
			virtual void visit(subtraction& e) = 0;
			virtual void visit(division& e) = 0;
			virtual void visit(multiplication& e) = 0;
			virtual void visit(assignment& e) = 0;
			virtual void visit(indexing& u) = 0;

			virtual void visit(variable& v) = 0;
			virtual void visit(layout_variable& v) = 0;
			virtual void visit(image_variable& v) = 0;
			virtual void visit(constant& v) = 0;
		};

		struct expression {
			id expression_id = generate_id<expression>();
			expression() {}
			expression(id i) : expression_id(std::move(i)) {}
			virtual void accept(statement_visitor& v) = 0;
			virtual ~expression() {}
		};

		struct expression_reference : expression {
			expression_reference(id i) : expression(i) {}

			virtual void accept(statement_visitor& v) {
				v.visit(*this);
			}
		};

		template <typename T>
		struct is_terminating_expression : std::false_type {};

		template <>
		struct is_terminating_expression<assignment> : std::true_type {};

		template <>
		struct is_terminating_expression<declaration_assignment> : std::true_type {};

		template <>
		struct is_terminating_expression<declaration> : std::true_type {};

	}
}
