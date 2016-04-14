#pragma once

#include "graphics_device.hpp"
#include "shader.hpp"


namespace csgo {

    class compute_program {
    public:
        compute_program(shader_source code, int wgx, int wgy, int wgz) : _cshader(code), _workgroupx(wgx), _workgroupy(wgy), _workgroupz(wgz)  {
            
        }

	   void run() {
		   // Do all the bindings here...
		   GLuint programid = _cshader.shader_resource();
		   gl::UseProgram(programid); // Compute shader program.
		   gl::DispatchCompute(_workgroupx, _workgroupy, _workgroupz);
	   }

    private:
	    uint32_t _workgroupx;
	    uint32_t _workgroupy;
	    uint32_t _workgroupz;
	    compute_shader _cshader;
    };
}