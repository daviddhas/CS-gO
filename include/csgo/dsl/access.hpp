#pragma once

#include <csgo/dsl/expression.hpp>
#include <string>

namespace csgo {
	namespace dsl {
		struct dot_access : expression {
			std::string access_name;

			dot_access(std::string x) : access_name(std::move(x)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		dot_access xyaccess{ "xy" };
		dot_access xyzaccess{ "xyz" };
	}
}
