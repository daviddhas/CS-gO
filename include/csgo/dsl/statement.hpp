#pragma once

#include <csgo/binary_operations.hpp>
#include <csgo/unary_operations.hpp>
#include <csgo/built_in.hpp>
#include <csgo/dsl/intrinsic.hpp>
#include <vector>
#include <memory>

namespace csgo {
	namespace dsl {
		struct statement {
			std::vector<std::unique_ptr<expression>> expressions;

			void accept(expression_visitor& v) {
				v.visit(*this);
			}
		};
	}
}
