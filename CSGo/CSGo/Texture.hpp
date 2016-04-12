#pragma once

#include <vector>

#include "LValue.hpp"

namespace csgo
{
    template <class T>
    class Texture : public Expression
    {
    };

    template <class T>
    class ReadTexture : public Texture<T>
    {
    public:
        ReadTexture(const std::vector<T>& v)
            : v(v)
        { }

    private:
        std::vector <T> v;
    };

    template <class T>
    class WriteTexture : public Texture<T>, public LValue
    {
    public:
        WriteTexture(int size)
            : sizex(size)
            , sizey(1)
            , sizez(1)
        { }

        Assignment operator=(const Expression& rhs)
        {
            return LValue::operator=(rhs);
        }

    private:
        int sizex, sizey, sizez;
    };
}