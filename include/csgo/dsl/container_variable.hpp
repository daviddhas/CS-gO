#pragma once

#include <csgo/dsl/variable.hpp>

namespace csgo {
	namespace dsl {

		struct container_variable : variable {
			type contained_type;
			container_variable() : container_variable(type::single_precision, type::image_2d) {}
			container_variable(type innertype) : container_variable(innertype, type::image_2d) {}
			container_variable(type innertype, type thistype) : variable(thistype),  contained_type(innertype) {}
		};

	}
}
