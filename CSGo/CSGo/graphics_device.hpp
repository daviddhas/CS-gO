#pragma once

#include "platform_gl.hpp"
#include "vendor_glfw.hpp"
#include <memory>

namespace csgo {

	namespace detail {
		struct glfw_deleter {
			void operator()(GLFWwindow* p) {
				glfwDestroyWindow(p);
			}
		};
	}

	struct graphics_device {
		std::unique_ptr<GLFWwindow, detail::glfw_deleter> window;

		graphics_device() {
			GLboolean r = glfwInit();
			if (r == gl::FALSE_) {
				// Something bad happened
			}
			// Window needs to be invisible, at least for the final version
			glfwWindowHint(GLFW_VISIBLE, gl::FALSE_);
			// Make the window
			window.reset(glfwCreateWindow(0, 0, "csgo blank window", nullptr, nullptr));
			glfwMakeContextCurrent(window.get());
		}

	};

}
