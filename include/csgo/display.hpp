#pragma once

#include <csgo/built_in_io.hpp>
#include <csgo/glsl/compiler.hpp>

namespace csgo
{
    struct display
    {
        template<typename T>
        static void image(const image2d_io<T>& input)
        {
            glsl::compiler::make_context();

            GLuint vertexArrayID;
            gl::GenVertexArrays(1, &vertexArrayID);
            gl::BindVertexArray(vertexArrayID);

            GLFWwindow *window = glfwGetCurrentContext();

            GLuint handle = gl::CreateProgram();
            GLuint frag = gl::CreateShader(gl::FRAGMENT_SHADER);
            glsl::compiler::compile(handle, frag, getFragShader());
            GLuint vert = gl::CreateShader(gl::VERTEX_SHADER);
            glsl::compiler::compile(handle, vert, getVertShader());

            gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
            gl::UseProgram(handle);

            gl::EnableVertexAttribArray(0);
            std::vector<GLfloat> quad = getQuad();
            GLuint positions;
            gl::GenBuffers(1, &positions);
            gl::BindBuffer(gl::ARRAY_BUFFER, positions);
            gl::BufferData(gl::ARRAY_BUFFER, (GLint)quad.size() * sizeof(GLfloat), quad.data(), gl::STATIC_DRAW);
            gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, nullptr);

            gl::EnableVertexAttribArray(1);
            std::vector<GLfloat> quad_uvs = getUVs();
            GLuint uvs;
            gl::GenBuffers(1, &uvs);
            gl::BindBuffer(gl::ARRAY_BUFFER, uvs);
            gl::BufferData(gl::ARRAY_BUFFER, (GLint)quad_uvs.size() * sizeof(GLfloat), quad_uvs.data(), gl::STATIC_DRAW);
            gl::VertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE_, 0, nullptr);

            gl::ActiveTexture(gl::TEXTURE0);
            gl::BindTexture(gl::TEXTURE_2D, input.get_texture_ID());
            gl::Uniform1i(gl::GetUniformLocation(handle, "tex"), 0);

            gl::DrawArrays(gl::TRIANGLE_STRIP, 0, (GLint)quad.size());

            gl::DisableVertexAttribArray(0);
            gl::DisableVertexAttribArray(1);

            glfwSwapBuffers(window);

            gl::DeleteShader(frag);
            gl::DeleteShader(vert);
            gl::DeleteProgram(handle);
        }

    private:

        static std::string getVertShader() {
            return
                "#version 450 core\n"
                "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
                "layout(location = 1) in vec2 vertex_uv;\n"
                "out vec2 uv;\n"
                "void main() {\n"
                "gl_Position.xyz = vertexPosition_modelspace;\n"
                "gl_Position.w = 1.0;\n"
                "uv = vertex_uv;\n"
                "}\n"
                ;
        }

        static std::string getFragShader() {
            return
                "#version 450 core\n"
                "in vec2 uv;\n"
                "uniform sampler2D tex;\n"
                "void main() {\n"
                "gl_FragColor = texture(tex, uv);\n"
                "}\n"
                ;
        }

        static std::vector<GLfloat> getQuad() {
            return {
                -1.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
            };
        }

        static std::vector<GLfloat> getUVs() {
            return {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
            };
        }
    };
}