#pragma once

#include "unqualified.hpp"
#include <tuple>
#include <cstddef>

namespace csgo { namespace meta {

	template <typename T>
	using invoke_t = typename T::type;

	namespace tmp_detail {
		template <std::ptrdiff_t i, typename Target, typename T, typename... Tn>
		struct index_of_impl {
			static const std::ptrdiff_t value = std::is_same<Target, T>::value ? i : index_of_impl<i + 1, Target, Tn...>::value;
		};

		template <std::ptrdiff_t i, typename T>
		struct index_of_impl<i, T, T> {
			static const std::ptrdiff_t value = i;
		};

		template <std::ptrdiff_t i, typename T, typename Target>
		struct index_of_impl < i, T, Target > {
			static const std::ptrdiff_t value = -1;
		};

		template <std::ptrdiff_t n, typename T, typename... Tn>
		struct at_impl {
			static_assert( n > -1, "index value is negative" );
			typedef meta::invoke_t<at_impl<n - 1, Tn...>> type;
		};

		template <typename T, typename... Tn>
		struct at_impl <0, T, Tn...> {
			typedef T type;
		};
	}

	template <typename... Tn>
	struct types {};

	template <typename T>
	struct types<T> {
		typedef T type;
	};

	template <std::ptrdiff_t n, typename T, typename... Tn>
	struct make_types_n : public make_types_n<n - 1, T, T, Tn... > {};

	template <typename T, typename... Tn>
	struct make_types_n<0, T, Tn...> : public types < Tn... >{};

	template<std::ptrdiff_t I, typename... Tn>
	struct at {
		static_assert(I > -1, "index value is negative");
		static const std::ptrdiff_t value = I;
		typedef meta::invoke_t<tmp_detail::at_impl<I, Tn...>> type;
	};

	template <typename T, typename... Tn>
	struct index_of {
		static const std::ptrdiff_t value = tmp_detail::index_of_impl<0, T, Tn...>::value;
	};

	template<std::ptrdiff_t I, typename... Tn>
	using at_t = meta::invoke_t<at<I, Tn...>>;

}}
