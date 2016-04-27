#pragma once

#include <csgo/dsl/variable.hpp>
#include <csgo/dsl/expression_consume.hpp>
#include <csgo/dsl/primitives.hpp>
#include <csgo/dsl/binary_expression.hpp>

namespace csgo {
	namespace dsl {
		struct image_variable : layout_variable {
			image_variable() : image_variable({}, type::image_2d) {}
			image_variable(qualifiers q) : image_variable(q, type::image_2d) {}
			image_variable(qualifiers q, type thistype) : layout_variable(std::move(q), thistype) {}

			template <typename T>
			image_variable& operator= (T&& right) {
				consume(assignment(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(right))
				));
				return *this;
			}

			template <typename T>
			indexing operator[](T&& idx) {
				indexing op(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(idx))
				);
				return op;
			}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct buffer_variable : layout_variable {
			buffer_variable() : buffer_variable({}, type::image_buffer) {
				consume(declaration(
					dsl::make_unique_expression(*this)
				));
			}
			buffer_variable(qualifiers q) : buffer_variable(q, type::image_2d) {}
			buffer_variable(qualifiers q, type thistype) : layout_variable(std::move(q), thistype) {}
			template <typename T, meta::enable<is_expression<T>> = meta::enabler>
			buffer_variable(T&& expr) : layout_variable({ format_qualifier_for<uint8_t>::value }, dsl::type::image_2d) {
				consume(declaration_assignment(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(expr))
				));
			}

			template <typename T>
			buffer_variable& operator= (T&& right) {
				consume(assignment(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(right))
				));
				return *this;
			}

			template <typename T>
			indexing operator[](T&& idx) {
				indexing op(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(idx))
				);
				return op;
			}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		template <typename P>
		struct image2d : image_variable {

			image2d() : image_variable({ format_qualifier_for<P>::value }, dsl::type::image_2d) {
				consume(declaration(
					dsl::make_unique_expression(*this)
				));
			}

			template <typename T, meta::enable<is_expression<T>, meta::not_<std::is_same<meta::unqualified_t<T>, image2d>>> = meta::enabler>
			image2d(T&& expr) : image_variable({ format_qualifier_for<P>::value }, dsl::type::image_2d) {
				consume(declaration_assignment(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(expr))
				));
			}
			
			template <typename T>
			image2d& operator= (T&& right) {
				consume(assignment(
					dsl::make_unique_expression(*this),
					dsl::make_unique_expression(std::forward<T>(right))
				));
				return *this;
			}

			virtual void accept(statement_visitor& v) {
				v.visit(*this);
			}
		};
	}
}
