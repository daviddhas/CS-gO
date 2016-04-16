#pragma once

namespace csgo { namespace meta {

	template <typename T, template <typename...> class Templ>
	struct is_specialization : std::false_type { };
	template <typename... T, template <typename...> class Templ>
	struct is_specialization<Templ<T...>, Templ> : std::true_type{ };

}}
