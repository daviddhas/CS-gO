#pragma once

#include <csgo/dsl/expression.hpp>
#include <string>

namespace csgo {
	namespace dsl {
		struct access : expression {
			std::string access_name;

			access(std::string x) : access_name(std::move(x)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};
		
		struct dot_access :access {
			variable& access_into;
			
			dot_access(variable& v, std::string x) : access(std::move(x)), access_into(v) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		const access xaccess{ "x" };
		const access yaccess{ "y" };
		const access zaccess{ "z" };
		const access xyaccess{ "xy" };
		const access xzaccess{ "xz" };
		const access yzaccess{ "yz" };
		const access xyzaccess{ "xyz" };
	}
}
