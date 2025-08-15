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

	constexpr matrix3x3::matrix3x3() noexcept
		: m_matrix{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		}
	{
	}

	constexpr matrix3x3::matrix3x3(std::float_t m00, std::float_t m01, std::float_t m02,
								   std::float_t m10, std::float_t m11, std::float_t m12,
								   std::float_t m20, std::float_t m21, std::float_t m22) noexcept
		: m_matrix{
			m00, m10, 0.f, m20,
			m01, m11, 0.f, m21,
			0.f, 0.f, 1.f, 0.f,
			m02, m12, 0.f, m22
		}
	{
	}

#pragma endregion
#pragma region Operations

	[[nodiscard]] constexpr std::span<const std::float_t> matrix3x3::data() const noexcept
	{
		return std::span(m_matrix.data(), m_matrix.size());
	}

	[[nodiscard]] constexpr matrix3x3 matrix3x3::inverse() const noexcept
	{
		const std::float_t determinant = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
			m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
			m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

		if (determinant == 0.f)
		{
			return identity();
		}

		const std::float_t inverse_determinant = 1.f / determinant;

		return matrix3x3(
			(m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) * inverse_determinant,
			-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) * inverse_determinant,
			(m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) * inverse_determinant,
			-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) * inverse_determinant,
			(m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) * inverse_determinant,
			-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) * inverse_determinant,
			(m_matrix[7] * m_matrix[1] - m_matrix[3] * m_matrix[5]) * inverse_determinant,
			-(m_matrix[7] * m_matrix[0] - m_matrix[3] * m_matrix[4]) * inverse_determinant,
			(m_matrix[5] * m_matrix[0] - m_matrix[1] * m_matrix[4]) * inverse_determinant
		);
	}

	[[nodiscard]] constexpr vector2f matrix3x3::transform(std::float_t x, std::float_t y) const noexcept
	{
		return vector2f(
			m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
			m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]
		);
	}

	[[nodiscard]] constexpr vector2f matrix3x3::transform(const vector2f& v) const noexcept
	{
		return transform(v.x, v.y);
	}

	[[nodiscard]] constexpr floatrect matrix3x3::transform(const floatrect& rect) const noexcept
	{
		const vector2f points[] =
		{
			transform(rect.left(), rect.top()),
			transform(rect.left(), rect.bottom()),
			transform(rect.right(), rect.top()),
			transform(rect.right(), rect.bottom())
		};

		std::float_t left = points[0].x, right = points[0].x;
		std::float_t top = points[0].y, bottom = points[0].y;

		for (const auto& point : points)
		{
			if (point.x < left)
			{
				left = point.x;
			}
			else if (point.x > right)
			{
				right = point.x;
			}
			if (point.y < top)
			{
				top = point.y;
			}
			else if (point.y > bottom)
			{
				bottom = point.y;
			}
		}

		return floatrect(left, top, right - left, bottom - top);
	}

	constexpr matrix3x3& matrix3x3::combine(const matrix3x3& other) noexcept
	{
		const std::float_t* a = m_matrix.data();
		const std::float_t* b = other.m_matrix.data();

		*this = matrix3x3(
			a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
			a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
			a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
			a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
			a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
			a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
			a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
			a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
			a[3] * b[12] + a[7] * b[13] + a[15] * b[15]
		);

		return *this;
	}

	constexpr matrix3x3& matrix3x3::translate(std::float_t x, std::float_t y) noexcept
	{
		const matrix3x3 translation_matrix(
			1.0f, 0.0f, x,
			0.0f, 1.0f, y,
			0.0f, 0.0f, 1.0f
		);

		return combine(translation_matrix);
	}

	constexpr matrix3x3& matrix3x3::translate(const vector2f& v) noexcept
	{
		return translate(v.x, v.y);
	}

	inline matrix3x3& matrix3x3::rotate(std::float_t angle) noexcept
	{
		const std::float_t radians = angle * (std::numbers::pi_v<std::float_t> / 180.f);
		const std::float_t cos_angle = std::cos(radians);
		const std::float_t sin_angle = std::sin(radians);

		const matrix3x3 rotation_matrix(
			cos_angle, -sin_angle, 0.f,
			sin_angle, cos_angle, 0.f,
			0.f, 0.f, 1.f
		);

		return combine(rotation_matrix);
	}

	inline matrix3x3& matrix3x3::rotate(std::float_t angle, std::float_t x, std::float_t y) noexcept
	{
		const std::float_t radians = angle * (std::numbers::pi_v<std::float_t> / 180.f);
		const std::float_t cos_angle = std::cos(radians);
		const std::float_t sin_angle = std::sin(radians);

		const matrix3x3 rotation_matrix(
			cos_angle, -sin_angle, x * (1.f - cos_angle) + y * sin_angle,
			sin_angle, cos_angle, y * (1.f - cos_angle) - x * sin_angle,
			0.f, 0.f, 1.f
		);

		return combine(rotation_matrix);
	}

	inline matrix3x3& matrix3x3::rotate(std::float_t angle, const vector2f& v) noexcept
	{
		return rotate(angle, v.x, v.y);
	}

	constexpr matrix3x3& matrix3x3::scale(std::float_t x, std::float_t y) noexcept
	{
		const matrix3x3 scale_matrix(
			x, 0.f, 0.f,
			0.f, y, 0.f,
			0.f, 0.f, 1.f
		);

		return combine(scale_matrix);
	}

	constexpr matrix3x3& matrix3x3::scale(std::float_t factor) noexcept
	{
		return scale(factor, factor);
	}

	constexpr matrix3x3& matrix3x3::scale(std::float_t factor, const vector2f& center) noexcept
	{
		return scale(factor, factor, center.x, center.y);
	}

	constexpr matrix3x3& matrix3x3::scale(std::float_t x, std::float_t y, std::float_t center_x, std::float_t center_y) noexcept
	{
		const matrix3x3 scale_matrix(
			x, 0.f, center_x * (1.f - x),
			0.f, y, center_y * (1.f - y),
			0.f, 0.f, 1.f
		);

		return combine(scale_matrix);
	}

	constexpr matrix3x3& matrix3x3::scale(std::float_t x, std::float_t y, const vector2f& center) noexcept
	{
		return scale(x, y, center.x, center.y);
	}

	constexpr matrix3x3& matrix3x3::scale(const vector2f& factors) noexcept
	{
		return scale(factors.x, factors.y);
	}

	constexpr matrix3x3& matrix3x3::scale(const vector2f& factors, const vector2f& center) noexcept
	{
		return scale(factors.x, factors.y, center.x, center.y);
	}

