#pragma once

namespace csgo { namespace meta {

	template <typename... Tn>
	struct void_type {
		typedef void type;
	};

	template <typename... Tn>
	using void_type_t = typename void_type<Tn...>::type;

}}
