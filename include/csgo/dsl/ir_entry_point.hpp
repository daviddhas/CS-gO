#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/dsl/statement.hpp>
#include <csgo/workgroup.hpp>
#include <csgo/entry_point.hpp>

namespace csgo {
	namespace dsl {
		struct ir_entry_point {
			std::vector<std::unique_ptr<dsl::variable>> input_variables;
			std::vector<std::unique_ptr<dsl::layout_variable>> output_variables;
			workgroup wg;
			std::vector<dsl::statement> statements;

			ir_entry_point(entry_point ep, std::vector<std::unique_ptr<dsl::variable>> inputs, std::vector<dsl::statement> statements)
				: input_variables(std::move(inputs)), output_variables(std::move(ep.output_variables)), wg(std::move(ep.wg)), statements(std::move(statements)) {

			}
		};
	}
}
