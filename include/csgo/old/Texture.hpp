#pragma once

#include <vector>

#include "Output.hpp"
#include "Input.hpp"

namespace csgo
{
    /* A templated container of 1, 2, or 3 dimensions
    */
    template <typename T>
    class Texture
    {
    };

    /* A texture that can be used as input to a program
    */
    template <typename T>
    class ReadTexture : public Texture<T>, public Input, public Expression
    {
    public:
        ReadTexture(const std::vector<T>& v)
            : v(v)
        { }

        std::string getType() const override
        {
            return "image2D";
        }

        std::string toCode() const override
        {
            return Input::name + "[ivec2(gl_GlobalInvocationID.xy)]";
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

        std::string toCode() const override
        {
            return name + "[ivec2(gl_GlobalInvocationID.xy)]";
        }

        void set(const std::vector<int>& val)
        {
            output = T::fromBytes(val);
        }

        std::string getType() const override
        {
            return "image2D";
        }

    private:
        int sizex, sizey, sizez;

        std::vector<T> output;
    };
}