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

	template<std::size_t N>
	constexpr matrix_stack<N>::matrix_stack() noexcept
		: m_stack{ matrix3x3::identity() }
		, m_current(0)
	{
	}

#pragma endregion
#pragma region Operations

	template<std::size_t N>
	[[nodiscard]] constexpr const matrix3x3& matrix_stack<N>::top() const noexcept
	{
		return m_stack[m_current];
	}

	template<std::size_t N>
	[[nodiscard]] constexpr std::size_t matrix_stack<N>::size() const noexcept
	{
		return m_current + 1;
	}

	template<std::size_t N>
	void matrix_stack<N>::pop() noexcept
	{
		if (m_current > 0)
		{
			m_current--;
		}
	}

	template<std::size_t N>
	void matrix_stack<N>::push() noexcept
	{
		if (m_current + 1 < N)
		{
			m_current++;
			m_stack[m_current] = m_stack[m_current - 1];
		}
	}

	template<std::size_t N>
	void matrix_stack<N>::identity() noexcept
	{
		m_stack[m_current] = matrix3x3::identity();
	}

	template<std::size_t N>
	void matrix_stack<N>::load(const matrix3x3& matrix) noexcept
	{
		m_stack[m_current] = matrix;
	}

	template<std::size_t N>
	void matrix_stack<N>::multiply(const matrix3x3& matrix) noexcept
	{
		m_stack[m_current] = m_stack[m_current] * matrix;
	}

	template<std::size_t N>
	void matrix_stack<N>::rotate(std::float_t angle, const vector2f& origin) noexcept
	{
		matrix3x3 matrix;
		matrix.rotate(angle, origin);
		multiply(matrix);
	}

	template<std::size_t N>
	void matrix_stack<N>::scale(std::float_t factor, const vector2f& origin) noexcept
	{
		matrix3x3 matrix;
		matrix.scale(factor, origin);
		multiply(matrix);
	}

	template<std::size_t N>
	void matrix_stack<N>::translate(const vector2f& translation) noexcept
	{
		matrix3x3 matrix;
		matrix.translate(translation);
		multiply(matrix);
	}

#pragma endregion

	template<std::size_t N>
	std::ostream& operator<<(std::ostream& stream, const matrix_stack<N>& stack) noexcept
	{
		stream << "matrix_stack(\n";

		for (const auto& matrix : stack.m_stack)
		{
			stream << "\t" << matrix << "\n";
		}

		stream << ")\n";

		return stream;
	}

}