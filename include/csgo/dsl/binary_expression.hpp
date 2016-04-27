#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/dsl/expression_consume.hpp>

namespace csgo {
	namespace dsl {
		struct binary_expression : expression {
			std::unique_ptr<expression> l;
			std::unique_ptr<expression> r;

			binary_expression(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : l(std::move(l)), r(std::move(r)) {}
		};

		struct addition : binary_expression {
			addition(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct subtraction : binary_expression {
			subtraction(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct multiplication : binary_expression {
			multiplication(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct division : binary_expression {
			division(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct assignment : binary_expression {
			assignment(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct declaration : expression {
			std::unique_ptr<variable> vardecl;

			declaration(std::unique_ptr<variable> vardecl) : vardecl(std::move(vardecl)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};
		
		struct declaration_assignment : assignment {
			declaration_assignment(std::unique_ptr<variable> decl, std::unique_ptr<expression> init) : assignment(std::move(decl), std::move(init)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct indexing : binary_expression {
			indexing(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			template <typename T>
			indexing& operator= (T&& right) && {
				consume(assignment(
					dsl::make_unique_expression(std::move(*this)),
					dsl::make_unique_expression(std::forward<T>(right))
				));
				return *this;
			}

			virtual void accept(statement_visitor& v) override {
				return v.visit(*this);
			}
		};

	}
}
