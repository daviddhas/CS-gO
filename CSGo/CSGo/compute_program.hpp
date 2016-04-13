#pragma once

#include "ProgramExceptions.hpp"
#include "Compiler.hpp"

#include <vector>
#include <algorithm>

namespace csgo
{
    class program
    {
    public:

        program(std::string code, program_ast& ast)
        {
            for (const Input& i : inputs)
                _inputs.push_back(&i);

            for (Output *o : outputs)
                _outputs.push_back(o);

        }

        /* Adds the list of assignments to the prorgam
        */
        void add(std::initializer_list<Assignment> assignments)
        {
            if (!_finished)
                for (const Assignment& a : assignments)
                    _assignments.push_back(a);
            else
                throw FinishedProgramException();
        }

        /* Compiles the program
        */
        void finish()
        {
            if (!_finished)
            {
                compiler::compile(_assignments, _inputs, _outputs);
                _finished = true;
            }
        }

        /* Runs the compiled program
        */
        void run()
        {
            if (_finished)
                ;
            else
                throw UnfinishedProgramException();
        }

    private:

        // has the program been compiled
        bool _finished = false;

        // assignments stored so far
        std::vector<Assignment> _assignments;

        // pointers to inputs and outputs
        std::vector<const Input*> _inputs;
        std::vector<Output*> _outputs;
    };
}