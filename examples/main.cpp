#include "main.hpp"

#include <csgo/util/window.hpp>
#include <array>

int main(int argc, char* argv[]) {
	
	csgo::util::window_pointer pwindow = csgo::util::make_window(800, 600);
	auto& window = *pwindow;

	std::ptrdiff_t simulation_index = 0;
	std::ptrdiff_t simulation_size = 5;
	straight_color straight_color_sim;
	simple simple_sim;
	map_roll map_roll_sim;
	function_demo function_demo_sim;
	particles particles_sim;
	for (auto starttime = std::chrono::high_resolution_clock::now();;) {
		if (simulation_index >= simulation_size) {
			simulation_index = 0;
		}
		else if (simulation_index < 0) {
			simulation_index = simulation_size - 1;
		}

		auto endtime = std::chrono::high_resolution_clock::now();
		auto integralelapsed = endtime - starttime;
		f_milliseconds elapsed = std::chrono::duration_cast<f_milliseconds>(integralelapsed);

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		switch (simulation_index) {
		case 0:
			straight_color_sim(window, elapsed);
			break;
		case 1:
			simple_sim(window, elapsed);
			break;
		case 2:
			map_roll_sim(window, elapsed);
			break;
		case 3:
			function_demo_sim(window, elapsed);
			break;
		case 4:
			particles_sim(window, elapsed);
			break;
		}
		starttime = std::chrono::high_resolution_clock::now();
		glfwSwapBuffers(&window);
	}
	return 0;
}