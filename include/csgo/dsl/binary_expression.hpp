#pragma once

#include <csgo/dsl/variable.hpp>

namespace csgo {
	namespace dsl {
		struct binary_expression : expression {
			std::unique_ptr<expression> l;
			std::unique_ptr<expression> r;

			binary_expression(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : l(std::move(l)), r(std::move(r)) {}
			
			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct addition : binary_expression {
			addition(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct subtraction : binary_expression {
			subtraction(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct multiplication : binary_expression {
			multiplication(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct division : binary_expression {
			division(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct involution : binary_expression {
			involution(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

	}
}
