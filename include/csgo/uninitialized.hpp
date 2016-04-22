#pragma once

#include <type_traits>
#include <cstddef>

namespace csgo {

	template <std::size_t size, std::size_t align>
	struct raw_storage {
		typedef typename std::aligned_storage<size, align>::type buffer_t;
		buffer_t buffer;

		template <typename T>
		T& get(std::size_t n) {
			return *static_cast<T*>(static_cast<void*>(static_cast<byte*>(static_cast<void*>(std::addressof(this->buffer))) + n));
		}

		template <typename T>
		const T& get(std::size_t n) const {
			return *static_cast<const T*>(static_cast<const void*>(static_cast<const byte*>(static_cast<const void*>(std::addressof(this->buffer))) + n));
		}

		template <typename T, std::size_t n = 0>
		T& get() {
			return *static_cast<T*>(static_cast<void*>(static_cast<byte*>(static_cast<void*>(std::addressof(this->buffer))) + n));
		}

		template <typename T, std::size_t n = 0>
		const T& get() const {
			return *static_cast<const T*>(static_cast<const void*>(static_cast<const byte*>(static_cast<const void*>(std::addressof(this->buffer))) + n));
		}
	};

	template <typename T, std::size_t type_size = sizeof(T), std::size_t type_align = std::alignment_of<T>::value>
	struct uninitialized {
		typedef raw_storage<type_size, type_align> storage_t;
		storage_t res;

		template <typename... Tn>
		void construct(Tn&&... argn) {
			new (std::addressof(get()))T(std::forward<Tn>(argn)...);
		}

		template <typename... Tn>
		void reconstruct(Tn&&... argn) {
			destruct();
			construct(std::forward<Tn>(argn)...);
		}

		T&& move() {
			return std::move(get());
		}

		T& get() & {
			return res.template get<T>();
		}

		const T& get() const & {
			return res.template get<T>();
		}

		T&& get() && {
			return std::move(res.template get<T>());
		}

		T& operator*() {
			return get();
		}

		const T& operator*() const {
			return get();
		}

		operator T && () {
			return move();
		}

		operator T& () {
			return get();
		}

		operator const T& () const {
			return get();
		}

		T* operator->() {
			return std::addressof(get());
		}

		const T* operator->() const {
			return std::addressof(get());
		}

		void destruct() {
			get().~T();
		}
	};

}
