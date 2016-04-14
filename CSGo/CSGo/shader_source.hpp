#pragma once

#include "shader_stage.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <memory>
#include <cstddef>

namespace csgo {

	struct blob {
		void* data;
		std::size_t size;
	};

	struct shader_source {
		std::string entry_point;
		shader_stage stage;
		std::string source_file;
		std::string source;
		
		bool compilable() const {
			return !entry_point.empty() && (!source.empty() || (source_file.empty()));
		}

		operator bool() const {
			return compilable();
		}

		shader_source(shader_stage stage, std::string source, std::string entrypoint = "main", std::string file = "") :
			source(std::move(source)), entry_point(std::move(entrypoint)),
			stage(stage),
			source_file(file) {
			if (!source.empty() || source_file.empty())
				return;
			// Open at end for tellg
			std::ifstream sourcecontents(source_file, std::ios::end);
			if (!sourcecontents) {
				return;
			}
			// Allocate memory up front from tellg()
			source.reserve(static_cast<std::size_t>(sourcecontents.tellg()));
			sourcecontents.seekg(0, std::ios::beg);
			source.assign(std::istreambuf_iterator<char>(sourcecontents), std::istreambuf_iterator<char>());
		}
	};

	struct shader_byte_code {
	private:
		friend struct shader;
		struct bytecode_deleter {
			void operator() (void* p) {
				// Nothing need doing for OpenGL
			}
		};

		shader_source bytecodesource;
		std::unique_ptr<void, bytecode_deleter> bytecode;
		std::size_t bytecodelength;
		std::string err;
		uint32_t errcode;

	public:

		shader_byte_code(shader_source source) : bytecodesource(source) {

		}
		shader_byte_code(shader_byte_code&& mov) = default;
		shader_byte_code& operator=(shader_byte_code&& mov) = default;

		blob byte_code() const {
			return blob{ bytecode.get(), bytecodelength };
		}

		const shader_source& source() const {
			return bytecodesource;
		}

		void* bytecode_resource() const {
			return bytecode.get();
		}

		shader_stage stage() const {
			return bytecodesource.stage;
		}

		const std::string& errors() const {
			return err;
		}

		int32_t error_code() const {
			return errcode;
		}

		bool has_errors() const {
			return !err.empty();
		}

		explicit operator bool() const {
			return has_errors();
		}

	};
}