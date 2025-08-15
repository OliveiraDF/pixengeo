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

#pragma once

#ifndef __PIXENGEO_GRAPHICS_H_INCLUDED__
#error "Do not include this file directly, include <pixengeo/graphics.h> instead."
#endif

namespace pxg::gfx
{

	class PIXENGEO_GRAPHICS_API window
	{
	public:

		typedef void (*error_callback_t)(int error_code, const char* description);

#pragma region Constructors

	public:

		window(std::string_view title, std::size_t width, std::size_t height, bool fullscreen, bool resizable, error_callback_t callback);
		~window();
		window(const window&) = delete;
		window& operator=(const window&) = delete;

#pragma endregion
#pragma region Attributes

	private:

		class impl;
		std::unique_ptr<impl> m_pimpl;

#pragma endregion
#pragma region Operations

	public:

		std::string_view glfw_version() const noexcept;
		void poll_events() const noexcept;
		bool should_close() const noexcept;
		void swap_buffers() noexcept;

#pragma endregion
	};

}