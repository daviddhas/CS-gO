#pragma once

#include "Input.hpp"
#include "Output.hpp"
#include "ProgramExceptions.hpp"

#include <vector>
#include <algorithm>

namespace csgo
{
    class Program
    {
    public:

        Program(std::initializer_list<Input> inputs, std::initializer_list<Output*> outputs)
        {
            for (const Input& i : inputs)
                _inputs.push_back(&i);

            for (Output *o : outputs)
                _outputs.push_back(o);

        }

        void add(std::initializer_list<Assignment> assignments)
        {
            if (!_finished)
                for (const Assignment& a : assignments)
                    _assignments.push_back(a);
            else
                throw FinishedProgramException();
        }

        void finish()
        {
            _finished = true;
            _program = makeProgram();
        }

        void run()
        {
            if (_finished);
            else
                throw UnfinishedProgramException();
        }

    private:
        bool _finished = false;
        std::string _program;

        std::vector<Assignment> _assignments;

        std::vector<const Input*> _inputs;
        std::vector<LValue*> _outputs;

        std::string makeProgram()
        {
            return "";
        }
    };
}