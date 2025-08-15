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

#include "pch.h"
#include "window_impl.h"

namespace pxg::gfx
{

#pragma region Constructors

	window::impl::impl(std::string_view title, std::size_t width, std::size_t height, bool fullscreen, bool resizable, error_callback_t callback)
		: m_window(nullptr)
	{
		BOOST_ASSERT_MSG(width >= 0, "Window width must be greater than zero");
		BOOST_ASSERT_MSG(height >= 0, "Window height must be greater than zero");
		BOOST_ASSERT_MSG(callback, "A callback must be set");

		glfwSetErrorCallback(callback);

		if (!glfwInit())
		{
			throw std::runtime_error("[GLFW] Unable to initialize GLFW");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, resizable);

		m_window = glfwCreateWindow(static_cast<int>(width),
									static_cast<int>(height),
									title.data(),
									fullscreen ? glfwGetPrimaryMonitor() : nullptr,
									nullptr);
		if (!m_window)
		{
			throw std::runtime_error("[GLFW] Unable to create window");
		}

		glfwMakeContextCurrent(m_window);
	}

	window::impl::~impl()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

#pragma endregion
#pragma region Operations

	std::string_view window::impl::glfw_version() const noexcept
	{
		static thread_local const std::string version_cache =
			std::format("{}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

		return version_cache;
	}

	void window::impl::poll_events() const noexcept
	{
		glfwPollEvents();
	}

	bool window::impl::should_close() const noexcept
	{
		return glfwWindowShouldClose(m_window) == GLFW_TRUE;
	}

	void window::impl::swap_buffers() noexcept
	{
		glfwSwapBuffers(m_window);
	}

#pragma endregion

}