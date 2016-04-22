#pragma once

#include <csgo/glsl/compiler.hpp>
#include <csgo/dsl/io_result.hpp>

namespace csgo {
    struct program {

        template<typename F>
        program(F&& f)
            : program(f, false)
        { }

        template<typename F>
        program(F&& f, bool makeContext)
            : ir(dsl::make_ir_program(std::forward<F>(f)))
        {
            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(ir, dsl::generate(ir, gen), makeContext);
        }

        template<typename... Args>
        dsl::io_result operator()(Args&&... args)
        {
            gl::UseProgram(handle);

            set_inputs(std::forward<Args>(args)...);
            std::vector<dsl::texture_data> outputs = set_outputs();

            gl::DispatchCompute(ir.main.wg.x, ir.main.wg.y, ir.main.wg.z);

            return dsl::io_result(outputs);
        }

    private:

#pragma region set inputs

        template<typename... Args>
        void set_inputs(Args&&...args)
        {
            if(sizeof...(args) != ir.inputs.size())
                throw std::runtime_error("Wrong number of inputs");

            set_inputs_impl(0, std::forward<Args>(args)...);
        }

        template<typename Arg, typename... Args>
        void set_inputs_impl(int n, Arg&& arg, Arg&& args)
        {
            set_input(arg.getTextureID(), n);
            set_inputs_impl(n + 1, std::forward<Args>(args)...);
        }

        void set_inputs_impl(int) // base case
        {}

        void set_input(GLuint textureID, int n)
        {
            GLuint loc = gl::GetUniformLocation(handle, ir.ast.symbols.find(ir.inputs[n].id).first.c_str());
            gl::Uniform1i(loc, n);
            gl::ActiveTexture(gl::TEXTURE0 + n);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
        }

#pragma endregion

        std::vector<dsl::texture_data> set_outputs()
        {
            std::vector<dsl::texture_data> outputs;
            for(auto& uniform : ir.outputs)
            {
                // TODO: set outputs
            }

            return outputs;
        }

        dsl::ir_program ir;
        GLuint handle;
    };
}