#pragma once

#include <csgo/dsl/ir_entry_point.hpp>
#include <csgo/dsl/abstract_syntax_tree.hpp>
#include <csgo/type_traits.hpp>
#include <memory>
#include <vector>
#include <tuple>

namespace csgo {
	namespace dsl {

		struct ir_program {
			ir_entry_point main;
			abstract_syntax_tree ast;

			ir_program(ir_entry_point main, abstract_syntax_tree ast) : main(std::move(main)), ast(std::move(ast)) {

			}
		};

		namespace dsl_detail {
			template <std::size_t... I, typename... Args, typename F>
			ir_program make_ir_program_inputs(std::index_sequence<I...>, F&& f, Args&&... args) {
				// Set up the black hole that sucks in statements
				// plus its guard
				
				std::vector<std::unique_ptr<variable>> inputs;
				(void)detail::swallow{ (
					inputs.push_back(dsl::make_unique_expression(args))
				, 0)... };
				blackhole& b = get_blackhole(); {
					blackhole_guard g(b);
					entry_point ep = f(args...);
					ir_entry_point irep(std::move(ep), std::move(inputs), std::move(b.statements));
					abstract_syntax_tree ast(irep);
					return ir_program(std::move(irep), std::move(ast));
				}
			}

			template <std::size_t... I, typename F, typename... Args>
			ir_program make_ir_program_ordered(meta::types<>, std::index_sequence<I...> indices, F&& f, Args&&... args) {
				// As you can see, the "types" list is empty,
				// which means we've instantiated all of the arguments
				// into the Args... pack. Now we just forward them
				return make_ir_program_inputs(indices, std::forward<F>(f), std::forward<Args>(args)...);
			}

			template <std::size_t... I, typename T, typename... Args, typename F, typename... FxArgs>
			ir_program make_ir_program_ordered(meta::types<T, Args...>, std::index_sequence<I...> indices, F&& f, FxArgs&&... fxargs) {
				// This fixes the order of evaluation of arguments
				// We instantiate the leftmost (first) argument T, stick it after the arguments we've already
				// instianted (the FxArgs...),
				// and then recurse until we hit the base case above
				return make_ir_program_ordered(meta::types<Args...>(), indices, std::forward<F>(f), std::forward<FxArgs>(fxargs)..., T());
			}

			template <std::size_t... I, typename... Args, typename F>
			ir_program make_ir_program(meta::types<Args...> ta, std::index_sequence<I...> indices, F&& f) {
				// Instantiate default-constructed arguments
				// The ordered function ensures it's instantiated in the proper order
				return make_ir_program_ordered(ta, indices, std::forward<F>(f));
			}
		}

		template <typename F>
		ir_program make_ir_program(F&& f) {
			// determine the arguments of F
			typedef typename meta::bind_traits<meta::unqualified_t<F>>::args_type args_type;
			typedef std::make_index_sequence<meta::bind_traits<meta::unqualified_t<F>>::arity> indices_type;
			return dsl_detail::make_ir_program(args_type(), indices_type(), std::forward<F>(f));
		}
	}
}
