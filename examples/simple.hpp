#pragma once

#include <csgo/compute_program.hpp>
#include <csgo/util/window.hpp>
#include "types.hpp"

inline auto simple_program(csgo::dsl::image2d<glm::vec4> in) {
	using namespace csgo::dsl;

	// Declare your output parameters
	// You can declare them wherever you want,
	// we just happen to put ours up here
	image2d<glm::vec4> x;

	// Perform the desired operations
	x = in;

	// Return the variables that you desire
	// They must be uniforms
	return x;
}

struct simple {

	csgo::compute_program p;

	simple() : p(simple_program) {

	}

	void operator()(GLFWwindow& window, f_milliseconds time) {

	}
};