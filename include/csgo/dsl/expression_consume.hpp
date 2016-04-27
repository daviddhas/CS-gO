#pragma once

#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/blackhole.hpp>

namespace csgo {
	namespace dsl {

		template <typename Expression>
		expression_reference consume(Expression&& expr, bool terminating = is_terminating_expression<meta::unqualified_t<Expression>>::value) {
			expression_reference er(expr.expression_id);
			blackhole& b = get_blackhole();
			b.consume(std::forward<Expression>(expr), terminating);
			return er;
		}

	}
}