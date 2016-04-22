#pragma once

#include <vector>
#include <csgo/built_in_io.hpp>

namespace csgo {
    namespace dsl {
        struct io_result {
            io_result(image2d_io<float> f)
                : image2d_float(std::move(image2d_float))
                , image2d_int(std::vector<int>(), 0)
                , t(IMAGE2D_FLOAT)
            { }

            io_result(image2d_io<int> image2d_float)
                : image2d_int(std::move(image2d_int))
                , image2d_float(std::vector<float>(), 0)
                , t(IMAGE2D_INT)
            { }
            operator image2d_io<float>()
            {
                if (t == IMAGE2D_INT)
                    throw std::runtime_error("Cannot cast to float");
                return image2d_float;
            }

            operator image2d_io<int>()
            {
                if (t == IMAGE2D_FLOAT)
                    throw std::runtime_error("Cannot cast to int");
                return image2d_int;
            }

        private:
            enum result_type { IMAGE2D_FLOAT, IMAGE2D_INT };

            result_type t;

            image2d_io<float> image2d_float;
            image2d_io<int> image2d_int;
        };
    }
}