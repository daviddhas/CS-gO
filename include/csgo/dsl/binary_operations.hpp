#pragma once

#include <csgo/dsl/binary_expression.hpp>

namespace csgo {
	namespace dsl {
		namespace dsl_detail {
			template <typename T, meta::enable<is_expression<T>> = meta::enabler>
			inline decltype(auto) make_expression(T&& value) {
				return std::forward<T>(value);
			}

			template <typename T, meta::enable<is_variable<T>> = meta::enabler>
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
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline addition operator + (L&& l, R&& r) {
			return addition(
				dsl_detail::make_unique_expression(std::forward<L>(l)),
				dsl_detail::make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline subtraction operator - (L&& l, R&& r) {
			return subtraction(
				dsl_detail::make_unique_expression(std::forward<L>(l)),
				dsl_detail::make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline multiplication operator * (L&& l, R&& r) {
			return multiplication(
				dsl_detail::make_unique_expression(std::forward<L>(l)),
				dsl_detail::make_unique_expression(std::forward<R>(r))
			);
		}

		template <typename L, typename R, meta::enable<meta::any<is_expression<L>, is_expression<R>>> = meta::enabler>
		inline division operator / (L&& l, R&& r) {
			return division(
				dsl_detail::make_unique_expression(std::forward<L>(l)),
				dsl_detail::make_unique_expression(std::forward<R>(r))
			);
		}
	}
}