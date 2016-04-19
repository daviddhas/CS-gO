#pragma once

#include <csgo/format_qualifier.hpp>
#include <csgo/memory_qualifier.hpp>
#include <vector>

namespace csgo {
	struct qualifiers {
		format_qualifier format;
		std::vector<memory_qualifier> memory_qualifiers;
	};
}
