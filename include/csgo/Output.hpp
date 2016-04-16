#pragma once

#include "Variable.hpp"
#include "LValue.hpp"

namespace csgo
{
    class Output : public LValue, public Variable
    {
    public:
        // TODO: make these OpenGL types
        virtual void set(const std::vector<int>& data) = 0;
    };
}