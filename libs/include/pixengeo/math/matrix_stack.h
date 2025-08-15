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

	template<std::size_t N>
	class matrix_stack
	{
#pragma region Constructors

	public:

		constexpr matrix_stack() noexcept;
		~matrix_stack() = default;

#pragma endregion
#pragma region Attributes

	private:

		std::size_t m_current;
		std::array<matrix3x3, N> m_stack;

#pragma endregion
#pragma region Operations

	public:

		[[nodiscard]] constexpr const matrix3x3& top() const noexcept;
		[[nodiscard]] constexpr std::size_t size() const noexcept;
		void pop() noexcept;
		void push() noexcept;
		void identity() noexcept;
		void load(const matrix3x3& matrix) noexcept;
		void multiply(const matrix3x3& matrix) noexcept;
		void rotate(std::float_t angle, const vector2f& origin) noexcept;
		void scale(std::float_t factor, const vector2f& origin) noexcept;
		void translate(const vector2f& translation) noexcept;

#pragma endregion

		friend std::ostream& operator<<(std::ostream& stream, const matrix_stack<N>& stack) noexcept;

	};

	using matrix_stack_8 = matrix_stack<8>;
	using matrix_stack_16 = matrix_stack<16>;
	using matrix_stack_32 = matrix_stack<32>;

	template<std::size_t N>
	std::ostream& operator<<(std::ostream& stream, const matrix_stack<N>& stack) noexcept;

}

#include "matrix_stack.inl"