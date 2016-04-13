#pragma once

#include "Input.hpp"
#include "Output.hpp"
#include "ast.hpp"
#include <string>
#include <vector>

namespace csgo
{
    class CodeGenerator
    {
    public:

	    CodeGenerator() {}

        /* Generates a string of GLSL code from the CS Go internal representation
        */
        static std::string generateCode(abstract_syntax_tree& ast)
        {
            // TODO: finish this @Jett
            std::string code;
            return code;
        }
    };
}