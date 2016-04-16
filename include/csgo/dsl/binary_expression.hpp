#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/dsl/expression.hpp>
#include <memory>

namespace csgo {
	namespace dsl {

		struct binary_expression : expression {
			std::unique_ptr<expression> l;
			std::unique_ptr<expression> r;

			binary_expression(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : l(std::move(l)), r(std::move(r)) {}

		};

		struct assignment : binary_expression {
			assignment(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

		struct addition : binary_expression {
			addition(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

		struct subtraction : binary_expression {
			subtraction(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

		struct multiplication : binary_expression {
			multiplication(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

		struct division : binary_expression {
			division(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

		struct involution : binary_expression {
			involution(std::unique_ptr<expression> l, std::unique_ptr<expression> r) : binary_expression(std::move(l), std::move(r)) {}
		};

	}
}
