#pragma once

namespace csgo {

	enum class memory_qualifier {
		none,
		coherent,
		readonly,
		writeonly,
		volatile_readwrite,
		restricted,
	};

}
