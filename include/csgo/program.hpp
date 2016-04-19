#pragma once

#include <csgo/glsl/compiler.hpp>

namespace csgo {
    struct program {
        template<typename F>
        program(F&& f)
        {
            dsl::ir_program p = dsl::make_ir_program(f);
            glsl::glsl_generator gen;
            std::string code = dsl::generate(p, gen);
        }
    };
}