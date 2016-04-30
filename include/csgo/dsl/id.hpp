#pragma once

#include <atomic>
#include <cstdint>

namespace csgo {
	namespace dsl {
		struct id {
			int64_t value;

			id(int64_t value) : value(value) {}
			id() = default;
			id(const id&) = default;
			id& operator=(const id&) = default;
		};

		inline bool operator== (const id& l, const id& r) {
			return l.value == r.value;
		}

		inline bool operator!= (const id& l, const id& r) {
			return l.value != r.value;
		}

		inline bool operator< (const id& l, const id& r) {
			return l.value < r.value;
		}

		inline bool operator> (const id& l, const id& r) {
			return l.value > r.value;
		}

		inline bool operator<= (const id& l, const id& r) {
			return l.value <= r.value;
		}

		inline bool operator>= (const id& l, const id& r) {
			return l.value >= r.value;
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
	struct hash< ::csgo::dsl::id > {
		::std::size_t operator()(const ::csgo::dsl::id& x) const {
			return std::hash<decltype(x.value)>()(x.value);
		}
	};

}
