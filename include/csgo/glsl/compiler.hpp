#pragma once

#include <csgo/glsl/glsl_generator.hpp>
#include <csgo/gl_detail/gl.hpp>
#include <GLFW/glfw3.h>

namespace csgo {
    namespace glsl {

        struct compiler {
            static GLuint compile(const dsl::ir_program& p, const std::string& code, bool makeContextQ) {
                if (makeContextQ)
                    makeContext();
			 
			 std::cout << code;

                GLuint handle = gl::CreateProgram();
                GLuint shader = gl::CreateShader(gl::COMPUTE_SHADER);

                char const *codeP = code.c_str();
                gl::ShaderSource(shader, 1, &codeP, nullptr);
                gl::CompileShader(shader);

                constexpr GLsizei length = 10240;
                GLchar log[length];

                GLint status;
                gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
                gl::GetShaderInfoLog(shader, length - 1, nullptr, log);

                std::cerr << "Log: " << std::endl << log << std::endl; // for debugging warnings
                if (!status)
                    throw std::runtime_error("GLSL compilation failure");

                gl::AttachShader(handle, shader);
                gl::LinkProgram(handle);

                gl::GetProgramiv(handle, gl::LINK_STATUS, &status);
                gl::GetProgramInfoLog(handle, length - 1, nullptr, log);
                if (!status)
                    throw std::runtime_error("GLSL linker failure");

                return handle;
            }

        private:
            static void makeContext() {
                if (glfwGetCurrentContext() != nullptr)
                    return;

                if (!glfwInit())
                    throw std::runtime_error("GLFW failed to initialize");

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                GLFWwindow *window = glfwCreateWindow(1024, 512, "CS Go", nullptr, nullptr);
                glfwMakeContextCurrent(window);

			 // hook up OpenGL debug callback
			 // So we get error messages printed out to the console
			 gl::DebugMessageCallback(gl_detail::debug_callback, nullptr);
            }
        };
    }
}