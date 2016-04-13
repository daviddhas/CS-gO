#pragma once

#include <GL/glew.h>

#include "ProgramExceptions.hpp"
#include "Compiler.hpp"

#include <vector>
#include <algorithm>

namespace csgo
{
    class Program
    {
    public:

        // TODO: appropriately infer number of work groups
        Program(std::initializer_list<std::shared_ptr<Input>> inputs, std::initializer_list<std::shared_ptr<Output>> outputs)
            : Program(inputs, outputs, 16, 16, 1)
        { }

        /* Creates a CS Go program with the given inputs, outputs,
         * and work group dimensions
        */
        Program(std::initializer_list<std::shared_ptr<Input>> inputs, std::initializer_list<std::shared_ptr<Output>> outputs,
                int x, int y, int z)
            : _inputs({ inputs })
            , _outputs({ outputs })
            , _x(x)
            , _y(y)
            , _z(z)
        {

            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MAJOR_VERSION, &minor);
            if (major < 4 || minor < 3)
                throw ComputeShaderSupportException();
        }

        /* Adds the list of assignments to the prorgam
        */
        void set(std::shared_ptr<LValue> lhs, std::shared_ptr<Expression> rhs)
        {
            if (!_finished)
                _assignments.push_back(Assignment(lhs, rhs));
            else
                throw FinishedProgramException();
        }

        /* Compiles the program
        */
        void finish()
        {
            if (!_finished)
            {
                Compiler::compile(_assignments, _inputs, _outputs, _x, _y, _z);
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
        // work group dimensions
        int _x, _y, _z;

        // has the program been compiled
        bool _finished = false;

        // assignments stored so far
        std::vector<Assignment> _assignments;

        // pointers to inputs and outputs
        std::vector<std::shared_ptr<Input>> _inputs;
        std::vector<std::shared_ptr<Output>> _outputs;
    };
}