#pragma once

#include "LValue.hpp"

#include <algorithm>

namespace csgo
{
    class Float : public LValue
    {
    public:
        Float()
            : f(0)
        { }

        Float(float f)
            : f(f)
        { }

        operator float() const
        {
            return f;
        }

        static std::vector<Float> fromBytes(const std::vector<int>& data)
        {
            std::vector<Float> fs(data.size());
            std::transform(data.begin(), data.end(), fs.begin(), [](int i) { return (float)i; });
            return fs;
        }


    private:
        float f;
    };
}