#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/dsl/expression_consume.hpp>

namespace csgo {
	namespace dsl {
		struct unary_expression : expression {
			std::unique_ptr<expression> l;

			unary_expression(std::unique_ptr<expression> l) : l(std::move(l)) {}
		};
	}
}
