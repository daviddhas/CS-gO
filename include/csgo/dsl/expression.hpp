#pragma once

#include <csgo/type_traits.hpp>

namespace csgo {
	namespace dsl {

		struct expression;
		
		struct variable;
		struct layout_variable;
		struct constant;
		
		struct binary_expression;
		struct unary_expression;
		struct addition;
		struct division;
		struct subtraction;
		struct multiplication;
		struct involution;
		
		struct statement;
		
		struct expression_visitor {
			virtual void visit(statement& s) = 0;
			virtual void visit(expression& e) = 0;
			
			virtual void visit(binary_expression& e) = 0;
			virtual void visit(addition& e) = 0;
			virtual void visit(subtraction& e) = 0;
			virtual void visit(division& e) = 0;
			virtual void visit(multiplication& e) = 0;

			virtual void visit(variable& v) = 0;
			virtual void visit(layout_variable& v) = 0;
			virtual void visit(constant& v) = 0;
		};

		struct expression {
			virtual void accept(expression_visitor& v) {
				v.visit(*this);
			}
			virtual ~expression() {}
		};

	}
}
