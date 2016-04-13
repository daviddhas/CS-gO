#pragma once

#include "Input.hpp"
#include "Output.hpp"
#include <string>
#include <vector>

namespace csgo
{
    class CodeGenerator
    {
    public:

        /* Generates a string of GLSL code from the CS Go internal representation
        */
        static std::string generateCode(const std::vector<Assignment>& assignments,
            const std::vector<const Input*> inputs,
            const std::vector<Output*> outputs)
        {
            // TODO: finish this @Jett
            std::string code;
            return code;
        }
    };
}