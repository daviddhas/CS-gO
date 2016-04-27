#pragma once

#include <csgo/glsl/compiler.hpp>
#include <csgo/dsl/io_result.hpp>

namespace csgo {
    struct program {

        typedef std::vector<std::vector<GLuint>> size_list_t;

        template<typename F>
        program(F&& f, size_list_t sizes)
            : program(std::forward<F>(f), std::move(sizes), false)
        {
            gl::Enable(gl::TEXTURE_2D);
        }

        template<typename F>
        program(F&& f, const size_list_t& sizes, bool makeContext)
            : ir(dsl::make_ir_program(std::forward<F>(f)))
            , sizes(sizes)
        {
            if (sizes.size() != ir.main.output_variables.size())
                throw std::runtime_error("Incorrect number of output sizes");

            glsl::glsl_generator gen;
            handle = glsl::compiler::compile(ir, dsl::generate(ir, gen), makeContext);
        }

        template<typename... Args>
        dsl::io_result operator()(Args&&... args)
        {
            if(sizeof...(args) != ir.main.input_variables.size())
                throw std::runtime_error("Incorrect number of inputs");

            gl::UseProgram(handle);
            set_inputs(std::forward<Args>(args)...);
            std::vector<dsl::texture_data> outputs = set_outputs();

            gl::ValidateProgram(handle);
            char *log = new char[1024];
            gl::GetProgramInfoLog(handle, 1023, nullptr, log);
            std::cout << "the log: " << log << std::endl;

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
        void set_inputs_impl(int n, Arg&& arg, Args&&... args)
        {
            set_input(arg.getTextureID(), n);
            set_inputs_impl(n + 1, std::forward<Args>(args)...);
        }

        void set_inputs_impl(int) // base case
        {}

        void set_input(GLuint textureID, int n)
        {
            // TODO: add int support
		  const std::string& name = ir.ast.input_name(n);
            GLuint loc = gl::GetUniformLocation(handle, name.c_str());
            gl::ActiveTexture(gl::TEXTURE0 + n);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::BindImageTexture(loc, textureID, 0, false, 0, gl::READ_ONLY, gl::R32F);
            gl::Uniform1i(loc, n);
        }

        std::vector<dsl::texture_data> set_outputs()
        {
            GLuint size = (GLuint)ir.main.output_variables.size();
            std::vector<dsl::texture_data> outputs(size);

            std::vector<GLuint> handles(size);
            gl::GenTextures(size, handles.data());

            GLuint numInputs = (GLuint)ir.main.input_variables.size();
            for (GLuint i = 0; i < size; i++)
            {
                // TODO: add int support
                gl::ActiveTexture(gl::TEXTURE0 + numInputs + i);
                gl::BindTexture(gl::TEXTURE_2D, handles[i]);
                gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
                gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
                gl::TexImage2D(gl::TEXTURE_2D, 0, gl::R32F, sizes[i][0], sizes[i][1], 0, gl::RED, gl::FLOAT, nullptr);

			 const std::string& outputname = ir.ast.output_name(i);
                GLint loc = gl::GetUniformLocation(handle, outputname.c_str());
                gl::BindImageTexture(loc, handles[i], 0, false, 0, gl::WRITE_ONLY, gl::R32F);
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