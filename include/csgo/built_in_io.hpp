#pragma once

#include <csgo/gl_detail/gl.hpp>
#include <vector>
#include <type_traits>

namespace csgo {
    template <typename P>
    struct image2d_io {

        template<typename std::enable_if_t<std::is_same<P, float>::value || std::is_same<P, int>::value, int> = 0>
        image2d_io(const std::vector<P>& data, int width)
            : height((int)data.size() / width)
            , width(width)
        {
            gl::GenTextures(1, &textureID);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::TexImage2D(gl::TEXTURE_2D, 0, getInternalFormat(), width, height, 0, getFormat(), getType(), data.data());
        }

        std::vector<P> read()
        {
            std::vector<P> data(height * width);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::GetTexImage(gl::TEXTURE_2D, 0, getFormat(), getType(), data.data());
            return data;
        }

        GLuint getTextureID()
        {
            return textureID;
        }

    private:

        int height;
        int width;
        GLuint textureID;

#pragma region gl type getters

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLenum getFormat()
        {
            return gl::RED;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getFormat()
        {
            return gl::RED_INTEGER;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLint getInternalFormat()
        {
            return gl::R32F;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getInternalFormat()
        {
            return gl::R32I;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        GLenum getType()
        {
            return gl::FLOAT;
        }

        template<typename U = P, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        GLenum getType()
        {
            return gl::INT;
        }

#pragma endregion

    };

}
