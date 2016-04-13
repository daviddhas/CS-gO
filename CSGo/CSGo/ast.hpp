#pragma once

#include "ProgramExceptions.hpp"
#include "Compiler.hpp"

#include <vector>
#include <algorithm>

namespace csgo
{
	// This class gathers and generates relevant information based on
	// expressions and statements in a csgo module.
	// Meant to be consumed by the compiler / program
	class abstract_syntax_tree {
	public:

		abstract_syntax_tree(std::initializer_list<Input> inputs, std::initializer_list<Output*> outputs) {
			for (const Input& i : inputs)
				_inputs.push_back(&i);

			for (Output *o : outputs)
				_outputs.push_back(o);

		}

		/* Adds the list of assignments to the prorgam
		*/
		void add(std::initializer_list<Assignment> assignments)
		{
			// This code assumes that at the end of the day,
			// every program results in assignment to an output
			if (!_finished)
				for (const Assignment& a : assignments)
					_assignments.push_back(a);
			else
				throw FinishedProgramException();
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
