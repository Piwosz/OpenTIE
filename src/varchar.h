/*
 * varchar.h
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#ifndef SRC_VARCHAR_H_
#define SRC_VARCHAR_H_

#include <cstring>
#include <cassert>
#include <string>
#include <type_traits>
#include <array>

namespace tie {

template<std::size_t N>
struct Varchar {
	typedef Varchar<N> varchar_type;

	enum {
		max_length = N
	};

//	template<std::size_t T>
//	struct size_wrapper {
//		enum {
//			value = T
//		};
//	};

	std::array<char, N> data;

	Varchar() {
		std::memset(data.data(), 0, max_length);
	}

	Varchar(const char * rhs) {
		std::strncpy(data.data(), rhs, max_length);
	}

	Varchar(const varchar_type & rhs) {
		assert(this != &rhs);
		std::strncpy(data.data(), rhs.data.data(), max_length);
	}

	template<std::size_t T>
	Varchar(const Varchar<T> & rhs) {
		std::strncpy(data.data(), rhs.data.data(),
			std::conditional<N<T, Varchar<N>, Varchar<T>>::type::max_length);
	}

	/*
	 * In memory size.
	 */
	constexpr std::size_t size() const {
		return N;
	}

	/*
	 * Actual string length.
	 */
	std::size_t length() const {
		return ::strnlen(data.data(), max_length);
	}

	/*
	 * Is empty?
	 */
	bool emtpy() const {
		return (data[0] == '\0');
	}

	/*
	 * Comparsion method
	 */

	template<std::size_t T>
	int Compare(const Varchar<T> & rhs) const {
		return ::strncmp(data.data(), rhs.data.data(),
				std::conditional<N<T,Varchar<N>,Varchar<T>>::type::max_length);
	}

	/*
	 * Assignment operator
	 */
	varchar_type & operator=(const char * rhs) {
		assert(data.data() != rhs);
		std::strncpy(data.data(), rhs, max_length);
		return *this;
	}

	/*
	 * Array access
	 */
	char operator[](std::size_t index) {
		assert(index < max_length);
		if (max_length <= index) throw std::runtime_error("index error");
		return data[index];
	}

	std::string String() const {
		return std::string(data.data(), length());
	}
};

template<std::size_t N, std::size_t T>
bool operator==(const Varchar<N> & lhs, const Varchar<T> & rhs) {
	return (lhs.Compare(rhs) == 0);
}

template<std::size_t N, std::size_t T>
bool operator!=(const Varchar<N> & lhs, const Varchar<T> & rhs) {
	return !(lhs == rhs);
}

namespace unit {
bool test_varchar();
};
};

#endif /* SRC_VARCHAR_H_ */
