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
            const std::vector<std::shared_ptr<Input>> inputs,
            const std::vector<std::shared_ptr<Output>> outputs,
            int x, int y, int z)
        {
            std::string code = CodeGenerator::generateCode(assignments, inputs, outputs, x, y, z);
            // TODO: finish this @JeanHeyd
        }
    };
}