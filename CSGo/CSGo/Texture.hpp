#pragma once

#include <vector>

#include "Output.hpp"
#include "Input.hpp"

namespace csgo
{
    /* A templated container of 1, 2, or 3 dimensions
    */
    template <typename T>
    class Texture : public Expression
    {
    };

    /* A texture that can be used as input to a program
    */
    template <typename T>
    class ReadTexture : public Texture<T>, public Input
    {
    public:
        ReadTexture(const std::vector<T>& v)
            : v(v)
        { }

        int opengltype() override
        {
            return 0;
        }

    private:
        std::vector <T> v;
    };

    /* A texture that can be used as output to a program
    */
    template <typename T>
    class WriteTexture : public Texture<T>, public Output
    {
    public:
        WriteTexture(int size)
            : sizex(size)
            , sizey(1)
            , sizez(1)
            , output(size)
        { }

        std::vector<T> read()
        {
            return output;
        }

        Assignment operator=(const Expression& rhs)
        {
            return LValue::operator=(rhs);
        }

        void set(const std::vector<int>& val)
        {
            output = T::fromBytes(val);
        }

        int opengltype() override
        {
            return 1;
        }

    private:
        int sizex, sizey, sizez;

        std::vector<T> output;
    };
}