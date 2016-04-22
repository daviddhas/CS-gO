#pragma once

#include <csgo/dsl/expression.hpp>
#include <vector>
#include <memory>

namespace csgo {
	namespace dsl {
		
		struct statement {
			std::vector<std::unique_ptr<expression>> expressions;

			virtual void accept(statement_visitor& v) {
				v.visit(*this);
			}
		};
	}
}
