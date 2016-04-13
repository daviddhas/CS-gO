#pragma once

#include <vector>
#include "Assignment.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "CodeGenerator.hpp"
#include "ast.hpp"

namespace csgo {
	struct compiler {
	private:
		code_generator codegen;

	public:
		compiler(abstract_syntax_tree& ast) {

		}
    };
}