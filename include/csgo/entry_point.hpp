#pragma once

#include <csgo/dsl/statement.hpp>
#include <csgo/workgroup.hpp>

namespace csgo {

    struct entry_point {
        dsl::statement root;
        workgroup wg;

	   template <typename T, meta::disable<meta::is_specialization<std::tuple, meta::unqualified_t<T>>> = meta::enabler>
        entry_point(T&& single_expression, workgroup wg = {}) : wg(wg) {
            root.expressions.push_back(dsl::make_unique_expression(std::forward<T>(single_expression)));
        }

        template <typename T, meta::enable<meta::is_specialization<std::tuple, meta::unqualified_t<T>>> = meta::enabler>
        entry_point(T&& multi_expression, workgroup wg = {}) : entry_point(meta::tuple_types<meta::unqualified_t<T>>(), std::make_index_sequence<std::tuple_size<meta::unqualified_t<T>>::value>(), std::forward<T>(multi_expression), std::move(wg)) {}

        void accept(dsl::expression_visitor& v) { 
            v.visit(root); 
        }

    private:

        template <typename T, typename... Args, std::size_t... I>
        entry_point(meta::types<Args...>, std::index_sequence<I...>, T&& multi_expression, workgroup wg) : wg(wg) {
            root.expressions.reserve(sizeof...(Args));
            root.expressions.push_back(dsl::make_unique_expression(forward_get<I>(multi_expression))...);
        }
    };
}
