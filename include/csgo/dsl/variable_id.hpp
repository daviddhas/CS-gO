#pragma once

#include <atomic>
#include <cstdint>

namespace csgo {
	namespace dsl {
		struct variable_id {
			int64_t id;

			variable_id(int64_t id) :id(id) {}
			variable_id() = default;
			variable_id(const variable_id&) = default;
			variable_id& operator=(const variable_id&) = default;
		};

		bool operator== (const variable_id& l, const variable_id& r) {
			return l.id == r.id;
		}

		bool operator!= (const variable_id& l, const variable_id& r) {
			return l.id != r.id;
		}

		bool operator< (const variable_id& l, const variable_id& r) {
			return l.id < r.id;
		}

		bool operator> (const variable_id& l, const variable_id& r) {
			return l.id > r.id;
		}

		bool operator<= (const variable_id& l, const variable_id& r) {
			return l.id <= r.id;
		}

		bool operator>= (const variable_id& l, const variable_id& r) {
			return l.id >= r.id;
		}

		template <typename Tag, typename A = int64_t>
		inline A generate_id() {
			static std::atomic<A> i;
			return i++;
		}
	}
}

namespace std {

	template <>
	struct hash< ::csgo::dsl::variable_id > {
		::std::size_t operator()(const ::csgo::dsl::variable_id& x) const {
			return std::hash<int64_t>()(x.id);
		}
	};

}
