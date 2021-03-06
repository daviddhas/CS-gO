#pragma once

#include <csgo/meta/bare_naked.hpp>
#include <csgo/meta/callable_enable_if.hpp>
#include <csgo/meta/enable_disable.hpp>
#include <csgo/meta/bind_traits.hpp>
#include <csgo/meta/is_specialization.hpp>
#include <csgo/meta/logic.hpp>
#include <csgo/meta/qualify.hpp>
#include <csgo/meta/sfinae_types.hpp>
#include <csgo/meta/tuple_tricks.hpp>
#include <csgo/meta/types.hpp>
#include <csgo/meta/qualify.hpp>
#include <csgo/meta/unwrap.hpp>
#include <csgo/meta/unqualified.hpp>
#include <initializer_list>

namespace csgo {
	namespace detail {
		using swallow = std::initializer_list<int>;
	}

	template <std::size_t I, typename Tuple>
	decltype(auto) forward_get(Tuple&& tuple) {
		return std::forward<std::tuple_element_t<I, meta::unqualified_t<Tuple>>>(std::get<I>(tuple));
	}
}
