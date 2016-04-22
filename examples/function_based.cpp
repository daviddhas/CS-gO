#include <csgo/program.hpp>

#include <iostream>

csgo::entry_point average(csgo::image2d<float> in1, csgo::image2d<float> in2) {
	csgo::image2d<float> x = in1 + in2;
	return std::make_tuple( x + in2 / 2 );
}

void function_based() {
    csgo::program p(average, true);
    int size = 100;
    std::vector<float> in1(size, 1);
    std::vector<float> in2(size, 3);

    auto results = p(csgo::image2d_io<float>(in1, 1), csgo::image2d_io<float>(in2, 1));

    csgo::image2d_io<float> result = results[0];
    for (float f : result.read())
        std::cout << f << " ";
    std::cout << '\n';

	// TODO: actual proper codegen
	// TODO: insert compilation, figure out higher level interface to wrap all of this work up into a single call and return a single
	// csgo::compute_program ...
}