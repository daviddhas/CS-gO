#pragma once

#include <csgo/glsl/compiler.hpp>

namespace csgo {
    struct program {
        template<typename F>
        program(F&& f)
            : program(f, false) {
        }

        template<typename F>
        program(F&& f, bool makeContext) : irp(dsl::make_ir_program(f)) {
            glsl::glsl_generator gen;
		  std::string code = dsl::generate(irp, gen);
            handle = glsl::compiler::compile(irp, code, makeContext);
        }

        void run() {
            gl::UseProgram(handle);
		  // Use the workgroups inferred from the entry_point program
		  workgroup& wg = irp.main.wg;
		  gl::DispatchCompute(wg.x, wg.y, wg.z);
        }

    private:
	    dsl::ir_program irp;
	    workgroup wg;
	    GLuint handle;
    };
}