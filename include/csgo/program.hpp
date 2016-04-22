#pragma once

#include <csgo/glsl/compiler.hpp>
#include <csgo/dsl/io_result.hpp>

namespace csgo {
    struct program {
        template<typename F>
        program(F&& f)
            : program(f, false) {
        }

        template<typename F>
        program(F&& f, bool makeContext) {
            dsl::ir_program p = dsl::make_ir_program(std::forward<F>(f));
            wg = p.main.wg;
            p.outputs.size();

            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(p, dsl::generate(p, gen), makeContext);
        }

        template<typename... Args>
        std::vector<dsl::io_result> operator()(Args... args) {
            gl::UseProgram(handle);
            gl::DispatchCompute(wg.x, wg.y, wg.z);

            return std::vector<dsl::io_result>();
        }

    private:
	    workgroup wg;
        GLuint handle;
    };
}