#pragma once

#include "platform_gl.hpp"
#include "vendor_glfw.hpp"
#include "error.hpp"
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
				throw error("Failed to initialize OpenGL - glfwInit");
			}
			// Window needs to be invisible, at least for the final version
			glfwWindowHint(GLFW_VISIBLE, gl::FALSE_);

			// Demand a 4.3 OpenGL context, at least
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			// Make the window
			window.reset(glfwCreateWindow(800, 600, "csgo blank window", nullptr, nullptr));
			if (window.get() == nullptr) {
				throw error("Failed to initialize OpenGL - glfwCreateWindow");
			}
			glfwMakeContextCurrent(window.get());
		}

	};

}
