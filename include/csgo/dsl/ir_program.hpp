#pragma once

#include <csgo/dsl/entry_point.hpp>
#include <csgo/dsl/ast.hpp>
#include <csgo/type_traits.hpp>
#include <memory>
#include <vector>
#include <tuple>

namespace csgo {
	namespace dsl {

		struct uniform_reference {
			variable_id id;
			type var_type;

			template <typename T>
			uniform_reference(T&& v) : id(v.id), var_type(v.variable_type) {

			}
		};

        // intermediate representation
		struct ir_program {
			std::vector<uniform_reference> inputs;
			std::vector<uniform_reference> outputs;
			entry_point main;
			abstract_syntax_tree ast;

			ir_program(entry_point main, abstract_syntax_tree ast, std::vector<uniform_reference> inputs, std::vector<uniform_reference> outputs ) : main(std::move(main)), ast(std::move(ast)), inputs(std::move(inputs)), outputs(std::move(outputs)) { 

			}
		};

		namespace dsl_detail {
			template <typename... Args, typename F>
			ir_program make_ir_program_inputs(F&& f, Args&&... args) {
				// Instantiate default-constructed arguments
				std::vector<uniform_reference> inputs{ args... };
				decltype(auto) ret = f(std::forward<Args>(args)...);
				abstract_syntax_tree ast(ret);
				std::vector<uniform_reference> outputs;
				outputs.reserve(ast.returns.size());
				for (const auto& r : ast.returns) {
					outputs.push_back(*r);
				}
				return ir_program(std::forward<decltype(ret)>(ret), std::move(ast), std::move(inputs), std::move(outputs));
			}

			template <typename F, typename... Args>
			ir_program make_ir_program_ordered(meta::types<>, F&& f, Args&&... args) {
				// As you can see, the "types" list is empty,
				// which means we've instantiated all of the arguments
				// into the Args... pack. Now we just forward them
				return make_ir_program_inputs(std::forward<F>(f), std::forward<Args>(args)...);
			}

			template <typename T, typename... Args, typename F, typename... FxArgs>
			ir_program make_ir_program_ordered(meta::types<T, Args...>, F&& f, FxArgs&&... fxargs) {
				// This fixes the order of evaluation of arguments
				// We instantiate the leftmost (first) argument T, stick it after the arguments we've already
				// instianted (the FxArgs...),
				// and then recurse until we hit the base case above
				return make_ir_program_ordered(meta::types<Args...>(), std::forward<F>(f), std::forward<FxArgs>(fxargs)..., T());
			}
			
			template <typename... Args, typename F>
			ir_program make_ir_program(meta::types<Args...> ta, F&& f) {
				// Instantiate default-constructed arguments
				// The ordered function ensures it's instantiated in the proper order
				return make_ir_program_ordered(ta, std::forward<F>(f));
			}
		}

		template <typename F>
		ir_program make_ir_program(F&& f) {
			// determine the arguments of F
			typedef typename meta::bind_traits<meta::unqualified_t<F>>::args_type args_type;
			return dsl_detail::make_ir_program(args_type(), std::forward<F>(f));
		}
	}
}
