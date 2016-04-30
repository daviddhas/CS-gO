#pragma once

#include <csgo/gl/gl_type_converter.hpp>
#include <vector>
#include <type_traits>

namespace csgo {

     struct texture_data {
          GLuint id, width, height;
     };

    template <typename P>
    struct image2d_io {

        typedef P type;

        typedef std::integral_constant<bool,
            std::is_same<P, float>::value
            || std::is_same<P, int>::value
            || std::is_same<P, glm::vec2>::value
            || std::is_same<P, glm::vec3>::value
            || std::is_same<P, glm::vec4>::value
            > is_valid_t;

	   static_assert(is_valid_t::value, "Unsupported image2d_io type");

        image2d_io(const std::vector<P>& vals, int width)
        {
            int height = (int)vals.size() / width;

            GLuint textureID;
            gl::GenTextures(1, &textureID);
            gl::BindTexture(gl::TEXTURE_2D, textureID);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
            gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
            gl::TexImage2D(gl::TEXTURE_2D, 0, gld::internal_format_of<P>::value, width, height, 0,
			  gld::format_of<P>::value, gld::gl_type_of<P>::value, vals.data());

            data = texture_data{ textureID, (GLuint)width, (GLuint)height };
        }

        image2d_io(texture_data data)
            : data(data)
        { }

        std::vector<P> read() const
        {
            std::vector<P> vals(data.height * data.width);
            gl::BindTexture(gl::TEXTURE_2D, data.id);
            gl::GetTexImage(gl::TEXTURE_2D, 0, gld::format_of<P>::value,
                gld::gl_type_of<P>::value, vals.data());
            return vals;
        }

        GLuint get_texture_ID() const
        {
            return data.id;
        }

    private:

        texture_data data;
    };

}
