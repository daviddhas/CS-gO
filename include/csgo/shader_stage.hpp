#pragma once

namespace csgo {

	enum class shader_stage {
		vertex = 0x00,
		hull = 0x01,
		tessellation_control = hull,
		domain = 0x02,
		tessellation_evaluation = domain,
		geometry = 0x03,
		pixel = 0x04,
		fragment = pixel,
		compute = 0x05,
	};

}
