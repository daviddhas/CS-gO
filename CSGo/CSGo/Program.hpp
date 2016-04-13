#pragma once

#include "Input.hpp"
#include "LValue.hpp"
#include <vector>
#include <algorithm>

namespace csgo
{
    class Program
    {
    public:
        Program(std::initializer_list<Input> inputs, std::initializer_list<LValue> outputs)
        {
            toPointers<Input>(inputs, _inputs);
            toPointers<LValue>(outputs, _outputs);
        }

        void run()
        {
        }

    private:
        std::vector<Input*> _inputs;
        std::vector<LValue*> _outputs;

        std::string makeProgram()
        {
            return "";
        }

        void fillOutputs()
        {
        }

        template<typename T>
        static void toPointers(const std::initializer_list<T>& in, const std::vector<T*>& out)
        {
            out.resize(in.size());
            std::transform(in.begin(), inp.end(), out.begin(), [](T i) { return &i; });
        }
    };
}