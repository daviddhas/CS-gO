#pragma once

#include <csgo/glsl/compiler.hpp>
#include <csgo/dsl/io_result.hpp>

namespace csgo {
    struct program {

        typedef std::vector<std::vector<GLuint>> size_list_t;

        template<typename F>
        program(F&& f, size_list_t sizes)
            : program(std::forward<F>(f), std::move(sizes), false)
        { }

        template<typename F>
        program(F&& f, const size_list_t& sizes, bool makeContext)
            : ir(dsl::make_ir_program(std::forward<F>(f)))
            , sizes(sizes)
        {
            if (sizes.size() != ir.outputs.size())
                throw std::runtime_error("Incorrect number of output sizes");

            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(ir, dsl::generate(ir, gen), makeContext);
        }

        template<typename... Args>
        dsl::io_result operator()(Args&&... args)
        {
            if(sizeof...(args) != ir.inputs.size())
                throw std::runtime_error("Incorrect number of inputs");

            gl::UseProgram(handle);

            set_inputs(std::forward<Args>(args)...);
            std::vector<dsl::texture_data> outputs = set_outputs();

            gl::DispatchCompute(ir.main.wg.x, ir.main.wg.y, ir.main.wg.z);

            return dsl::io_result(outputs);
        }

    private:

#pragma region set inputs/outputs

        template<typename... Args>
        void set_inputs(Args&&... args)
        {
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

        std::vector<dsl::texture_data> set_outputs()
        {
            GLuint size = (GLuint)ir.outputs.size();
            std::vector<dsl::texture_data> outputs(size);

            std::vector<GLuint> handles(size);
            gl::GenTextures(size, handles.data());

            GLuint numInputs = (GLuint)ir.inputs.size();
            for (GLuint i = 0; i < size; i++)
            {
                gl::ActiveTexture(gl::TEXTURE0 + numInputs + i);
                gl::BindTexture(gl::TEXTURE_2D, handles[i]);
                
                // get this type from semantic analysis?
                gl::TexImage2D(gl::TEXTURE_2D, 0, gl::R32F, sizes[i][0], sizes[i][1], 0, gl::RED, gl::FLOAT, nullptr);
                GLint loc = gl::GetUniformLocation(handle, ir.ast.symbols.find(ir.outputs[i].id).first.c_str());
                gl::Uniform1i(loc, numInputs + i);
                outputs[i] = dsl::texture_data{ handles[i], sizes[i][0], sizes[i][1] };
            }

            return outputs;
        }

#pragma endregion

        dsl::ir_program ir;
        GLuint handle;
        size_list_t sizes;
    };
}