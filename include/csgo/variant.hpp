#pragma once

#include "type_traits.hpp"
#include "in_place.hpp"
#include <cassert>

namespace csgo {

	struct bad_variant_cast : public std::bad_cast {
		using std::bad_cast::bad_cast;
		using std::bad_cast::operator=;
	};

	struct empty_variant_t {
	} const empty_variant;

	namespace variant_detail {
		template <typename T>
		struct reference_storage {
			T* elem;

			reference_storage(T& arg) : elem(std::addressof(arg)) {

			}

			operator T& () {
				return *elem;
			}

			operator const T& () const {
				return *elem;
			}
		};

		template <typename T, typename Policy, typename = void>
		struct valid_check {
			typedef std::false_type allows_empty_variant;
		};

		template <typename T, typename Policy>
		struct valid_check<T, Policy, std::enable_if_t<std::is_same<meta::unqualified_t<std::result_of_t<decltype(&Policy::construct)>>, empty_variant_t>::value>> {
			typedef std::true_type allows_empty_variant;
			bool valid() const {
				/*static_assert(
				std::is_same<meta::unqualified_t<decltype(policy::construct())>, empty_variant_t>::value,
				"This variant will always be valid (no need to call this function) (use optional_variant if you want an optional behavior)."
				);*/
				return static_cast<const T&>(*this).class_idx != -1;
			}
		};

		template <typename T, typename = void>
		struct unqualified_unwrap {
			typedef T type;
		};

		template <typename T>
		struct unqualified_unwrap<T, std::enable_if_t<meta::is_specialization<meta::unqualified_t<T>, std::reference_wrapper>::value>>
			: meta::unwrap<meta::unqualified_t<T>> {

		};

		template <typename T>
		using unqualified_unwrap_t = meta::invoke_t<unqualified_unwrap<T>>;

		template <typename T>
		using actual_t = unqualified_unwrap_t<meta::unqualified_t<T>>;

		template <typename T>
		using storage_t = std::conditional_t<std::is_lvalue_reference<std::remove_cv_t<T>>::value, reference_storage<meta::unqualified_t<T>>, std::remove_reference_t<T>>;

		struct visitor {
			template <typename T, std::ptrdiff_t I, typename Tv, typename TFx, typename... Tn>
			decltype(auto) operator()(meta::types<T>, meta::int_sequence<I>, Tv&& var, TFx&& fx, Tn&&... argn) const {
				return fx(var.unsafe_get<T>(), std::forward<Tn>(argn)...);
			}

			template <typename Tv, typename TFx, typename... Tn>
			decltype(auto) operator()(meta::types<>, meta::int_sequence<>, Tv&& var, TFx&& fx, Tn&&... argn) const {
				typedef meta::unqualified_t<Tv> variant_t;
				typedef variant_t::at_t<0> T;
				if (var.class_idx != -1)
					throw bad_variant_cast();
				return fx(var.unsafe_get<T>(), std::forward<Tn>(argn)...);
			}
		};

		struct copy_visitor {
			template <typename T, std::ptrdiff_t I, typename Tv, typename To>
			void operator()(meta::types<T>, meta::int_sequence<I>, Tv&& var, To&& copy) {
				typedef variant_detail::storage_t<T> Ts;
				typedef variant_detail::actual_t<T> Ta;
				new (std::addressof(var.storage))Ts(copy.get<Ta>());
				var.class_idx = I;
			}

			template <typename Tv, typename To>
			void operator()(meta::types<>, meta::int_sequence<>, Tv&&, To&&) {
				// TODO: is there a policy we should invoke
				// here if there's nothing to do?
			}
		};

		struct move_visitor {
			template <typename T, std::ptrdiff_t I, typename Tv, typename To>
			void operator()(meta::types<T>, meta::int_sequence<I>, Tv&& var, To&& mov) {
				typedef variant_detail::storage_t<T> Ts;
				new (std::addressof(var.storage))Ts(std::move(mov.get<T>()));
				var.class_idx = I;
			}

			template <typename Tv, typename To>
			void operator()(meta::types<>, meta::int_sequence<>, Tv&&, To&&) {
				// TODO: is there a policy we should invoke
				// here if there's nothing to do?
			}
		};

		struct destruct_visitor {
			template <typename T, std::ptrdiff_t I, typename Tv>
			void operator()(meta::types<T>, meta::int_sequence<I>, Tv&& var) {
				typedef std::is_const<std::remove_reference_t<Tv>> is_const;
				typedef variant_detail::storage_t<T> Ts;
				typedef std::conditional_t<is_const::value, const Ts, Ts> Ts_t;
				typedef std::conditional_t<is_const::value, const void, void> void_t;
				Ts_t& storage = *static_cast<Ts_t*>(static_cast<void_t*>(std::addressof(var.storage)));
				storage.~Ts_t();
				var.class_idx = -1;
			}

