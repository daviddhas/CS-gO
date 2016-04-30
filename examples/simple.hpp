#pragma once

#include <csgo/compute_program.hpp>
#include <csgo/util/window.hpp>
#include <csgo/display.hpp>
#include "types.hpp"
#include "basic.hpp"

inline auto simple_program(csgo::dsl::image2d<glm::vec4> in1, csgo::dsl::image2d<glm::vec4> in2) {
	using namespace csgo::dsl;

	// Declare your output parameters
	// You can declare them wherever you want,
	// we just happen to put ours up here
	image2d<glm::vec4> x = (in1 + in2) / 2;

	// Return the variables that you desire
	// They must be uniforms
	return x;
}

struct simple : basic {

	csgo::compute_program p;
	csgo::image2d_io<glm::vec4> in1, in2;

	simple() : p(simple_program), 
	in1({32 * 32, glm::vec4(1.0, 0.0, 0.0, 1.0)}, 32),
	in2({ 32 * 32, glm::vec4(1.0, 1.0, 1.0, 1.0) }, 32) {

	}

	void operator()(GLFWwindow& window, f_milliseconds time) {
		int w = 32, h = 32;
		//glfwGetWindowSize(&window, &w, &h);
		p.output_sizes({ { static_cast<GLuint>(w), static_cast<GLuint>(h) } });
		csgo::image2d_io<glm::vec4> im = p(in1, in2);
		show(window, time, im.get_texture_ID());
	}
};