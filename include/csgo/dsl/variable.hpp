#pragma once

#include <csgo/dsl/expression_consume.hpp>
#include <csgo/dsl/id.hpp>
#include <csgo/qualifiers.hpp>
#include <csgo/type_traits.hpp>
#include <csgo/dsl/type.hpp>
#include <csgo/dsl/writer.hpp>
#include <memory>
#include <atomic>
#include <cstdint>

namespace csgo {
	namespace dsl {
		struct variable : expression {
			id variable_id = generate_id<variable>();
			type variable_type;
			
			variable() : variable_type(type::user_defined_type) {}
			variable(type vartype) : variable_type(vartype) {}
			
			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct layout_variable : variable {
			qualifiers layout;
			
			layout_variable() : layout_variable({}, type::image_2d) {}
			layout_variable(qualifiers q) : layout_variable(q, type::image_2d) {}
			layout_variable(qualifiers q, type thistype) : variable(thistype), layout(std::move(q)) {}
			
			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct constant : variable {
			constant(type x) : variable(x) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}

			virtual void write(std::ostream& ostr) const = 0;
		};

		template <typename T>
		struct typed_constant : constant {
			T value;

			typed_constant(T value) : typed_constant(value, type_for<T>::value) {}
			typed_constant(T value, type x) : constant(x), value(value) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}

			virtual void write(std::ostream& ostr) const override {
				writer<T> w{};
				w.write(ostr, value);
			}
		};

		template <typename T>
		struct is_variable : std::is_base_of<variable, meta::unqualified_t<T>> {};
	}
}
