#pragma once

#include <csgo/dsl/binary_expression.hpp>

namespace csgo {
    template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
    inline dsl::addition operator + (L&& l, R&& r) {
        return dsl::addition(
            dsl::make_unique_expression(std::forward<L>(l)),
            dsl::make_unique_expression(std::forward<R>(r))
        );
    }

    template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
    inline dsl::subtraction operator - (L&& l, R&& r) {
        return dsl::subtraction(
            dsl::make_unique_expression(std::forward<L>(l)),
            dsl::make_unique_expression(std::forward<R>(r))
        );
    }

    template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
    inline dsl::multiplication operator * (L&& l, R&& r) {
        return dsl::multiplication(
            dsl::make_unique_expression(std::forward<L>(l)),
            dsl::make_unique_expression(std::forward<R>(r))
        );
    }

    template <typename L, typename R, meta::enable<meta::any<dsl::is_expression<L>, dsl::is_expression<R>>> = meta::enabler>
    inline dsl::division operator / (L&& l, R&& r) {
        return dsl::division(
            dsl::make_unique_expression(std::forward<L>(l)),
            dsl::make_unique_expression(std::forward<R>(r))
        );
    }
}