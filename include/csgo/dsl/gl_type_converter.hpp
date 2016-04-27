#pragma once

#include <csgo/gl/gl.hpp>

namespace csgo { namespace dsl {
    struct gl_type_converter
    {
        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLenum getFormat()
        {
            return gl::RED;
        }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLenum getFormat()
        {
            return gl::RED_INTEGER;
        }

        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLint getInternalFormat()
        {
            return gl::R32F;
        }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLenum getInternalFormat()
        {
            return gl::R32I;
        }

        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLenum getType()
        {
            return gl::FLOAT;
        }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLenum getType()
        {
            return gl::INT;
        }
    };
} }