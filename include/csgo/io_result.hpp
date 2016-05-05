#pragma once

#include <csgo/built_in_io.hpp>
#include <vector>
#include <tuple>

namespace csgo {

#pragma region converter

	template<typename T>
	struct converter {};

	template<>
	struct converter<image2d_io<float>>
	{
		static image2d_io<float> convert(const std::vector<texture_data>& data)
		{
			return image2d_io<float>(data[0]);
		}
	};

	template<>
	struct converter<image2d_io<int>>
	{
		static image2d_io<int> convert(const std::vector<texture_data>& data) {
			return image2d_io<int>(data[0]);
		}
	};

	template<>
	struct converter<image2d_io<glm::vec2>>
	{
		static image2d_io<glm::vec2> convert(const std::vector<texture_data>& data) {
			return image2d_io<glm::vec2>(data[0]);
		}
	};

	template<>
	struct converter<image2d_io<glm::vec3>>
	{
		static image2d_io<glm::vec3> convert(const std::vector<texture_data>& data) {
			return image2d_io<glm::vec3>(data[0]);
		}
	};

	template<>
	struct converter<image2d_io<glm::vec4>>
	{
		static image2d_io<glm::vec4> convert(const std::vector<texture_data>& data) {
			return image2d_io<glm::vec4>(data[0]);
		}
	};

	template<typename... Args>
	struct converter<std::tuple<Args...>> {
		template <std::size_t... Indices>
		static std::tuple<Args...> convert(std::index_sequence<Indices...>, const std::vector<texture_data>& data) {
			return std::make_tuple(converter<Args>{}.convert(outputs[Indices])...);
		}

		static std::tuple<Args...> convert(const std::vector<texture_data>& data) {
			return convert(std::make_index_sequence<sizeof...(Args)>(), data);
		}
	};

#pragma endregion

	struct io_result {
		io_result(std::vector<texture_data> outputs)
			: outputs(std::move(outputs))
		{ }

		template <typename T>
		operator T()
		{
			return converter<meta::unqualified_t<T>>{}.convert(outputs);
		}


	private:

		std::vector<texture_data> outputs;
	};
}
