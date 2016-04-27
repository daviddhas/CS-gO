#pragma once

#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/blackhole.hpp>

namespace csgo {
	namespace dsl {

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		inline decltype(auto) make_expression(T&& value) {
			return std::forward<T>(value);
		}

		template <typename T, meta::enable<is_primitive<T>> = meta::enabler>
		inline decltype(auto) make_expression(T&& value) {
			return typed_constant<meta::unqualified_t<T>>(std::forward<T>(value));
		}

		template <typename T>
		inline decltype(auto) make_unique_expression(T&& value) {
			decltype(auto) r = make_expression(std::forward<T>(value));
			return std::make_unique<meta::unqualified_t<decltype(r)>>(std::forward<decltype(r)>(r));
		}

		template <typename Expression>
		expression_reference consume(Expression&& expr, bool terminating = is_terminating_expression<meta::unqualified_t<Expression>>::value) {
			expression_reference er(expr.expression_id);
			blackhole& b = get_blackhole();
			b.consume(std::forward<Expression>(expr), terminating);
			return er;
		}

	}
}