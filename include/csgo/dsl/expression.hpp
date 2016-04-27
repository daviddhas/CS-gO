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


		struct access;
		struct dot_access;

		struct statement_visitor {
			virtual void visit(const statement& s) = 0;

			virtual void visit(const expression_reference& e) = 0;

			virtual void visit(const declaration& d) = 0;
			virtual void visit(const declaration_assignment& d) = 0;

			virtual void visit(const addition& e) = 0;
			virtual void visit(const subtraction& e) = 0;
			virtual void visit(const division& e) = 0;
			virtual void visit(const multiplication& e) = 0;
			virtual void visit(const assignment& e) = 0;
			virtual void visit(const indexing& u) = 0;

			virtual void visit(const variable& v) = 0;
			virtual void visit(const layout_variable& v) = 0;
			virtual void visit(const image_variable& v) = 0;
			virtual void visit(const constant& v) = 0;

			virtual void visit(const dot_access& v) = 0;
			virtual void visit(const access& v) = 0;
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

		template <typename T>
		struct is_expression : std::is_base_of<expression, meta::unqualified_t<T>> {};

		template <typename T>
		struct is_primitive : std::is_arithmetic<meta::unqualified_t<T>> {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec1<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x4<T, p>> : std::true_type {};

	}
}
