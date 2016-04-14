#pragma once

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
            if (_finished)
            {
			  return;
            }
		  Compiler& compiler = get_compiler();
		  _program = std::make_unique<compute_program>(compiler.compile(_assignments, _inputs, _outputs, _x, _y, _z));
		  _finished = true;
        }

        /* Runs the compiled program
        */
        void run()
        {
            if (!_finished)
                throw UnfinishedProgramException();
		  _program->run();
        }

    private:
	    // Compiler instance to work with (static until we sort out initialization hierarchy
	    static Compiler& get_compiler() {
		    static Compiler compiler{};
		    return compiler;
	    }

	    // pointer for deferred initialization until get std::(experimental::)optional
	    std::unique_ptr<compute_program> _program;

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