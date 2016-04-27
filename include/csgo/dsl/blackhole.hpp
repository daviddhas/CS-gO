#pragma once

#include <csgo/dsl/statement.hpp>
#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/variable.hpp>
#include <vector>

namespace csgo {
	namespace dsl {
		
		template <typename T, meta::enable<is_expression<T>> = meta::enabler>
		inline decltype(auto) make_expression(T&& value) {
			return std::forward<T>(value);
		}

		template <typename T, meta::enable<is_primitive<T>> = meta::enabler>
		inline decltype(auto) make_expression(T&& value) {
			return typed_constant<meta::unqualified_t<T>>(std::forward<T>(value));
		}

		template <typename T>
		inline decltype(auto) make_unique_expression(T&& value) {
			decltype(auto) r = make_expression(std::forward<T>(value));
			return std::make_unique<meta::unqualified_t<decltype(r)>>(std::forward<decltype(r)>(r));
		}

		struct blackhole {
			std::vector<statement> statements;
			bool consuming;

			blackhole() : consuming(false) {
				statements.reserve(128);
			}

			void begin() {
				statements.clear();
				statements.push_back({});
				consuming = true;
			}

			template <typename Expression>
			void consume(Expression&& expression, bool terminating = is_terminating_expression<meta::unqualified_t<Expression>>::value) {
				if (!consuming)
					return;
				statement& s = statements.back();
				s.expressions.push_back(make_unique_expression(std::forward<Expression>(expression)));
				if (terminating) {
					statements.push_back({});
				}
			}

			void end() {
				consuming = false;
			}
			
			void accept(statement_visitor& v) {
				for (auto& s : statements) {
					s.accept(v);
				}
			}
		};

		struct blackhole_guard {
			blackhole& b;
			blackhole_guard(blackhole& b) : b(b) {
				b.begin();
			}

			~blackhole_guard() {
				b.end();
			}
		};

		inline blackhole& get_blackhole() {
			thread_local blackhole b;
			return b;
		}
	}
}
