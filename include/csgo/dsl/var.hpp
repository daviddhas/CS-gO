#pragma once

#include <csgo/dsl/variable.hpp>

namespace csgo {
	namespace dsl {
		template <typename V>
		struct var : variable {
			var() : variable(type_for<V>::value) {}
			template <typename T>
			var(T initialization) : variable(make_unique_expression(std::move(initialization)), type_for<V>::value) {}

			virtual void accept(expression_visitor& v) {
				v.visit(*this);
			}
		};
	}
}