/**
 *
 * libretro
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 CHOQUET Olivier
 *
 * This software is a computer program whose purpose is to provide
 * modern C++ cross-platform 2D game engine.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#pragma once

#ifndef __PIXENGEO_MATH_H_INCLUDED__
#error "Do not include this file directly, include <pixengeo/math.h> instead."
#endif

namespace pxg::math
{

	template<typename T>
	struct vector2
	{
		static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

#pragma region Constructors

		constexpr vector2() noexcept;
		constexpr vector2(T x, T y) noexcept;
		template<typename U>
		constexpr explicit vector2(const vector2<U>& vector) noexcept;
		~vector2() = default;

#pragma endregion
#pragma region Attributes

		T x;
		T y;

#pragma endregion

	};

	using vector2f = vector2<std::float_t>;
	using vector2d = vector2<std::double_t>;
	using vector2i = vector2<std::int32_t>;
	using vector2sz = vector2<std::size_t>;

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const vector2<T>& vector) noexcept;

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator+(const vector2<T>& lhs, const vector2<T>& rhs) noexcept;	

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator-(const vector2<T>& rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator-(const vector2<T>& lhs, const vector2<T>& rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator*(const vector2<T>& lhs, T rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator*(T lhs, const vector2<T>& rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator/(const vector2<T>& lhs, T rhs) noexcept;

	template<typename T>
	constexpr vector2<T>& operator+=(vector2<T>& lhs, const vector2<T>& rhs) noexcept;

	template<typename T>
	constexpr vector2<T>& operator-=(vector2<T>& lhs, const vector2<T>& rhs) noexcept;

	template<typename T>
	constexpr vector2<T>& operator*=(vector2<T>& lhs, T rhs) noexcept;

	template<typename T>
	constexpr vector2<T>& operator/=(vector2<T>& lhs, T rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr bool operator==(const vector2<T>& lhs, const vector2<T>& rhs) noexcept;

	template<typename T>
	[[nodiscard]] constexpr bool operator!=(const vector2<T>& lhs, const vector2<T>& rhs) noexcept;

}

#include "vector2.inl"