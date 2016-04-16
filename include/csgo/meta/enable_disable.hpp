#pragma once

#include <type_traits>
#include "logic.hpp"

namespace csgo { namespace meta {

	enum class enabler_t_ {
		_
	};

	//typedef int enabler_t;
	typedef enabler_t_ enabler_t;

	//constexpr const enabler_t enabler = 0;
	constexpr const enabler_t enabler = enabler_t::_;

	template <typename T, typename... Condition>
	using typed_enable = std::enable_if_t<all<Condition...>::value, T>;

	template <typename T, typename... Condition>
	using typed_disable = std::enable_if_t<not_<all<Condition...>>::value, T>;

	template <typename... Condition>
	using enable = typed_enable<enabler_t, Condition...>;

	template <typename... Condition>
	using disable = typed_disable<enabler_t, Condition...>;

}}
