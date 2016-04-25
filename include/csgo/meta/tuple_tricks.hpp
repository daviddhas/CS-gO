#pragma once

#include "types.hpp"
#include "unqualified.hpp"
#include <tuple>
#include <type_traits>
#include <utility>

namespace csgo { namespace meta {

	template<unsigned I, typename T>
	struct unqualified_tuple_element {
		typedef std::tuple_element_t<I, unqualified_t<T>> type;
	};

	template<unsigned I, typename T>
	using unqualified_tuple_element_t = meta::invoke_t<unqualified_tuple_element<I, T>>;

	template <typename T>
	struct tuple_indices : public std::make_index_sequence<std::tuple_size<unqualified_t<T>>::value> {};

	template <typename... Tn>
	struct expand_types : types<Tn...> {};

	template <typename... Tn>
	struct expand_types<std::tuple<Tn...>> : types<Tn...> {};

	template<typename T, std::size_t L, std::size_t... I>
	auto tail ( T&& t,  std::index_sequence<I..., L> ) -> decltype( std::get<L>( std::forward<T>( t ) ) ) {
		return std::get<L>( std::forward<T>( t ) );
	}

	template<typename T>
	auto tail( T&& t ) -> decltype( tail( std::forward<T>( t ), tuple_indices<unqualified_t<T>>() ) ) {
		return tail( std::forward<T>( t ), tuple_indices<unqualified_t<T>>( ) );
	}

	template <typename T>
	unqualified_tuple_element_t<0, T> head( T&& t ) {
		return std::get<0>( std::forward<T>( t ) );
	}
}}
