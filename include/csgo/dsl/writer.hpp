#pragma once

#include <glm/glm.hpp>
#include <ostream>

namespace csgo {
	namespace dsl {

		template <typename X, typename = void>
		struct writer {
			template <typename T>
			void write(std::ostream& ostr, T&& value) {
				ostr << value;
			}
		};

		template <typename T, glm::precision p>
		struct writer<glm::tvec2<T, p>> {
			void write(std::ostream& ostr, const glm::tvec2<T, p>& value) {
				ostr << "vec2( ";
				ostr << value.x;
				ostr << ", " << value.y;
				ostr << " )";
			}
		};

		template <typename T, glm::precision p>
		struct writer<glm::tvec3<T, p>> {
			void write(std::ostream& ostr, const glm::tvec3<T, p>& value) {
				ostr << "vec3( ";
				ostr << value.x;
				ostr << ", " << value.y;
				ostr << ", " << value.z;
				ostr << " )";
			}
		};

		template <typename T, glm::precision p>
		struct writer<glm::tvec4<T, p>> {
			void write(std::ostream& ostr, const glm::tvec4<T, p>& value) {
				ostr << "vec4( ";
				ostr << value.x;
				ostr << ", " << value.y;
				ostr << ", " << value.z;
				ostr << ", " << value.w;
				ostr << " )";
			}
		};
	}
}
