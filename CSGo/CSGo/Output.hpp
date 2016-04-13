#pragma once

#include "LValue.hpp"

namespace csgo
{
    template<typename T>
    class Output : public LValue
    {
    public:
        virtual T read() = 0;
        virtual void set(const T& val) = 0;
    };
}