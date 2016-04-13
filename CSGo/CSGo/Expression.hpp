#pragma once

#include <string>
#include <memory>

namespace csgo
{
    /* Any evaluable code
    */
    class Expression
    {
    public:
        virtual std::string toCode() const = 0;
    };
}