#include <csgo/program.hpp>
#include <csgo/dsl/generator.hpp>
#include <csgo/glsl/glsl_generator.hpp>

#include <iostream>

csgo::dsl::entry_point average(csgo::dsl::image2d<float> in1, csgo::dsl::image2d<float> in2) {
	using namespace csgo::dsl;
	image2d<float> x = (in1 + in2);
	return x / 2;
}

void function_based() {
    csgo::program p(average);
	csgo::glsl::glsl_generator gen;
	// TODO: actual proper codegen
	// TODO: insert compilation, figure out higher level interface to wrap all of this work up into a single call and return a single
	// csgo::compute_program ...
}