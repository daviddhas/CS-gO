#include <iostream>
#include "csgo.hpp"

int main(int argc, char *argv[])
{

int size = 256;
std::vector<Float> vec1(size);
std::vector<Float> vec2(size);

//std::vector<csgo::Float> vec1(size, 2f);
//std::vector<csgo::Float> vec2(size, 3f);

ReadTex<Float>in1(vec1);
ReadTex<Float>in2(vec2);
//csgo::WriteTex<csgo::Float> out(size);

//csgo::Program program(in1, in2, out);
//out = (in1 + in2)/2;
//program.run();

//std::vector<csgo::Float> output = out.read();

return 0;

}
