#pragma once

#include <vector>
#include <csgo/built_in_io.hpp>

namespace csgo {
    namespace dsl {

#pragma region converter

        struct texture_data
        { };

        // TODO: implement converters
        template<typename T>
        struct converter {};

        template<>
        struct converter<image2d_io<float>>
        {
            static image2d_io<float> convert(texture_data data)
            {
                return image2d_io<float>(std::vector<float>(), 0);
            }
        };

        template<>
        struct converter<image2d_io<int>>
        {
            static image2d_io<float> convert(texture_data data) {
                return image2d_io<float>(std::vector<float>(), 0);
            }
        };

#pragma endregion

        struct io_result {
            io_result(std::vector<texture_data> output)
                : output(std::move(output))
            { }

            template<typename... Ts>
            operator std::tuple<Ts...>()
            {
                return toTuple<Ts...>(std::make_index_sequence<sizeof...(Ts)>());
            }


        private:
            template<typename... Ts, std::size_t... Indices>
            std::tuple<Ts...> toTuple(std::index_sequence<Indices...>)
            {
                return std::make_tuple(converter<Ts>::convert(output[Indices])...);
            }

            std::vector<texture_data> output;
        };
    }
}