#include "csgo.hpp"

using namespace csgo;

int main(int argc, char *argv[])
{
	// graphics_device initializes all of the
	// OpenGL stuff.
	graphics_device gd;
	int size = 256;
	std::vector<csgo::Float> vec1(size, 2);
	std::vector<csgo::Float> vec2(size, 3);

	ReadTexture<Float> in1(vec1);
	ReadTexture<Float> in2(vec2);

	csgo::WriteTexture<csgo::Float> out(size);

	csgo::Program program({ in1, in2 }, { out });

	out = (in1 + in2) + in1;

	program.run();

	std::vector<csgo::Float> output = out.read();

    return 0;

}
