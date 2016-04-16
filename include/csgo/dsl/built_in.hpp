#pragma once

#include <csgo/dsl/type.hpp>
#include <csgo/dsl/container_variable.hpp>

namespace csgo {
	namespace dsl {

		template <typename T>
		struct image2d : container_variable {
			image2d() : container_variable(type_for<T>::value, type::image_2d) {}
		};

	}
}
