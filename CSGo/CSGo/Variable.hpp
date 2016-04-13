#pragma once

#include <string>

namespace csgo
{
    class Variable
    {
    public:
        std::string name;

        virtual std::string getType() const = 0;
    };
}