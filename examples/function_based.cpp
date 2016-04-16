#include <csgo/dsl/ast.hpp>

csgo::dsl::program average(csgo::dsl::image2d<float> in1, csgo::dsl::image2d<float> in2) {
	return ( in1 + in2 ) / 2;
}

void function_based() {
	csgo::dsl::program p = csgo::dsl::make_program(average);
	csgo::dsl::abstract_syntax_tree ast(std::move(p));
}