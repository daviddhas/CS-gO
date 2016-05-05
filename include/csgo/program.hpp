#pragma once

#include <csgo/compiler.hpp>
#include <csgo/io_result.hpp>

namespace csgo {
    struct program {

        typedef std::vector<std::vector<GLuint>> size_list_t;

        template<typename F>
        program(F&& f)
        : ir(dsl::make_ir_program(std::forward<F>(f))) {
            glsl::compute_generator gen;
            handle = glsl::compiler::compile(ir, dsl::generate(ir, gen));
	   }

        template<typename... Args>
	   io_result operator()(Args&&... args)
	   {
		   if (sizeof...(args) != ir.main.input_variables.size())
			   throw std::runtime_error("Incorrect number of inputs");

		   gl::UseProgram(handle);
		   set_inputs(std::forward<Args>(args)...);
		   std::vector<texture_data> outputs = set_outputs();

		   gl::ValidateProgram(handle);
		   //char log[1024];
		   //gl::GetProgramInfoLog(handle, 1023, nullptr, log);
		   //std::cout << "Validation log: " << log << std::endl;

		   gl::DispatchCompute(ir.main.wg.x, ir.main.wg.y, ir.main.wg.z);

		   return io_result(outputs);
	   }

	   void output_sizes(size_list_t o) {
		   sizes = std::move(o);
		   if (sizes.size() != ir.main.output_variables.size())
			   throw std::runtime_error("Incorrect number of output sizes");
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
		  const std::string& name = ir.ast.input_name(n);
            set_input(std::forward<Arg>(arg), n, name);
            set_inputs_impl(n + 1, std::forward<Args>(args)...);
        }

        void set_inputs_impl(int) // base case
        {}

	   template<typename T, meta::enable<dsl::is_primitive<T>> = meta::enabler>
	   void set_input(T&& arg, int n, const std::string& name)
	   {
		   GLuint loc = gl::GetUniformLocation(handle, name.c_str());
		   gl::Uniform4fv(loc, sizeof(T) / sizeof(float));
	   }

	   template<typename T, meta::disable<dsl::is_primitive<T>> = meta::enabler>
        void set_input(T&& arg, int n, const std::string& name)
        {
		   // Assumed to be an image type.
		   GLuint textureid = arg.get_texture_ID();
            GLuint loc = gl::GetUniformLocation(handle, name.c_str());
            gl::ActiveTexture(gl::TEXTURE0 + n);
            gl::BindTexture(gl::TEXTURE_2D, textureid);
            gl::BindImageTexture(loc, textureid, 0, false, 0, gl::READ_ONLY, gld::internal_format_of<meta::unqualified_t<T>>());
            gl::Uniform1i(loc, n);
        }

        std::vector<texture_data> set_outputs()
        {
            GLuint size = (GLuint)ir.main.output_variables.size();
            std::vector<texture_data> outputs(size);

            std::vector<GLuint> handles(size);
            gl::GenTextures(size, handles.data());

            GLuint numInputs = (GLuint)ir.main.input_variables.size();
            for (GLuint i = 0; i < size; i++)
            {
			  const dsl::layout_variable& outputvar = *ir.main.output_variables[i];
			  const std::string& outputname = ir.ast.output_name(i);
                GLenum format = gld::from_qualifier_to::gl_format(outputvar.layout.format);
                GLenum internal_format = gld::from_qualifier_to::gl_internal_format(outputvar.layout.format);
                GLenum type = gld::from_qualifier_to::gl_type(outputvar.layout.format);

                gl::ActiveTexture(gl::TEXTURE0 + numInputs + i);
                gl::BindTexture(gl::TEXTURE_2D, handles[i]);
                gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
                gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
                gl::TexImage2D(gl::TEXTURE_2D, 0, internal_format, sizes[i][0], sizes[i][1], 0, format, type, nullptr);


                GLint loc = gl::GetUniformLocation(handle, outputname.c_str());
                gl::BindImageTexture(loc, handles[i], 0, false, 0, gl::WRITE_ONLY, internal_format);
                gl::Uniform1i(loc, numInputs + i);
                outputs[i] = texture_data{ handles[i], sizes[i][0], sizes[i][1] };
            }

            return outputs;
        }

#pragma endregion

        dsl::ir_program ir;
        GLuint handle;
        size_list_t sizes;
    };
}
