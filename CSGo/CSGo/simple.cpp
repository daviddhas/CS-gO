#include "csgo.hpp"

using namespace csgo;

int main(int argc, char *argv[])
{
    int size = 256;
    std::vector<csgo::Float> vec1(size, 2);
    std::vector<csgo::Float> vec2(size, 3);

    ReadTexture<Float> in1(vec1);
    ReadTexture<Float> in2(vec2);

    csgo::WriteTexture<csgo::Float> out(size);

    csgo::Program p({ in1, in2 }, { &out });

    p.set({
        out = (in1 + in2) + in1,
    });

    p.finish();
    p.run();

    std::vector<csgo::Float> output = out.read();

    return 0;

}
