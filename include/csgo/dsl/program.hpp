#pragma once

#include <csgo/dsl/entry_point.hpp>
#include <csgo/dsl/ast.hpp>
#include <csgo/type_traits.hpp>
#include <memory>
#include <vector>
#include <tuple>

namespace csgo {
	namespace dsl {

		struct uniform_descriptor {
			variable_id id;
			type var_type;

			template <typename T>
			uniform_descriptor(T&& v) : id(v.id), var_type(v.variable_type) {

			}
		};

		struct program {
			std::vector<uniform_descriptor> inputs;
			std::vector<uniform_descriptor> outputs;
			entry_point main;
			abstract_syntax_tree ast;

			program(entry_point main, abstract_syntax_tree ast, std::vector<uniform_descriptor> inputs, std::vector<uniform_descriptor> outputs ) : main(std::move(main)), ast(std::move(ast)), inputs(std::move(inputs)), outputs(std::move(outputs)) { 
				
			}
		};

		namespace dsl_detail {
			template <typename... Args, typename F>
			program make_program_inputs(F&& f, Args&&... args) {
				// Instantiate default-constructed arguments
				std::vector<uniform_descriptor> inputs{ args... };
				decltype(auto) ret = f(std::forward<Args>(args)...);
				abstract_syntax_tree ast(ret);
				return program(std::forward<decltype(ret)>(ret), std::move(ast), inputs, {});
			}
			
			template <typename... Args, typename F>
			program make_program(meta::types<Args...>, F&& f) {
				// Instantiate default-constructed arguments
				return make_program_inputs(std::forward<F>(f), Args()...);
			}
		}

		template <typename F>
		program make_program(F&& f) {
			// determine the arguments of F
			typedef typename meta::bind_traits<meta::unqualified_t<F>>::args_type args_type;
			return dsl_detail::make_program(args_type(), std::forward<F>(f));
		}
	}
}
