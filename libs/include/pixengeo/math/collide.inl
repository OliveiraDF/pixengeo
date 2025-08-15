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

	template<typename T>
	[[nodiscard]] constexpr bool collide(const vector2<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return lhs == rhs;
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const vector2<T>& lhs, const line<T>& rhs) noexcept
	{
		const T d1 = euclidian_distance(rhs.start, lhs);
		const T d2 = euclidian_distance(rhs.end, lhs);
		const T line_length = euclidian_distance(rhs.start, rhs.end);

		return (d1 + d2) <= (line_length + std::numeric_limits<T>::epsilon());
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const line<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const line<T>& lhs, const line<T>& rhs) noexcept
	{
		const T determinant = (lhs.end.x - lhs.start.x) * (rhs.end.y - rhs.start.y) -
			(lhs.end.y - lhs.start.y) * (rhs.end.x - rhs.start.x);
		if (determinant == T(0))
		{
			return false;
		}

		const T lambda = ((rhs.start.x - lhs.start.x) * (rhs.end.y - rhs.start.y) -
						  (rhs.start.y - lhs.start.y) * (rhs.end.x - rhs.start.x)) / determinant;

		const T gamma = ((rhs.start.x - lhs.start.x) * (lhs.end.y - lhs.start.y) -
						 (rhs.start.y - lhs.start.y) * (lhs.end.x - lhs.start.x)) / determinant;

		return (lambda >= T(0) && lambda <= T(1)) && (gamma >= T(0) && gamma <= T(1));
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const vector2<T>& lhs, const rect<T>& rhs) noexcept
	{
		return (lhs.x >= rhs.left() && lhs.x <= rhs.right() &&
				lhs.y >= rhs.top() && lhs.y <= rhs.bottom());
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const rect<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const line<T>& lhs, const rect<T>& rhs) noexcept
	{
		if (collide(lhs.start, rhs) || collide(lhs.end, rhs))
		{
			return true;
		}

		line<T> top_edge{ {rhs.left(), rhs.top()}, {rhs.right(), rhs.top()} };
		line<T> bottom_edge{ {rhs.left(), rhs.bottom()}, {rhs.right(), rhs.bottom()} };
		line<T> left_edge{ {rhs.left(), rhs.top()}, {rhs.left(), rhs.bottom()} };
		line<T> right_edge{ {rhs.right(), rhs.top()}, {rhs.right(), rhs.bottom()} };

		return collide(lhs, top_edge) || collide(lhs, bottom_edge) ||
			collide(lhs, left_edge) || collide(lhs, right_edge);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const rect<T>& lhs, const line<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const rect<T>& lhs, const rect<T>& rhs) noexcept
	{
		return !(lhs.right() < rhs.left() || lhs.left() > rhs.right() ||
				 lhs.bottom() < rhs.top() || lhs.top() > rhs.bottom());
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const circle<T>& lhs, const vector2<T>& rhs) noexcept
	{
		return euclidian_distance(lhs.center, rhs) <= lhs.radius;
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const vector2<T>& lhs, const circle<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const line<T>& lhs, const circle<T>& rhs) noexcept
	{
		const T d1 = euclidian_distance(lhs.start, rhs.center);
		const T d2 = euclidian_distance(lhs.end, rhs.center);
		const T line_length = euclidian_distance(lhs.start, lhs.end);
		if (d1 <= rhs.radius || d2 <= rhs.radius)
		{
			return true;
		}

		const T distance_to_line = std::abs((lhs.end.y - lhs.start.y) * rhs.center.x -
											(lhs.end.x - lhs.start.x) * rhs.center.y +
											lhs.end.x * lhs.start.y - lhs.end.y * lhs.start.x) /
								   line_length;

		return distance_to_line <= rhs.radius;
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const circle<T>& lhs, const line<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const circle<T>& lhs, const rect<T>& rhs) noexcept
	{
		const T closest_x = std::clamp(lhs.center.x, rhs.left(), rhs.right());
		const T closest_y = std::clamp(lhs.center.y, rhs.top(), rhs.bottom());
		const T distance_x = lhs.center.x - closest_x;
		const T distance_y = lhs.center.y - closest_y;
		return (distance_x * distance_x + distance_y * distance_y) <= (lhs.radius * lhs.radius);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const rect<T>& lhs, const circle<T>& rhs) noexcept
	{
		return collide(rhs, lhs);
	}

	template<typename T>
	[[nodiscard]] constexpr bool collide(const circle<T>& lhs, const circle<T>& rhs) noexcept
	{
		return euclidian_distance(lhs.center, rhs.center) <= (lhs.radius + rhs.radius);
	}

}