#pragma once

#include <csgo/dsl/function_call.hpp>
#include <csgo/dsl/expression_consume.hpp>

namespace csgo {
	namespace dsl {

		struct intrinsic : expression {
			std::string name;
			std::unique_ptr<expression> param;

			intrinsic(std::string name, std::unique_ptr<expression> arg) : name(std::move(name)), param(std::move(arg)) {

			}

			virtual void accept(statement_visitor& v) const override {
				v.visit(*this);
			}

		};

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic length( T&& v ) {
			return intrinsic("length", make_unique_expression(std::forward<T>(v)));
		}

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic sin(T&& v) {
			return intrinsic("sin", make_unique_expression(std::forward<T>(v)));
		}

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic cos(T&& v) {
			return intrinsic("cos", make_unique_expression(std::forward<T>(v)));
		}

	}
}
