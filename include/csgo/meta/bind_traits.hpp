#pragma once

#include "unqualified.hpp"
#include <tuple>

namespace csgo { namespace meta {

	namespace detail {
		template<class F>
		struct check_deducible_signature {
			template<class G>
			static auto test(int) -> decltype(&G::operator(), void());
			template<class>
			static auto test(...) -> struct nat;

			using type = std::is_void < decltype(test<F>(0)) >;
		};
	}

	template<class F>
	struct has_deducible_signature : detail::check_deducible_signature<F>::type { };

	template <typename T>
	using has_deducible_signature_t = typename has_deducible_signature<T>::type;

	namespace detail {

		template <typename T>
		struct non_functor_function_traits;

		template<typename T, typename R, typename... Args>
		struct non_functor_function_traits < R( T::* )( Args... ) > {
			static const std::size_t arity = sizeof...( Args );
			static const bool is_member_function = true;
			static const bool is_member_variable = false;
			typedef std::tuple<Args...> arg_tuple_type;
			typedef types<Args...> args_type;
			typedef R( T::* function_pointer_type )( Args... );
			typedef typename std::remove_pointer<function_pointer_type>::type function_type;
			typedef R( *free_function_pointer_type )( Args... );
			typedef R return_type;
			typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
			template<std::size_t i>
			using arg = typename std::tuple_element<i, arg_tuple_type>::type;
		};

		template<typename T, typename R, typename... Args>
		struct non_functor_function_traits < R( T::* )( Args... ) const > {
			static const std::size_t arity = sizeof...( Args );
			static const bool is_member_function = true;
			static const bool is_member_variable = false;
			typedef std::tuple<Args...> arg_tuple_type;
			typedef types<Args...> args_type;
			typedef R( T::* function_pointer_type )( Args... );
			typedef typename std::remove_pointer<function_pointer_type>::type function_type;
			typedef R( *free_function_pointer_type )( Args... );
			typedef R return_type;
			typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
			template<std::size_t i>
			using arg = typename std::tuple_element<i, arg_tuple_type>::type;
		};

		template<typename R, typename... Args>
		struct non_functor_function_traits < R( Args... ) > {
			static const std::size_t arity = sizeof...( Args );
			static const bool is_member_function = false;
			static const bool is_member_variable = false;
			typedef std::tuple<Args...> arg_tuple_type;
			typedef types<Args...> args_type;
			typedef R( function_type )( Args... );
			typedef R( *function_pointer_type )( Args... );
			typedef R( *free_function_pointer_type )( Args... );
			typedef R return_type;
			typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
			template<std::size_t i>
			using arg = typename std::tuple_element<i, arg_tuple_type>::type;
		};

		template<typename R, typename... Args>
		struct non_functor_function_traits < R( *)( Args... ) > {
			static const std::size_t arity = sizeof...( Args );
			static const bool is_member_function = false;
			static const bool is_member_variable = false;
			typedef std::tuple<Args...> arg_tuple_type;
			typedef types<Args...> args_type;
			typedef R( function_type )( Args... );
			typedef R( *function_pointer_type )( Args... );
			typedef R( *free_function_pointer_type )( Args... );
			typedef R return_type;
			typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
			template<std::size_t i>
			using arg = typename std::tuple_element<i, arg_tuple_type>::type;
		};

		template <typename T>
		struct member_traits {};

		template<typename T, typename R>
		struct member_traits<R T::* const > {
			static const std::size_t arity = 1;
			static const bool is_member_function = false;
			static const bool is_member_variable = true;
			typedef std::tuple<R> arg_tuple_type;
			typedef types<R> args_type;
			typedef R(T::* function_pointer_type)();
			typedef typename std::remove_pointer<function_pointer_type>::type function_type;
			typedef R(*free_function_pointer_type)();
			typedef R return_type;
			typedef typename std::remove_pointer<free_function_pointer_type>::type signature_type;
			template<std::size_t i>
			using arg = typename std::tuple_element<i, arg_tuple_type>::type;
		};

		template <typename T, bool = has_deducible_signature<T>::value>
		struct fx_traits : public detail::non_functor_function_traits<T> { };

		template <typename T>
		struct fx_traits<T, true> : detail::non_functor_function_traits<decltype(&unqualified_t<T>::operator())> { };
		
		template <typename T, bool = std::is_member_object_pointer<T>::value>
		struct callable_traits : detail::fx_traits<T> { };
		
		template <typename T>
		struct callable_traits<T, true> : member_traits<T> {};
	}

	template <typename T>
	struct bind_traits : detail::callable_traits<T> {};

	template <typename T>
	using function_args_t = typename bind_traits<T>::args_type;

	template <typename T>
	using function_signature_t = typename bind_traits<T>::signature_type;

}}
