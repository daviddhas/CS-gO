#pragma once

#include <type_traits>

namespace csgo {
	namespace enums {
		template <typename TEnum>
		inline std::underlying_type_t<TEnum> to_underlying(TEnum value) {
			typedef typename std::underlying_type<TEnum>::type Tu;
			return static_cast<Tu>(value);
		}

		template <typename T, typename TEnum, typename = std::enable_if_t<std::is_enum<TEnum>::value>>
		inline T enum_cast(TEnum value) {
			return static_cast<T>(enums::to_underlying(value));
		}
	}
}
