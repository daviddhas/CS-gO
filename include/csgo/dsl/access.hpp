#pragma once

#include <csgo/dsl/expression.hpp>
#include <string>

namespace csgo {
	namespace dsl {
		struct dot_access {
			std::string access_name;
		};

		dot_access xyaccess{ "xy" };
		dot_access xyzaccess{ "xyz" };
	}
}
