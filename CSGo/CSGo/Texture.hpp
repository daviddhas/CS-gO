#pragma once

#include <vector>

#include "Output.hpp"
#include "Input.hpp"

namespace csgo
{
    template <typename T>
    class Texture : public Expression
    {
    };

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