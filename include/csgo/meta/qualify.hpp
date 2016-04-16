#pragma once

#include <type_traits>

namespace csgo { namespace meta {

	template <typename Source, typename Naked>
	struct qualify {
		typedef std::conditional_t<std::is_rvalue_reference<Source>::value, std::add_rvalue_reference_t<Naked>, Naked> rvalue_t;
		typedef std::conditional_t<std::is_lvalue_reference<Source>::value, std::add_lvalue_reference_t<rvalue_t>, rvalue_t> lvalue_t;
		typedef std::conditional_t<std::is_const<Source>::value, std::add_const_t<rvalue_t>, lvalue_t> const_t;
		typedef std::conditional_t<std::is_volatile<Source>::value, std::add_volatile_t<rvalue_t>, const_t> type;
	};

}}
