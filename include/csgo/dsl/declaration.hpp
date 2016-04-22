#pragma once

#include <csgo/dsl/variable.hpp>

namespace csgo {
	namespace dsl {
		struct declaration : expression {
			std::unique_ptr<variable> vardecl;

			declaration(std::unique_ptr<variable> vardecl) : vardecl(std::move(vardecl)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};

		struct declaration_assignment : declaration {
			std::unique_ptr<expression> initialization;

			declaration_assignment(std::unique_ptr<variable> decl, std::unique_ptr<expression> init) : declaration(std::move(decl)), initialization(std::move(init)) {}

			virtual void accept(statement_visitor& v) override {
				v.visit(*this);
			}
		};
	}
}