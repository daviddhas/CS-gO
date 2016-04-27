#pragma once

#include <csgo/dsl/variable.hpp>

namespace csgo {
	namespace dsl {
		template <typename V>
		struct var : variable {
			typedef var<V> parent_type;

			var() : variable(type_for<V>::value) {}
			template <typename T, meta::enable<
				is_expression<T>, 
				meta::not_<std::is_base_of<parent_type, meta::unqualified_t<T>>>
			> = meta::enabler>
			var(T&& initialization) : variable(type_for<V>::value) {
				consume(declaration_assignment{
					make_unique_expression(*this),
					make_unique_expression(std::forward<T>(initialization))
				});
			}

			virtual void accept(statement_visitor& v) {
				v.visit(*this);
			}
		};
	}
}