#include "main.hpp"
#include <csgo/csgo.hpp>

#include <iostream>

void simple() {
    int size = 256;
    std::vector<csgo::Float> vec1(size, 2);
    std::vector<csgo::Float> vec2(size, 3);

    auto in1 = std::make_shared<csgo::ReadTexture<csgo::Float>>(vec1);
    auto in2 = std::make_shared<csgo::ReadTexture<csgo::Float>>(vec2);

    auto out = std::make_shared<csgo::WriteTexture<csgo::Float>>(size);

    csgo::Program p({ in1, in2 }, { out });

    p.set(out, (in1 + in2) + in1);

    p.finish();
    p.run();

    std::vector<csgo::Float> output = out->read();
}


