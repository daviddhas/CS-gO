#include <csgo/lang.hpp>
#include <csgo/compute_program.hpp>
#include <csgo/util.hpp>
#include <iostream>

auto average(csgo::dsl::image2d<glm::vec4> in1, csgo::dsl::image2d<glm::vec4> in2) {
	using namespace csgo::dsl;
	// Perform the desired operations
	image2d<glm::vec4> x = ( in1 + in2 ) / 2;
	
	// Return the variables that you desire
	// They must be uniforms
	return x;
}

void scratch() {
    GLuint size = 32;
    csgo::compute_program p(average);
    csgo::image2d_io<glm::vec4> in1(std::vector<glm::vec4>(size * size, glm::vec4(1)), size);
    csgo::image2d_io<glm::vec4> in2(std::vector<glm::vec4>(size * size, glm::vec4(1, 0, 0, 1)), size);

    p.output_sizes({ { size, size } });
    auto ior = p(in1, in2);

    csgo::image2d_io<glm::vec4> results = ior;
    auto result = results.read();

    csgo::display::image(results);
    while (true);
}