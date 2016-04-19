#pragma once

#include <csgo/dsl/type.hpp>
#include <csgo/dsl/expression.hpp>
#include <csgo/dsl/variable_id.hpp>
#include <csgo/qualifiers.hpp>
#include <csgo/type_traits.hpp>
#include <memory>
#include <atomic>
#include <cstdint>

namespace csgo {
	namespace dsl {
		struct variable : expression {
			variable_id id = generate_id<variable>();
			type variable_type;
			std::shared_ptr<expression> initialization;

			variable() : variable_type(type::user_defined_type) {}
			variable(type vartype) : variable_type(vartype), initialization(std::move(initialization)) {}
			variable(std::unique_ptr<expression> initialization, type vartype) : variable_type(vartype), initialization(std::move(initialization)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct layout_variable : variable {
			qualifiers layout;
			
			layout_variable() : layout_variable({}, type::image_2d) {}
			layout_variable(qualifiers q) : layout_variable(q, type::image_2d) {}
			layout_variable(qualifiers q, type thistype) : variable(thistype), layout(std::move(q)) {}
			layout_variable(std::unique_ptr<expression> initilization, qualifiers q, type thistype) : variable(std::move(initilization), thistype), layout(std::move(q)) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}
		};

		struct constant : variable {
			constant(type x) : variable(x) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}

			virtual void write(std::ostream& ostr) = 0;
		};

		template <typename T>
		struct typed_constant : constant {
			T value;

			typed_constant(T value) : typed_constant(value, type_for<T>::value) {}
			typed_constant(T value, type x) : constant(x), value(value) {}

			virtual void accept(expression_visitor& v) override {
				v.visit(*this);
			}

			virtual void write(std::ostream& ostr) override {
				ostr << value;
			}
		};


		template <typename T>
		struct is_variable : std::is_base_of<variable, meta::unqualified_t<T>> {};
		
		template <typename T>
		struct is_expression : std::is_base_of<expression, meta::unqualified_t<T>> {};

		template <typename T>
		struct is_primitive : std::is_arithmetic<meta::unqualified_t<T>> {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec1<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tvec4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat2x4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat3x4<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x2<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x3<T, p>> : std::true_type {};

		template <typename T, glm::precision p>
		struct is_primitive<glm::tmat4x4<T, p>> : std::true_type {};

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
	}
}
