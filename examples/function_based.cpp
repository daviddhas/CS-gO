#include <csgo/program.hpp>
#include <csgo/dsl/generator.hpp>
#include <csgo/glsl/glsl_generator.hpp>
#include <csgo/lang.hpp>

#include <iostream>

csgo::entry_point average(csgo::dsl::image2d<float> in1, csgo::dsl::image2d<float> in2) {
	using namespace csgo::dsl;
	// Perform the desired operations
	image2d<float> x = in1 + in2;
	image2d<float> y = x / 2;

	// Return the variables that you desire
	// They must be uniforms
	return std::make_tuple( x, y );
}

void function_based() {
    csgo::program p(average, true);
    p.run();

	// TODO: actual proper codegen
	// TODO: insert compilation, figure out higher level interface to wrap all of this work up into a single call and return a single
	// csgo::compute_program ...
}