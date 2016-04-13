#pragma once

#include <vector>
#include "Assignment.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "CodeGenerator.hpp"

namespace csgo
{
    class Compiler
    {
    public:
        /* Creates a compiled OpenGL compute shader from the CS Go
         * internal representation
        */
        static void compile(const std::vector<Assignment>& assignments,
            const std::vector<const Input*> inputs,
            const std::vector<Output*> outputs)
        {
            std::string code = CodeGenerator::generateCode(assignments, inputs, outputs);
            // TODO: finish this @JeanHeyd
        }
    };
}