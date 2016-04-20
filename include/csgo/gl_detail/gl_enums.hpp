#pragma once

#include <csgo/platform_gl.hpp>
#include <csgo/shader_stage.hpp>
#include <csgo/enums.hpp>

namespace csgo {
	namespace gl_detail {
		enum class shader_stage {
			vertex = gl::VERTEX_SHADER,
			hull = gl::TESS_CONTROL_SHADER,
			tessellation_control = hull,
			domain = gl::TESS_EVALUATION_SHADER,
			tessellation_evaluation = domain,
			geometry = gl::GEOMETRY_SHADER,
			pixel = gl::FRAGMENT_SHADER,
			fragment = pixel,
			compute = gl::COMPUTE_SHADER,
		};
		
		inline shader_stage to_platform(csgo::shader_stage value) {
			static const shader_stage stages[] = {
				shader_stage::vertex,
				shader_stage::tessellation_control,
				shader_stage::tessellation_evaluation,
				shader_stage::geometry,
				shader_stage::pixel,
				shader_stage::compute,
			};
			return stages[enums::to_underlying(value)];
		}
	}
}
