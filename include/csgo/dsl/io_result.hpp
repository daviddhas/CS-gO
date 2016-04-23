#pragma once

#include <vector>
#include <csgo/built_in_io.hpp>

namespace csgo {
    namespace dsl {

#pragma region converter

        // TODO: implement converters
        template<typename T>
        struct converter {};

        template<>
        struct converter<image2d_io<float>>
        {
            static image2d_io<float> convert(texture_data data)
            {
                return image2d_io<float>(data);
            }
        };

        template<>
        struct converter<image2d_io<int>>
        {
            static image2d_io<int> convert(texture_data data) {
                return image2d_io<int>(data);
            }
        };

#pragma endregion

        struct io_result {
            io_result(std::vector<texture_data> outputs)
                : outputs(std::move(outputs))
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
                return std::make_tuple(converter<Ts>::convert(outputs[Indices])...);
            }

            std::vector<texture_data> outputs;
        };
    }
}