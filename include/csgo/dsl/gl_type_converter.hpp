#pragma once

#include <csgo/gl/gl.hpp>

namespace csgo { namespace dsl {
    struct gl_type_converter
    {
        // formats
        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLenum get_format() { return gl::RED; }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLenum get_format() { return gl::RED_INTEGER; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec2>::value, int> = 0>
        static GLenum get_format() { return gl::RG; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec3>::value, int> = 0>
        static GLenum get_format() { return gl::RGB; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec4>::value, int> = 0>
        static GLenum get_format() { return gl::RGBA; }


        // internal formats
        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLint get_internal_format() { return gl::R32F; }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLint get_internal_format() { return gl::R32I; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec2>::value, int> = 0>
        static GLint get_internal_format() { return gl::RG32F; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec3>::value, int> = 0>
        static GLint get_internal_format() { return gl::RGBA32F; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec4>::value, int> = 0>
        static GLint get_internal_format() { return gl::RGBA32F; }


        // types
        template<typename U, typename std::enable_if_t<std::is_same<U, float>::value, int> = 0>
        static GLenum get_type() { return gl::FLOAT; }

        template<typename U, typename std::enable_if_t<std::is_same<U, int>::value, int> = 0>
        static GLenum get_type() { return gl::INT; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec2>::value, int> = 0>
        static GLenum get_type() { return gl::FLOAT; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec3>::value, int> = 0>
        static GLenum get_type() { return gl::FLOAT; }

        template<typename U, typename std::enable_if_t<std::is_same<U, glm::vec4>::value, int> = 0>
        static GLenum get_type() { return gl::FLOAT; }
    };


    // invert format_qualifier_for

    struct from_qualifier_to
    {
        static GLenum gl_internal_format(format_qualifier f)
        {
            switch (f)
            {
            case format_qualifier::r8:
                return gl::R8UI;
            case format_qualifier::r32f:
                return gl::R32F;
            case format_qualifier::rg32f:
                return gl::RG32F;
            case format_qualifier::rgba32f:
                return gl::RGBA32F;
            case format_qualifier::r32i:
                return gl::R32I;
            case format_qualifier::rg32i:
                return gl::RG32I;
            case format_qualifier::rgba32i:
                return gl::RGBA32I;
            case format_qualifier::r32ui:
                return gl::R32UI;
            case format_qualifier::rg32ui:
                return gl::RG32UI;
            case format_qualifier::rgba32ui:
                return gl::RGBA32UI;
            default:
                throw std::runtime_error("Invalid format qualifier");
            }
        }

        static GLenum gl_format(format_qualifier f)
        {
            switch (f)
            {
            case format_qualifier::r8:
                return gl::RED_INTEGER;
            case format_qualifier::r32f:
                return gl::RED;
            case format_qualifier::rg32f:
                return gl::RG;
            case format_qualifier::rgba32f:
                return gl::RGBA;

            case format_qualifier::r32i:
            case format_qualifier::r32ui:
                return gl::RED_INTEGER;

            case format_qualifier::rg32i:
            case format_qualifier::rg32ui:
                return gl::RG_INTEGER;

            case format_qualifier::rgba32i:
            case format_qualifier::rgba32ui:
                return gl::RGBA_INTEGER;

            default:
                throw std::runtime_error("Invalid format qualifier");
            }
        }

        static GLenum gl_type(format_qualifier f)
        {
            switch (f)
            {
            case format_qualifier::r8:
                return gl::BYTE;

            case format_qualifier::r32f:
            case format_qualifier::rg32f:
            case format_qualifier::rgba32f:
                return gl::FLOAT;

            case format_qualifier::r32i:
            case format_qualifier::rg32i:
            case format_qualifier::rgba32i:
                return gl::INT;

            case format_qualifier::r32ui:
            case format_qualifier::rg32ui:
            case format_qualifier::rgba32ui:
                return gl::UNSIGNED_INT;

            default:
                throw std::runtime_error("Invalid format qualifier");
            }
        }
    };
} }