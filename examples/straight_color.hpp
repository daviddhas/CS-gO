#pragma once

#include <csgo/compute_program.hpp>
#include <csgo/util/window.hpp>
#include "basic.hpp"
#include "types.hpp"

inline auto straight_color_program() {
	using namespace csgo::dsl;
	
	// Declare your output parameters
	// You can declare them wherever you want,
	// we just happen to put ours up here
	image2d<glm::vec4> x;
	
	// Perform the desired operations
	x[gl_GlobalInvocationID.xy] = glm::vec4( 1.0, 0.0, 1.0, 1.0 );

	// Return the variables that you desire
	// They must be uniforms
	return x;
}

struct straight_color : basic {

	csgo::compute_program p;
	
	straight_color() : p(straight_color_program) {

	}

	void operator()(GLFWwindow& window, f_milliseconds time) {
		int w = 0, h = 0;
		glfwGetWindowSize(&window, &w, &h);
		p.output_sizes({ { static_cast<GLuint>(w), static_cast<GLuint>(h)} });
		csgo::image2d_io<glm::vec4> result = p();
		show(window, time, result.get_texture_ID());
	}
};