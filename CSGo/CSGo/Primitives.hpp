#pragma once

#include "LValue.hpp"

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

    private:
        float f;
    };
}