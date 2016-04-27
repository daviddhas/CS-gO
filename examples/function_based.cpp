#include <csgo/lang.hpp>
#include <csgo/program.hpp>
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

auto red_blue_set() {
	using namespace csgo::dsl;
	// Perform the desired operations
	image2d<float> x;
	x[gl_LocalInvocationID] = glm::vec4(1.0, 0.0, 1.0, 1.0);

	// Return the variables that you desire
	// They must be uniforms
	return x;
}

auto simple(csgo::dsl::image2d<glm::vec4> in) {
    using namespace csgo::dsl;
    image2d<float> x;
    x = in;
    return x;
}

void function_based() {
    GLuint size = 32;
    csgo::program p(simple, { {size, size} }, true);
    csgo::image2d_io<glm::vec4> in1(std::vector<glm::vec4>(size * size, glm::vec4(1)), size);
    csgo::image2d_io<glm::vec4> in2(std::vector<glm::vec4>(size * size, glm::vec4(1, 0, 0, 1)), size);

    std::tuple<csgo::image2d_io<glm::vec4>> results = p(in1, in2);

    auto result = std::get<0>(results).read();
    std::cout << result.size() << " " << size << std::endl;

    for (glm::vec4 v : result)
        std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;

    csgo::display::image(std::get<0>(results));
    while (true);
}