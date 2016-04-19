#pragma once

#include "types.hpp"
#include "void_type.hpp"

namespace csgo { namespace meta {

	template<int i, typename... >
	struct meta_int : public std::integral_constant<int, i> {};

	template<unsigned int i, typename... >
	struct meta_uint : public std::integral_constant<unsigned int, i> {};

	template<long i, typename... >
	struct meta_long : public std::integral_constant<long, i> {};

	template<unsigned long i, typename... >
	struct meta_ulong : public std::integral_constant<unsigned long, i> {};

	template<long long i, typename... >
	struct meta_long_long : public std::integral_constant<long long, i> {};

	template<unsigned long long i, typename... >
	struct meta_ulong_long : public std::integral_constant<unsigned long long, i> {};

	template<bool b, typename... >
	struct meta_bool : public std::integral_constant<bool, b> {};

	template<typename If, typename Then, typename Else>
	struct conditional : public std::conditional<If::value, Then, Else> {};

	template <typename If, typename Then, typename Else>
	using conditional_t = invoke_t<conditional<If, Then, Else>>;

	template<typename T>
	struct not_ : public meta_bool<!T::value> {};

	template<typename... Tn>
	struct any : public meta_bool<false> {};

	template<typename T, typename... Tn>
	struct any<T, Tn...> : public conditional_t<T, meta_bool<true>, invoke_t<any<Tn...>>>{};

	template <typename... Tn>
	using any_t = invoke_t<any<Tn...>>;

	template<typename... Tn>
	struct all : public meta_bool<true> {};

	template<typename T, typename... Tn>
	struct all<T, Tn...> : public conditional_t<T, all<Tn...>, invoke_t<meta_bool<false>>>{};

	template <typename... Tn>
	using all_t = invoke_t<all<Tn...>>;

	template<typename Lhs, typename Rhs>
	using or_ = std::integral_constant<bool, Lhs::value || Rhs::value>;

	template<typename Lhs, typename Rhs>
	using xor_ = std::integral_constant<bool, Lhs::value ^ Rhs::value>;

	template<typename Lhs, typename Rhs>
	using and_ = std::integral_constant<bool, Lhs::value && Rhs::value>;

	template <std::ptrdiff_t v1, std::ptrdiff_t... values>
	struct max {
		static const std::ptrdiff_t value = max<values...>::value < v1 ? v1 : max<values...>::value;
	};

	template <std::ptrdiff_t v>
	struct max <v> {
		static const std::ptrdiff_t value = v;
	};

}}
