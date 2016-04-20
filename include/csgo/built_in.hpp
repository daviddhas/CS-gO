#pragma once

#include <csgo/dsl/var.hpp>

namespace csgo {

    struct vec2 : dsl::var<glm::vec2> {
        using dsl::var<glm::vec2>::var;
    };
    struct vec3 : dsl::var<glm::vec3> {
        using dsl::var<glm::vec3>::var;
    };
    struct vec4 : dsl::var<glm::vec4> {
        using dsl::var<glm::vec4>::var;
    };

    template <typename P>
    struct image2d : dsl::layout_variable {
        image2d() : layout_variable({format_qualifier_for<P>::value}, dsl::type::image_2d) {}
        template <typename T>
        image2d(T initialization) : layout_variable(dsl::make_unique_expression(std::move(initialization)), { format_qualifier_for<P>::value }, dsl::type::image_2d) {}

        virtual void accept(dsl::expression_visitor& v) {
            v.visit(*this);
        }
    };

}
