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

namespace pxg::math
{

#pragma region Constructors

	template<typename T>
	constexpr circle<T>::circle() noexcept
		: center{ 0, 0 }
		, radius(0)
	{
	}

	template<typename T>
	constexpr circle<T>::circle(T x, T y, T radius) noexcept
		: center{ x, y }
		, radius(radius)
	{
	}

	template<typename T>
	constexpr circle<T>::circle(const vector2<T>& center, T radius) noexcept
		: center(center)
		, radius(radius)
	{
	}

	template<typename T>
	template<typename U>
	constexpr circle<T>::circle(const circle<U>& circle) noexcept
		: center(static_cast<vector2<T>>(circle.center))
		, radius(static_cast<T>(circle.radius))
	{
	}

#pragma endregion
#pragma region Operations
	
	template<typename T>
	[[nodiscard]] constexpr T circle<T>::diameter() const noexcept
	{
		return radius * T(2);
	}

	template<typename T>
	[[nodiscard]] constexpr T circle<T>::area() const noexcept
	{
		return std::numbers::pi_v<T> *radius * radius;
	}

	template<typename T>
	[[nodiscard]] constexpr bool circle<T>::empty() const noexcept
	{
		return radius <= T(0);
	}

	template<typename T>
	[[nodiscard]] constexpr bool circle<T>::null() const noexcept
	{
		return empty() && (center.x == T(0) && center.y == T(0));
	}

#pragma endregion

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const circle<T>& circle) noexcept
	{
		return stream << "circle(" << circle.center << ", " << circle.radius << ")";
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator==(const circle<T>& lhs, const circle<T>& rhs) noexcept
	{
		return (lhs.center == rhs.center) && (lhs.radius == rhs.radius);
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator!=(const circle<T>& lhs, const circle<T>& rhs) noexcept
	{
		return !(lhs == rhs);
	}

}