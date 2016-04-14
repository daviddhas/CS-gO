#pragma once

#include "platform_gl.hpp"
#include "shader_source.hpp"
#include "error.hpp"
#include <string>

namespace csgo {

	struct shader {
	private:
		struct shader_deleter {
			void operator ()(void* p) {
				int id = reinterpret_cast<int>(p);
				gl::DeleteProgram(id);
			}
		};

		struct reflection_deleter {
			void operator() (void* p) {
				// specifically do nothing
			}
		};


		shader_byte_code shaderbytecode;
		std::unique_ptr<void, shader_deleter> shaderresource;
		std::unique_ptr<void, reflection_deleter> reflection;

	public:
		const shader_byte_code& shader::byte_code() const {
			return shaderbytecode;
		}

		uint32_t shader_resource() const {
			return reinterpret_cast<uint32_t>(shaderresource.get());
		}

		shader_stage stage() const {
			return shaderbytecode.stage();
		}

		shader(shader_source description, shader_stage must_be = shader_stage::unknown) : shader(shader_byte_code(std::move(description)), must_be) {

		}

		shader(shader_byte_code description, shader_stage must_be = shader_stage::unknown) : shaderresource(nullptr), reflection(nullptr), shaderbytecode(std::move(description)) {
			if (must_be != shader_stage::unknown && must_be != shaderbytecode.stage()) {
				throw shader_error(0x1, "shader byte code must match the expected shader type");
			}
			const std::string& sourcebytecode = byte_code().source().source;
			const GLchar* const code = static_cast<const GLchar* const>(sourcebytecode.data());
			const GLint codesize = static_cast<GLint>(sourcebytecode.size());
			gl_detail::shader_stage typedglstage = gl_detail::to_platform(stage());
			GLuint glstage = static_cast<GLuint>(typedglstage);
			GLuint programid = gl::CreateShaderProgramv(glstage, 1, &code);
			shaderresource.reset(reinterpret_cast<void*>(programid));

			GLint r = 0;
			gl::GetProgramiv(programid, gl::LINK_STATUS, &r);
			if (r == gl::FALSE_) {
				// Panic
				GLint errorsize = 0;
				gl::GetProgramiv(programid, gl::INFO_LOG_LENGTH, &errorsize);

				std::string& err = shaderbytecode.err;
				err.resize(errorsize);
				GLchar* errortarget = const_cast<GLchar*>(static_cast<const GLchar*>(err.data()));
				gl::GetProgramInfoLog(programid, errorsize, &errorsize, errortarget);
				throw shader_error(gl::GetError(), err);
			}
		}
	};

	struct vertex_shader : public shader {
		vertex_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::vertex) {}
	};

	struct hull_shader : public shader {
		hull_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::hull) {}
	};

	struct domain_shader : public shader {
		domain_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::domain) {}
	};

	struct geometry_shader : public shader {
		geometry_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::geometry) {}
	};

	struct pixel_shader : public shader {
		pixel_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::pixel) {}
	};

	struct compute_shader : public shader {
		compute_shader(shader_source methoddesc) : shader(std::move(methoddesc), shader_stage::compute) {}
	};
};
