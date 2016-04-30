#pragma once

#include "program.hpp"
#include "shader.hpp"


namespace csgo {

    class compute_program : public program {
    public:
	    template <typename F>
	    compute_program(F&& func) : program(std::forward<F>(func)) {

	    }
    };
}