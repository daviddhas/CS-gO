#pragma once

#include <stdexcept>

namespace csgo {

	struct error : std::runtime_error {
		error(std::string message) : std::runtime_error(std::move(message)) {}
	};

	struct shader_error : error {
		shader_error(int errc, std::string message) : std::runtime_error(std::to_string( errc ) + ": " + message) {}
	};

}
