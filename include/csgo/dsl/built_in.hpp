#pragma once

#include <csgo/dsl/var.hpp>

namespace csgo {
	namespace dsl {

		struct vec2 : var<glm::vec2> {
			using var<glm::vec2>::var;
		};
		struct vec3 : var<glm::vec3> {
			using var<glm::vec3>::var;
		};
		struct vec4 : var<glm::vec4> {
			using var<glm::vec4>::var;
		};

		template <typename P>
		struct image2d : container_variable {
			image2d() : container_variable(type_for<P>::value, type::image_2d) {}
			template <typename T>
			image2d(T initialization) : container_variable(make_unique_expression(std::move(initialization)), type_for<T>::value, type::image_2d) {}

			virtual void accept(expression_visitor& v) {
				v.visit(*this);
			}
		};

	}
}
