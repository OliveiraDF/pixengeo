/**
 *
 * pixengeo
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

namespace pxg::math
{

#pragma region Constructors

	template<typename T>
	constexpr vector2<T>::vector2() noexcept
		: x(0)
		, y(0)
	{
	}

	template<typename T>
	constexpr vector2<T>::vector2(T x, T y) noexcept
		: x(x)
		, y(y)
	{
	}

	template<typename T>
	template<typename U>
	constexpr vector2<T>::vector2(const vector2<U>& vector) noexcept
		: x(static_cast<T>(vector.x))
		, y(static_cast<T>(vector.y))
	{
	}

#pragma endregion

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const vector2<T>& vector) noexcept
	{
		return stream << "vector2(" << vector.x << ", " << vector.y << ")";
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator+(const vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator-(const vector2<T>& rhs) noexcept
	{
		return vector2<T>(-rhs.x, -rhs.y);
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator-(const vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator*(const vector2<T>& lhs, T rhs) noexcept
	{
		return vector2<T>(lhs.x * rhs, lhs.y * rhs);
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator*(T lhs, const vector2<T>& rhs) noexcept
	{
		return vector2<T>(rhs.x * lhs, rhs.y * lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr vector2<T> operator/(const vector2<T>& lhs, T rhs) noexcept
	{
		return vector2<T>(lhs.x / rhs, lhs.y / rhs);
	}

	template<typename T>
	constexpr vector2<T>& operator+=(vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;

		return lhs;
	}

	template<typename T>
	constexpr vector2<T>& operator-=(vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;

		return lhs;
	}

	template<typename T>
	constexpr vector2<T>& operator*=(vector2<T>& lhs, T rhs) noexcept
	{
		lhs.x *= rhs;
		lhs.y *= rhs;

		return lhs;
	}

	template<typename T>
	constexpr vector2<T>& operator/=(vector2<T>& lhs, T rhs) noexcept
	{
		lhs.x /= rhs;
		lhs.y /= rhs;

		return lhs;
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator==(const vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator!=(const vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y);
	}


}