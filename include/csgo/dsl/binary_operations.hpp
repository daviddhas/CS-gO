#pragma once

#include <csgo/dsl/binary_expression.hpp>

namespace csgo {
	namespace dsl {

		template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
		inline addition operator + (L&& l, R&& r) {
			dsl::addition op(
				dsl::make_unique_expression(std::forward<L>(l)),
				dsl::make_unique_expression(std::forward<R>(r))
			);
			return op;
		}

		template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
		inline subtraction operator- (L&& l, R&& r) {
			dsl::subtraction op(
				dsl::make_unique_expression(std::forward<L>(l)),
				dsl::make_unique_expression(std::forward<R>(r))
			);
			return op;
		}

		template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
		inline multiplication operator * (L&& l, R&& r) {
			dsl::multiplication op(
				dsl::make_unique_expression(std::forward<L>(l)),
				dsl::make_unique_expression(std::forward<R>(r))
			);
			return op;
		}

		template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
		inline division operator / (L&& l, R&& r) {
			dsl::division op(
				dsl::make_unique_expression(std::forward<L>(l)),
				dsl::make_unique_expression(std::forward<R>(r))
			);
			return op;
		}
	}
}