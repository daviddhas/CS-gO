#pragma once

#include <csgo/dsl/function_call.hpp>
#include <csgo/dsl/expression_consume.hpp>

namespace csgo {
	namespace dsl {

		struct intrinsic : expression {
			std::string name;
			std::vector<std::unique_ptr<expression>> params;

			template <typename... Args>
			intrinsic(std::string name, Args&&... args) : name(std::move(name)), params(make_unique_expression(std::forward<Args>(args))...) {

			}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}

		};

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic length( T&& v ) {
			return intrinsic("length", std::forward<T>(v));
		}

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic sin(T&& v) {
			return intrinsic("sin", std::forward<T>(v));
		}

		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		intrinsic cos(T&& v) {
			return intrinsic("cos", std::forward<T>(v));
		}

	}
}
