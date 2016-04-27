#pragma once

#include <vector>
#include <type_traits>

#include <csgo/dsl/gl_type_converter.hpp>

namespace csgo {

    namespace dsl {
        struct texture_data {
            GLuint id, width, height;
        };
    }

    template <typename P>
    struct image2d_io {

        typedef P type;

        template<typename std::enable_if_t<std::is_same<P, float>::value || std::is_same<P, int>::value, int> = 0>
        image2d_io(const std::vector<P>& vals, int width)
        {
            int height = (int)vals.size() / width;

            GLuint textureID;
            gl::GenTextures(1, &textureID);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
            gl::TexImage2D(gl::TEXTURE_2D, 0, dsl::gl_type_converter::get_internal_format<P>(), width, height, 0,
                dsl::gl_type_converter::get_format<P>(), dsl::gl_type_converter::get_type<P>(), vals.data());

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
            gl::GetTexImage(gl::TEXTURE_2D, 0, dsl::gl_type_converter::get_format<P>(),
                dsl::gl_type_converter::get_type<P>(), vals.data());
            return vals;
        }

        GLuint get_texture_ID() const
        {
            return data.id;
        }

    private:

        dsl::texture_data data;
    };

}
