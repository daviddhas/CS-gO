#pragma once

#include <csgo/lang.hpp>
#include <csgo/workgroup.hpp>
#include <vector>
#include <memory>

namespace csgo {

	struct entry_point {
		std::vector<std::unique_ptr<dsl::variable>> output_variables;
		workgroup wg;
	
		template <typename T, meta::disable<meta::is_specialization<std::tuple, meta::unqualified_t<T>>> = meta::enabler>
		entry_point(T&& single_expression, workgroup wg = {}) : wg(wg) {
			static_assert(std::is_base_of<dsl::variable, meta::unqualified_t<T>>::value, "The return type of a csgo program must be a variable type");
			output_variables.push_back(dsl::make_unique_expression(std::forward<T>(single_expression)));
		}

		template <typename T, meta::enable<meta::is_specialization<std::tuple, meta::unqualified_t<T>>> = meta::enabler>
		entry_point(T&& multi_expression, workgroup wg = {}) : entry_point(meta::tuple_types<meta::unqualified_t<T>>(), std::make_index_sequence<std::tuple_size<meta::unqualified_t<T>>::value>(), std::forward<T>(multi_expression), std::move(wg)) {}

	private:

		template <typename T, typename... Args, std::size_t... I>
		entry_point(meta::types<Args...>, std::index_sequence<I...>, T&& multi_expression, workgroup wg) : wg(wg) {
			static_assert(meta::all<std::is_base_of<dsl::variable, meta::unqualified_t<Args>>...>::value, "The return type tuple of a csgo program must all be variables (not expressions)");
			(void)detail::swallow{ (
				output_variables.push_back(dsl::make_unique_expression(forward_get<I>(multi_expression)))
			, 0 )... };
		}
	};
}
