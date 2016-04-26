#pragma once

#include <csgo/type_traits.hpp>
#include <csgo/uninitialized.hpp>
#include <csgo/nullopt.hpp>
#include <csgo/in_place.hpp>

namespace csgo {

	template <typename T>
	struct optional {
	private:
		bool present;
		uninitialized<T> storage;

		template <typename... Tn>
		void place(Tn&&... argn) {
			assert(!valid());
			unchecked_place(std::forward<Tn>(argn)...);
		}

		template <typename... Tn>
		void unchecked_place(Tn&&... argn) {
			::new(std::addressof(storage)) T(std::forward<Tn>(argn)...);
			present = true;
		}

		void destroy() {
			assert(valid());
			unchecked_destroy();
		}

		void unchecked_destroy() {
			get().~T();
			present = false;
		}

	public:

		optional() : optional(nullopt) {

		}

		optional(nullopt_t) : present(false) {

		}

		template <typename ...Tn>
		explicit optional(in_place_t, Tn&&... argn) {
			unchecked_place(std::forward<Tn>(argn)...);
		}

		optional(const T& t) {
			unchecked_place(t);
		}

		optional(T&& t) {
			unchecked_place(std::move(t));
		}

		optional(const optional& that) : present(false) {
			if (that.valid())
				unchecked_place(*that);
		}

		optional(optional&& that) : present(false) {
			if (that.valid())
				unchecked_place(std::move(*that));
		}

		optional& operator=(nullopt_t) {
			if (valid())
				unchecked_destroy();
			return *this;
		}

		optional& operator=(T&& right) {
			if (valid())
				unchecked_destroy();
			unchecked_place(std::move(right));
			return *this;
		}

		optional& operator=(const T& right) {
			if (valid())
				unchecked_destroy();
			unchecked_place(right);
			return *this;
		}

		optional& operator=(const optional& that) {
			if (std::addressof(that) == this)
				return *this;
			if (valid() && that.valid())
				**this = *that;
			else if (valid())
				unchecked_destroy();
			else if (that.valid())
				place(*that);
			else
				present = false;

			return *this;
		}

		optional& operator=(optional&& that) {
			if (std::addressof(that) == this)
				return *this;
			if (valid() && that.valid())
				**this = std::move(*that);
			else if (valid())
				unchecked_destroy();
			else if (that.valid())
				unchecked_place(std::move(*that));
			else
				present = false;

			return *this;
		}

		void swap(optional& other) {
			if (other.valid() && valid()) {
				swap(**this, *other);
			}
			else if (!other.valid() && !valid()) {
				return;
			}
			optional& source = other ? *this : other;
			optional& target = other ? other : *this;
			target.unchecked_place(std::move(*source));
			source.unchecked_destroy();
		}

		~optional() {
			if (valid())
				unchecked_destroy();
		}

		T& get() {
			return *static_cast<T*>(static_cast<void*>(std::addressof(storage)));
		}

		const T& get() const {
			return *static_cast<T const*>(static_cast<void const*>(std::addressof(storage)));
		}

		T get_or(T defaultvalue) {
			if (valid())
				return get();
			return std::move(defaultvalue);
		}

		T get_or(T defaultvalue) const {
			if (valid())
				return get();
			return std::move(defaultvalue);
		}

		T& operator*() & {
			return get();
		}

		T&& operator*() && {
			return std::move(get());
		}

		const T& operator*() const & {
			return get();
		}

		T* operator->() {
			return std::addressof(get());
		}

		const T* operator->() const {
			return std::addressof(get());
		}

		bool valid() const {
			return present;
		}

		explicit operator bool() const {
			return valid();
		}

	};

	template <typename T>
	struct optional<T&> {
	private:
		typedef meta::unqualified_t<T> Tu;
		typedef std::remove_reference_t<T> Tc;
		struct storage_t {
			T* reference_val;
			storage_t() : reference_val(nullptr) { }
			storage_t(T& r) : storage_t(std::addressof(r)) { }
			storage_t(T* r) : reference_val(r) { }
		} storage;

		template <typename... Tn>
		void place(Tn&&... argn) {
			assert(!valid());
			unchecked_place(std::forward<Tn>(argn)...);
		}

		template <typename... Tn>
		void unchecked_place(Tn&&... argn) {
			storage = storage_t(std::forward<Tn>(argn)...);
		}

		void destroy() {
			assert(valid());
			unchecked_destroy();
		}

		void unchecked_destroy() {
			storage.~storage_t();
		}

	public:

		optional() : optional(nullopt) {

		}

		optional(nullopt_t) : storage(nullptr) {

		}

		optional(T& t) : storage(t) {

		}

		optional(T* t) : storage(t) {

		}

		optional(optional<Tu>& t) : optional(t ? std::addressof(t.get()) : nullptr) {

		}

		optional(const std::reference_wrapper<Tu>& t) : optional(std::addressof(t.get())) {

		}

		template <typename C = T, typename = std::enable_if_t<std::is_const<C>::value>>
		optional(const std::reference_wrapper<Tc>& t) : optional(std::addressof(t.get())) {

		}

		optional(const optional& that) : storage(that.valid() ? &that.get() : nullptr) {

		}

		optional(optional&& that) : storage(that.valid() ? &that.get() : nullptr) {

		}

		optional& operator=(T& value) {
			if (valid())
				unchecked_destroy();
			unchecked_place(value);
			return *this;
		}

		optional& operator=(T* value) {
			if (valid())
				unchecked_destroy();
			if (value == nullptr) {
				return *this;
			}
			unchecked_place(value);
			return *this;
		}

		optional& operator=(const std::reference_wrapper<Tu>& value) {
			return operator=(value.get());
		}

		template <typename C = T, typename = std::enable_if_t<std::is_const<C>::value>>
		optional& operator=(const std::reference_wrapper<Tc>& value) {
			return operator=(std::addressof(value.get()));
		}

		optional& operator=(const optional& value) {
			if (!value.valid())
				return operator=(nullopt);
			return operator=(std::addressof(value.get()));
		}

		optional& operator=(optional&& value) {
			if (!value.valid())
				return operator=(nullopt);
			return operator=(std::addressof(value.get()));
		}

		optional& operator=(nullopt_t) {
			if (valid())
				unchecked_destroy();
			return *this;
		}

		~optional() {
			if (valid())
				unchecked_destroy();
		}

		T& get() {
			return *storage.reference_val;
		}

		const T& get() const {
			return *storage.reference_val;
		}

		T get_or(T defaultvalue) {
			if (valid())
				return get();
			return std::move(defaultvalue);
		}

		T get_or(T defaultvalue) const {
			if (valid())
				return get();
			return std::move(defaultvalue);
		}

		T& operator*() {
			return get();
		}

		const T& operator*() const {
			return get();
		}

		T* operator->() {
			return std::addressof(get());
		}

		const T* operator->() const {
			return std::addressof(get());
		}

		bool valid() const {
			return storage.reference_val != nullptr;
		}

		explicit operator bool() const {
			return valid();
		}

	};

}
