#include <csgo/program.hpp>

#include <iostream>

csgo::entry_point average(csgo::image2d<float> in1, csgo::image2d<float> in2) {
	using namespace csgo::dsl;
	csgo::image2d<float> x = in1 + in2;
	return std::make_tuple( x + in2 / 2 );
}

void function_based() {
    csgo::program p(average, true);
    p.run();

/*    image2d_io;
    image2d_array_io;
    buffer_io;
    */
	// TODO: actual proper codegen
	// TODO: insert compilation, figure out higher level interface to wrap all of this work up into a single call and return a single
	// csgo::compute_program ...
}