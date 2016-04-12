#pragma once

#include "LValue.hpp"

namespace csgo
{
    class Float : public LValue
    {
    public:
        Float(float f)
            : f(f)
        { }

        operator float() const
        {
            return f;
        }

    private:
        float f;
    };
}