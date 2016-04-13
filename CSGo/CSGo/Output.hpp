#pragma once

#include "LValue.hpp"

namespace csgo
{
    class Output : public LValue
    {
    public:
        // TODO: make this OpenGL types
        virtual void set(const std::vector<int>& data) = 0;
        virtual int opengltype() = 0;
    };
}