#include <csgo/dsl/program.hpp>
#include <csgo/dsl/generator.hpp>
#include <csgo/dsl/glsl_generator.hpp>

#include <iostream>

csgo::dsl::entry_point average(csgo::dsl::image2d<float> in1, csgo::dsl::image2d<float> in2) {
	using namespace csgo::dsl;
	image2d<float> x = (in1 + in2);
	return x / 2;
}

void function_based() {
	csgo::dsl::program p = csgo::dsl::make_program(average);
	csgo::dsl::glsl_generator gen;
	std::string code = csgo::dsl::generate(p, gen);
	std::cout << code;
}