			template <typename Tv>
			void operator()(meta::types<>, meta::int_sequence<>, Tv&&) {
				// TODO: is there a policy we should invoke
				// here if there's nothing to do?
			}
		};
	}

	struct union_policy {
		template <typename... Cn>
		static auto construct(meta::types<Cn...>) {
			typedef meta::at_pack_t<0, Cn...> default_t;
			return default_t();
		}
	};

	struct optional_policy {
		template <typename... Cn>
		static empty_variant_t construct(meta::types<Cn...>) {
			return empty_variant;
		}
	};

	template <typename Policy, typename... Cn>
	struct variant_base : public variant_detail::valid_check<variant_base<Policy, Cn...>, Policy> {
	public:
		typedef meta::types<Cn...> variant_types;
		typedef Policy policy;
		template <typename T>
		using index = meta::index_of_pack<T, Cn...>;
		// TODO: One day...
		/*template <typename T>
		using index_v = meta::index_of<T, Cn...>::value;*/
		template <std::ptrdiff_t I>
		using at = meta::at_pack<I, Cn...>;
		template <std::ptrdiff_t I>
		using at_t = meta::at_pack_t<I, Cn...>;

	private:
		friend variant_detail::copy_visitor;
		friend variant_detail::move_visitor;
		friend variant_detail::destruct_visitor;
		friend variant_detail::visitor;
		std::ptrdiff_t class_idx;
		std::aligned_storage_t<meta::max<sizeof(Cn)...>::value> storage;

		template <std::size_t n = 0>
		struct walker {
			template <typename Tv, typename TFx, typename... Tn>
			decltype(auto) operator()(Tv&& var, TFx&& fx, Tn&&... argn) const {
				return walk(var.class_idx, std::forward<Tv>(var), std::forward<TFx>(fx), std::forward<Tn>(argn)...);
			}

			template <typename Tv, typename TFx, typename... Tn>
			decltype(auto) walk(std::ptrdiff_t idx, Tv&& var, TFx&& fx, Tn&&... argn) {
				typedef meta::at_pack_t<n, Cn...> T;
				if (n == idx)
					return fx(meta::types<T>(), meta::int_sequence<n>(), std::forward<Tv>(var), std::forward<Tn>(argn)...);
				walker<n + 1> w{};
				return w.walk(idx, std::forward<Tv>(var), std::forward<TFx>(fx), std::forward<Tn>(argn)...);
			}
		};

		template <>
		struct walker<sizeof...(Cn)> {
			template <typename Tv, typename TFx, typename... Tn>
			decltype(auto) operator()(Tv&& var, TFx&& fx, Tn&&... argn) const {
				return walk(var.class_idx, std::forward<Tv>(var), std::forward<TFx>(fx), std::forward<Tn>(argn)...);
			}

			template <typename Tv, typename TFx, typename... Tn>
			decltype(auto) walk(std::ptrdiff_t idx, Tv&& var, TFx&& fx, Tn&&... argn) const {
				return fx(meta::types<>(), meta::int_sequence<>(), std::forward<Tv>(var), std::forward<Tn>(argn) ...);
			}
		};

		template <typename TFx, typename... Tn>
		decltype(auto) walk_at(std::ptrdiff_t idx, TFx&& fx, Tn&&... argn) {
			walker<> w{};
			return w.walk(idx, *this, std::forward<TFx>(fx), std::forward<Tn>(argn)...);
		}

		template <typename TFx, typename... Tn>
		decltype(auto) walk_at(std::ptrdiff_t idx, TFx&& fx, Tn&&... argn) const {
			walker<> w{};
			return w.walk(idx, *this, std::forward<TFx>(fx), std::forward<Tn>(argn)...);
		}

		template <std::ptrdiff_t I, typename... Tn>
		void place(in_place_at<I>, Tn&&... argn) {
			static_assert(I < sizeof...(Cn) && I > -1, "The type desired is not within the bounds for this variant_base");
			typedef meta::at_pack_t<I, Cn...> T;
			typedef variant_detail::storage_t<T> Ts;
			typedef variant_detail::actual_t<T> Ta;
			typedef meta::any<std::is_same<Ta, Cn>...> contains_t;
			new (std::addressof(storage))Ts(std::forward<Tn>(argn)...);
			class_idx = I;
		}

		template <typename T, typename... Tn>
		void place(in_place_of<T>, Tn&&... argn) {
			typedef meta::index_of_pack<T, Cn...> index_t;
			static_assert(index_t::value != -1, "Desired type is not part of this variant");
			//static_assert(meta::index_of<T, Cn...>::value == meta::last_index_of<T, Cn...>::value, "Cannot determine which type is the correct one to use: specify in_place_at<integer_constant> to give specific type");
			place(in_place_at<index_t::value>(), std::forward<Tn>(argn)...);
		}