#pragma endregion

	inline std::ostream& operator<<(std::ostream& stream, const matrix3x3& matrix) noexcept
	{
		return stream << "matrix3x3("
			<< matrix.data()[0] << ", " << matrix.data()[1] << ", " << matrix.data()[2] << ", "
			<< matrix.data()[4] << ", " << matrix.data()[5] << ", " << matrix.data()[6] << ", "
			<< matrix.data()[8] << ", " << matrix.data()[9] << ", " << matrix.data()[10] << ")";
	}

	[[nodiscard]] constexpr matrix3x3 operator*(const matrix3x3& lhs, const matrix3x3& rhs) noexcept
	{
		return matrix3x3(lhs).combine(rhs);
	}

	[[nodiscard]] constexpr vector2f operator*(const matrix3x3& lhs, const vector2f& rhs) noexcept
	{
		return lhs.transform(rhs);
	}

	constexpr matrix3x3& operator*=(matrix3x3& lhs, const matrix3x3& rhs) noexcept
	{
		return lhs.combine(rhs);
	}

	[[nodiscard]] constexpr bool operator==(const matrix3x3& lhs, const matrix3x3& rhs) noexcept
	{
		std::span<const std::float_t> a = lhs.data();
		std::span<const std::float_t> b = rhs.data();

		return ((a[0] == b[0]) && (a[1] == b[1]) && (a[3] == b[3]) &&
				(a[4] == b[4]) && (a[5] == b[5]) && (a[7] == b[7]) &&
				(a[12] == b[12]) && (a[13] == b[13]) && (a[15] == b[15]));
	}

	[[nodiscard]] constexpr bool operator!=(const matrix3x3& lhs, const matrix3x3& rhs) noexcept
	{
		return !(lhs == rhs);
	}

}