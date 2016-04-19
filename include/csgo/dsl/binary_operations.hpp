#pragma once

#include <csgo/dsl/binary_expression.hpp>

namespace csgo {
	namespace dsl {
		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline addition operator + (L&& l, R&& r) {
			return addition(
				make_unique_expression(std::forward<L>(l)),
				make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline subtraction operator - (L&& l, R&& r) {
			return subtraction(
				make_unique_expression(std::forward<L>(l)),
				make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline multiplication operator * (L&& l, R&& r) {
			return multiplication(
				make_unique_expression(std::forward<L>(l)),
				make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline division operator / (L&& l, R&& r) {
			return division(
				make_unique_expression(std::forward<L>(l)),
				make_unique_expression(std::forward<R>(r))
			);
		}
	}
}