#pragma once

namespace csgo {
	namespace dsl {

		enum class type {

			// scalar types
			boolean,
			integer,
			unsigned_integer,
			single_precision,
			double_precision,

			boolean_vector_2,
			boolean_vector_3,
			boolean_vector_4,
			integer_vector_2,
			integer_vector_3,
			integer_vector_4,
			unsigned_integer_vector_2,
			unsigned_integer_vector_3,
			unsigned_integer_vector_4,
			single_vector_2,
			single_vector_3,
			single_vector_4,
			double_vector_2,
			double_vector_3,
			double_vector_4,

			single_matrix_22,
			single_matrix_23,
			single_matrix_24,
			single_matrix_32,
			single_matrix_33,
			single_matrix_34,
			single_matrix_42,
			single_matrix_43,
			single_matrix_44,

			double_matrix_22,
			double_matrix_23,
			double_matrix_24,
			double_matrix_32,
			double_matrix_33,
			double_matrix_34,
			double_matrix_42,
			double_matrix_43,
			double_matrix_44,

			// resource types
			image_1d,
			image_2d,
			image_3d,
			image_cube,
			image_2d_rect,
			image_1d_array,
			image_2d_array,
			image_cube_array,
			image_buffer,
			image_2d_multisample,
			image_2d_multisample_array,

			// composite types
			user_defined_type,

		};

	}
}