		template <typename T>
		void place(T&& item) {
			place(in_place_of<variant_detail::actual_t<T>>(), std::forward<T>(item));
		}

	public:
		template <std::ptrdiff_t I, typename... Tn>
		variant_base(in_place_at<I> ipa, Tn&&... argn) : class_idx(-1) {
			place(ipa, std::forward<Tn>(argn)...);
		}

		template <typename T, typename... Tn>
		variant_base(in_place_of<T>, Tn&&... argn) : variant_base(in_place_at<meta::index_of_pack<T, Cn...>::value>(), std::forward<Tn>(argn)...) {
			static_assert(meta::index_of_pack<T, Cn...>::value != -1, "Desired type is not part of this variant");
			//static_assert(meta::index_of<T, Cn...>::value == meta::last_index_of<T, Cn...>::value, "Cannot determine which type is the correct one to use: specify in_place_at<integer_constant> to give specific type");
		}

		template <typename T, typename = std::enable_if_t<!std::is_same<variant_base, meta::unqualified_t<T>>::value && !std::is_same<empty_variant_t, meta::unqualified_t<T>>::value>>
		variant_base(T&& item) : variant_base(in_place_of<variant_detail::actual_t<T>>(), std::forward<T>(item)) {}

		variant_base() : variant_base(policy::construct(variant_types())) {

		}

		variant_base(empty_variant_t) {
			static_assert(allows_empty_t::value, "You cannot construct an empty variant unless the policy allows for it.");
		}

		variant_base(const variant_base& copy) : class_idx(-1) {
			variant_detail::copy_visitor copier{};
			walk_at(copy.class_idx, copier, copy);
		}

		variant_base(variant_base&& mov) : class_idx(-1) {
			variant_detail::move_visitor mover{};
			walk_at(mov.class_idx, mover, std::move(mov));
		}

		template <typename T, typename = std::enable_if_t<!std::is_same<variant_base, meta::unqualified_t<T>>::value>>
		variant_base& operator=(T&& item) {
			variant_detail::destruct_visitor destructor{};
			walk(destructor);
			place(std::forward<T>(item));
			return *this;
		}

		variant_base& operator=(const variant_base& copy) {
			variant_detail::destruct_visitor destructor{};
			walk(destructor);
			variant_detail::copy_visitor copier{};
			walk_at(copy.class_idx, copier, copy);
			return *this;
		}

		variant_base& operator=(variant_base&& mov) {
			variant_detail::destruct_visitor destructor{};
			walk(destructor);
			variant_detail::move_visitor mover{};
			walk_at(mov.class_idx, mover, std::move(mov));
			return *this;
		}

		~variant_base() {
			variant_detail::destruct_visitor destructor{};
			walk(destructor);
		}

		std::ptrdiff_t class_index() const {
			return class_idx;
		}

		template <typename T>
		bool is() const {
			return class_index() == meta::index_of_pack<T, Cn...>::value;
		}

		template <typename T>
		T& unsafe_get() {
			typedef variant_detail::storage_t<T> Ts;
			return *static_cast<Ts*>(static_cast<void*>(std::addressof(storage)));
		}

		template <typename T>
		const T& unsafe_get() const {
			typedef variant_detail::storage_t<T> Ts;
			return *static_cast<const Ts*>(static_cast<const void*>(std::addressof(storage)));
		}

		template <typename T>
		T& get() {
			assert((class_idx == meta::index_of_pack<T, Cn...>::value));
			return unsafe_get<T>();
		}

		template <typename T>
		const T& get() const {
			assert((class_idx == meta::index_of_pack<T, Cn...>::value));
			return unsafe_get<T>();
		}

		template <typename... Tn>
		decltype(auto) visit(Tn&&... argn) {
			variant_detail::visitor v{};
			return walk(v, std::forward<Tn>(argn)...);
		}

		template <typename... Tn>
		decltype(auto) visit(Tn&&... argn) const {
			variant_detail::visitor v{};
			return walk(v, std::forward<Tn>(argn)...);
		}

		template <typename TFx, typename... Tn>
		decltype(auto) walk(TFx&& fx, Tn&&... argn) {
			return walk_at(class_idx, std::forward<TFx>(fx), std::forward<Tn>(argn)...);
		}

		template <typename TFx, typename... Tn>
		decltype(auto) walk(TFx&& fx, Tn&&... argn) const {
			return walk_at(class_idx, std::forward<TFx>(fx), std::forward<Tn>(argn)...);
		}
	};

	template <typename... Cn>
	using union_variant = variant_base<union_policy, Cn...>;

	template <typename... Cn>
	using optional_variant = variant_base<optional_policy, Cn...>;

	template <typename... Cn>
	using variant = union_variant<Cn...>;

}
