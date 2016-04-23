#include <csgo/program.hpp>

#include <iostream>

csgo::entry_point average(csgo::image2d<float> in1, csgo::image2d<float> in2) {
	csgo::image2d<float> x = in1 + in2;
	return std::make_tuple( x + in2 / 2 );
}

void function_based() {
    GLuint size = 100;
    csgo::program p(average, { {1, size} }, true);
    std::vector<float> in1(size, 1);
    std::vector<float> in2(size, 3);

    auto results_ = p(csgo::image2d_io<float>(in1, 1), csgo::image2d_io<float>(in2, 1));

    std::tuple<csgo::image2d_io<float>> results = results_;
    for (float f : std::get<0>(results).read())
        std::cout << f << " ";
    std::cout << '\n';

	// TODO: actual proper codegen
	// TODO: insert compilation, figure out higher level interface to wrap all of this work up into a single call and return a single
	// csgo::compute_program ...
}