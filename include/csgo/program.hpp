#pragma once

#include <csgo/glsl/compiler.hpp>
#include <csgo/built_in_io.hpp>

namespace csgo {
    struct program {
        template<typename F>
        program(F&& f)
            : program(f, false) {
        }

        template<typename F>
        program(F&& f, bool makeContext) {
            dsl::ir_program p = dsl::make_ir_program(f);
		  // the ir_program's main has the workgroup count on it
		  wg = p.main.wg; // save it
            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(p, dsl::generate(p, gen), makeContext);
        }

        void run() {
            gl::UseProgram(handle);
		  // Use the workgroups inferred from the entry_point program
            gl::DispatchCompute(wg.x, wg.y, wg.z);
        }

    private:
	    workgroup wg;
        GLuint handle;
    };
}