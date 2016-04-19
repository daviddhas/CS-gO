#pragma once

#include <csgo/glsl/compiler.hpp>

namespace csgo {
    struct program {
        template<typename F>
        program(F&& f)
            : program(f, false) {
        }

        template<typename F>
        program(F&& f, bool makeContext) {
            dsl::ir_program p = dsl::make_ir_program(f);
            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(p, dsl::generate(p, gen), makeContext);
        }

        void run() {
            gl::UseProgram(handle);
            gl::DispatchCompute(1, 1, 1);
        }

    private:
        GLuint handle;
    };
}