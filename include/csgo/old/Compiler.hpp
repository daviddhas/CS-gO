#pragma once

#include <vector>
#include "Assignment.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "CodeGenerator.hpp"
#include "compute_program.hpp"

namespace csgo
{
        class Compiler {
        private:
            // Need a point of initialization for the graphics device: might as well go with a (static?)
            // instance of the compiler until we sort out ordering issues
            graphics_device gd;

        public:
            /* Creates a compiled OpenGL compute shader from the CS Go
             * internal representation
            */
            compute_program compile(const std::vector<Assignment>& assignments,
                const std::vector<std::shared_ptr<Input>> inputs,
                const std::vector<std::shared_ptr<Output>> outputs,
                int x, int y, int z) {
                std::string code = CodeGenerator::generateCode(assignments, inputs, outputs, x, y, z);
                shader_source src(shader_stage::compute, code, "main");
                return compute_program(std::move(src), x, y, z);
            }
        };
    }
}