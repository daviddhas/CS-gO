#pragma once

#include <csgo/gl/gl.hpp>
#include <memory>

namespace csgo {
	namespace util {
		struct glfw_deleter {
			void operator()(GLFWwindow* p) {
				glfwDestroyWindow(p);
			}
		};

		typedef std::unique_ptr<GLFWwindow, glfw_deleter> window_pointer;

		inline window_pointer make_window(int width = 800, int height = 600) {
			if (!glfwInit())
				throw std::runtime_error("GLFW failed to initialize");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#ifdef _DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window_pointer window(glfwCreateWindow(width, height, "CS Go", nullptr, nullptr));
			glfwMakeContextCurrent(window.get());

#ifdef _DEBUG
			// hook up OpenGL debug callback
			// So we get error messages printed out to the console
			gl::DebugMessageCallback(gld::debug_callback, nullptr);
#endif
			return window;
		}
	}
}

