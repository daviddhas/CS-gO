#pragma once

#include <csgo/gl_detail/gl.hpp>
#include <vector>
#include <type_traits>

namespace csgo {

    namespace dsl {
        struct texture_data {
            GLuint id, width, height;
        };
    }

    template <typename P>
    struct image2d_io {

        template<typename std::enable_if_t<std::is_same<P, float>::value || std::is_same<P, int>::value, int> = 0>
        image2d_io(const std::vector<P>& vals, int width)
        {
            int height = (int)vals.size() / width;

            GLuint textureID;
            gl::GenTextures(1, &textureID);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::TexImage2D(gl::TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), vals.data());

            data = dsl::texture_data{ textureID, (GLuint)width, (GLuint)height };
        }

        template<typename std::enable_if_t<std::is_same<P, float>::value || std::is_same<P, int>::value, int> = 0>
        image2d_io(dsl::texture_data data)
            : data(data)
        { }

        std::vector<P> read() const
        {
            std::vector<P> vals(data.height * data.width);
            gl::BindTexture(gl::TEXTURE_2D, data.id);
            gl::GetTexImage(gl::TEXTURE_2D, 0, getFormat(), getType(), vals.data());
            return vals;
        }

        GLuint getTextureID() const
        {
            return data.id;
        }

    private:

        dsl::texture_data data;

#pragma region gl type getters

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLenum getFormat() const
        {
            return gl::RED;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getFormat() const
        {
            return gl::RED_INTEGER;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLint getInternalFormat() const
        {
            return gl::R32F;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getInternalFormat() const
        {
            return gl::R32I;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLenum getType() const
        {
            return gl::FLOAT;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getType() const
        {
            return gl::INT;
        }

#pragma endregion

    };

}
