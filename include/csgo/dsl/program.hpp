#pragma once

#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/constant.hpp>
#include <csgo/dsl/intrinsic.hpp>
#include <csgo/dsl/built_in.hpp>
#include <csgo/dsl/binary_operations.hpp>
#include <csgo/dsl/unary_operations.hpp>
#include <memory>

namespace csgo {
	namespace dsl {

		struct program {
			template <typename T>
			program(T expr) : root(std::make_unique<T>(std::move(expr))) {}

			std::unique_ptr<expression> root;
		};

	}
}
