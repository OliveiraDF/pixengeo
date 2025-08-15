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
	constexpr line<T>::line() noexcept
		: start{ 0, 0 }
		, end{ 0, 0 }
	{
	}

	template<typename T>
	constexpr line<T>::line(const vector2<T>& start, const vector2<T>& end) noexcept
		: start(start)
		, end(end)
	{
	}

	template<typename T>
	template<typename U>
	constexpr line<T>::line(const line<U>& line) noexcept
		: start{ static_cast<T>(line.start) }
		, end{ static_cast<T>(line.end) }
	{
	}

#pragma endregion
#pragma region Operations

	template<typename T>
	[[nodiscard]] constexpr vector2<T> line<T>::center() const noexcept
	{
		return { (start.x + end.x) / T(2), (start.y + end.y) / T(2) };
	}

	template<typename T>
	[[nodiscard]] constexpr T line<T>::angle() const noexcept
	{
		return std::atan2(end.y - start.y, end.x - start.x);
	}

#pragma endregion

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const line<T>& line) noexcept
	{
		return stream << "line(" << line.start.x << ", " << line.start.y << ", " << line.end.x << ", " << line.end.y << ")";
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator==(const line<T>& left, const line<T>& right) noexcept
	{
		return (left.start.x == right.start.x) && (left.start.y == right.start.y) && (left.end.x == right.end.x) && (left.end.y == right.end.y);
	}

	template<typename T>
	[[nodiscard]] constexpr bool operator!=(const line<T>& left, const line<T>& right) noexcept
	{
		return !(left == right);
	}

}