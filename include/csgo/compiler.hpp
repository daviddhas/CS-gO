#pragma once

#include <csgo/glsl/compute_generator.hpp>
#include <csgo/gl/gl.hpp>
#include <csgo/shader.hpp>

namespace csgo {
    namespace glsl {

        struct compiler {

		   shader_byte_code compile( const dsl::ir_program& p, dsl::generator& gen ) {
			   std::string code = gen.generate(p);
			   shader_source source(gen.generates_for(), std::move(code));
			   return shader_byte_code(std::move(source));
		   }

            static GLuint compile(const dsl::ir_program& p, const std::string& code) {

               GLuint handle = gl::CreateProgram();
                GLuint shader = gl::CreateShader(gl::COMPUTE_SHADER);
                compile(handle, shader, code);

                return handle;
            }

            static void compile(GLuint handle, GLuint shader, const std::string& code)
            {
                char const *codeP = code.c_str();
                gl::ShaderSource(shader, 1, &codeP, nullptr);
                gl::CompileShader(shader);

                constexpr GLsizei length = 10240;
                GLchar log[length];

                GLint status;
                gl::GetShaderiv(shader, gl::COMPILE_STATUS, &status);
                gl::GetShaderInfoLog(shader, length - 1, nullptr, log);

                std::cerr << "Compiler Log: " << std::endl << log << std::endl; // for debugging warnings
                if (!status)
                    throw std::runtime_error("GLSL compilation failure");

                gl::AttachShader(handle, shader);

                gl::LinkProgram(handle);

                gl::GetProgramiv(handle, gl::LINK_STATUS, &status);
                gl::GetProgramInfoLog(handle, length - 1, nullptr, log);

                std::cerr << "Linker Log: " << std::endl << log << std::endl; // for debugging warnings
                if (!status)
                    throw std::runtime_error("GLSL compilation failure");
            }
        };
    }
}