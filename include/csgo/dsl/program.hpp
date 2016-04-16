#pragma once

#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/constant.hpp>
#include <csgo/dsl/intrinsic.hpp>
#include <csgo/dsl/built_in.hpp>
#include <csgo/dsl/binary_operations.hpp>
#include <csgo/dsl/unary_operations.hpp>
#include <csgo/type_traits.hpp>
#include <memory>

namespace csgo {
	namespace dsl {

		struct program {
			template <typename T>
			program(T expr) : root(std::make_unique<T>(std::move(expr))) {}

			std::unique_ptr<expression> root;
		};

		namespace dsl_detail {
			template <typename... Args, typename F>
			program make_program(meta::types<Args...>, F&& f) {
				// Instantiate default-constructed arguments and call
				return f(Args()...);
			}
		}

		template <typename F>
		program make_program(F&& f) {
			// determine the arguments of F
			typedef typename meta::bind_traits<meta::unqualified_t<F>>::args_type args_type;
			return dsl_detail::make_program(args_type(), std::forward<F>(f));
		}

	}
}
