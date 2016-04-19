#pragma once

namespace csgo { namespace meta {

	template <template <typename...> class Templ, typename T>
	struct is_specialization : std::false_type { };
	template <template <typename...> class Templ, typename... T>
	struct is_specialization<Templ, Templ<T...>> : std::true_type{ };

}}
