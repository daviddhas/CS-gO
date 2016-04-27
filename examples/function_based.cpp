#include <csgo/lang.hpp>
#include <csgo/program.hpp>
#include <csgo/util.hpp>
#include <iostream>

auto average(csgo::dsl::image2d<int> in1, csgo::dsl::image2d<int> in2) {
	using namespace csgo::dsl;
	// Perform the desired operations
	image2d<int> x = ( in1 + in2 ) / 2;
	
	// Return the variables that you desire
	// They must be uniforms
	return x;
}

auto red_blue_set() {
	using namespace csgo::dsl;
	// Perform the desired operations
	image2d<float> x;
	x[gl_LocalInvocationID] = glm::vec4(1.0, 0.0, 1.0, 1.0);

	// Return the variables that you desire
	// They must be uniforms
	return x;
}

auto simple(csgo::dsl::image2d<float> in) {
    using namespace csgo::dsl;
    image2d<float> x;
    x = in;
    return x;
}

void function_based() {
    GLuint size = 32;
    csgo::program p(average, { {size, size} }, true);
    csgo::image2d_io<int> in1(std::vector<int>(size * size, 1), size);
    csgo::image2d_io<int> in2(std::vector<int>(size * size, 2), size);

    std::tuple<csgo::image2d_io<int>> results = p(in1, in2);

    for (int f : std::get<0>(results).read())
        std::cout << f << " ";
    std::cout << '\n';

//    csgo::display::image(std::get<0>(results));
    while (true);

	// TODO: actual proper codegen
}