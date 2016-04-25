#pragma once

#include <csgo/gl/platform_gl.hpp>
#include <csgo/shader_stage.hpp>
#include <csgo/enums.hpp>

#include <iostream>
#include <string>

namespace csgo {
	namespace gld {
		
		inline void APIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
			const static std::string sources[] = {
				"OpenGL API",
				"Windowing System",
				"Shader Compiler",
				"External",
				"Application",
				"Other",
			};
			const static std::string types[] = {
				"Error",
				"Behavior - Deprecated",
				"Behavior - Undefined",
				"Portability",
				"Performance",
				"Marker",
				"Push",
				"Pop",
				"Other",
			};
			const static std::string severities[] = {
				"High",
				"Medium",
				"Low",
				"Notification",
			};

			std::string target;
			
			target += "[ ";
			switch (source) {
			case gl::DEBUG_SOURCE_API:
				target += sources[0];
				break;
			case gl::DEBUG_SOURCE_WINDOW_SYSTEM:
				target += sources[1];
				break;
			case gl::DEBUG_SOURCE_SHADER_COMPILER:
				target += sources[2];
				break;
			case gl::DEBUG_SOURCE_THIRD_PARTY:
				target += sources[3];
				break;
			case gl::DEBUG_SOURCE_APPLICATION:
				target += sources[4];
				break;
			case gl::DEBUG_SOURCE_OTHER:
				target += sources[5];
				break;
			}
			target += " ] [ ";
			switch (type) {
			case gl::DEBUG_TYPE_ERROR:
				target += types[0];
				break;
			case gl::DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				target += types[1];
				break;
			case gl::DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				target += types[2];
				break;
			case gl::DEBUG_TYPE_PORTABILITY:
				target += types[3];
				break;
			case gl::DEBUG_TYPE_PERFORMANCE:
				target += types[4];
				break;
			case gl::DEBUG_TYPE_MARKER:
				target += types[5];
				break;
			case gl::DEBUG_TYPE_PUSH_GROUP:
				target += types[6];
				break;
			case gl::DEBUG_TYPE_POP_GROUP:
				target += types[7];
				break;
			case gl::DEBUG_TYPE_OTHER:
				target += types[8];
				break;
			}
			target += " ] [ ";
			switch (severity) {
			case gl::DEBUG_SEVERITY_HIGH:
				target += severities[0];
				break;
			case gl::DEBUG_SEVERITY_MEDIUM:
				target += severities[1];
				break;
			case gl::DEBUG_SEVERITY_LOW:
				target += severities[2];
				break;
			case gl::DEBUG_SEVERITY_NOTIFICATION:
				target += severities[3];
				break;
			}
			target += " ] - ";
			target += message;
			target += "\n";

			switch (severity) {
			case gl::DEBUG_SEVERITY_HIGH:
			case gl::DEBUG_SEVERITY_MEDIUM:
			case gl::DEBUG_SEVERITY_LOW:
			default:
				std::cout << target << std::endl;
				break;
			}
		}
	}
}
