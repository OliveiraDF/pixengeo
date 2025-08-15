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
#include "engine_impl.h"
#include "command_line_info.h"

namespace pxg::core
{

#pragma region Constructors

	engine::impl::impl()
		: m_project(nullptr, destroy_project_func())
	{
	}

	engine::impl::~impl()
	{
	}

#pragma endregion
#pragma region Operations

	int engine::impl::run(int argc, char** argv) noexcept
	{
		init_logging();

		BOOST_LOG_TRIVIAL(info) << "___________________  _______________   _________________________";
		BOOST_LOG_TRIVIAL(info) << "___  __ \\___  _/_  |/ /__  ____/__  | / /_  ____/__  ____/_  __ \\";
		BOOST_LOG_TRIVIAL(info) << "__  /_/ /__  / __    /__  __/  __   |/ /_  / __ __  __/  _  / / /";
		BOOST_LOG_TRIVIAL(info) << "_  ____/__/ /  _    | _  /___  _  /|  / / /_/ / _  /___  / /_/ / ";
		BOOST_LOG_TRIVIAL(info) << "/_/     /___/  /_/|_| /_____/  /_/ |_/  \\____/  /_____/  \\____/  engine v" PIXENGEO_VERSION;
		BOOST_LOG_TRIVIAL(info) << ""; BOOST_LOG_TRIVIAL(info) << "";

		try
		{
			const command_line_info cli = parse_command_line(argc, argv);
			if (cli.help)
			{
				return EXIT_SUCCESS;
			}

			load();

			load_module(cli.module);

			load_project(cli.project);

			main_loop(cli.title, cli.width, cli.height, cli.fullscreen, cli.resizable);
		}
		catch (const std::exception& e)
		{
			BOOST_LOG_TRIVIAL(error) << e.what();
		}

		return EXIT_SUCCESS;
	}

#pragma endregion
#pragma region Implementations

	void engine::impl::glfw_error_callback(int error_code, const char* description)
	{
		BOOST_LOG_TRIVIAL(error) << "[GLFW:" << error_code << "] " << description;
	}

	void engine::impl::gl_error_callback(int error_code, const char* description)
	{
		BOOST_LOG_TRIVIAL(warning) << "[OpenGL:" << error_code << "] " << description;
	}

	void engine::impl::init_logging() const noexcept
	{
		boost::log::add_console_log(std::clog, boost::log::keywords::format = "[%TimeStamp%] [%Severity%]: %Message%");
		boost::log::add_common_attributes();
	}

	void engine::impl::load()
	{

	}

	void engine::impl::load_module(const std::filesystem::path& module_path)
	{
		if (!std::filesystem::exists(module_path))
		{
			BOOST_LOG_TRIVIAL(warning) << "'" << module_path.c_str() << "' module doesn't exist";
			return;
		}

		if (!std::filesystem::is_regular_file(module_path))
		{
			BOOST_LOG_TRIVIAL(warning) << "'" << module_path.c_str() << "' is not a regular file";
			return;
		}

		m_module = boost::dll::shared_library(module_path.c_str(), boost::dll::load_mode::load_with_altered_search_path);

		if (!m_module.has("create_project_func") || !m_module.has("destroy_project_func"))
		{
			BOOST_LOG_TRIVIAL(warning) << "'" << module_path.c_str() << "' does not contain required functions";
			return;
		}

		auto fn_create_project = m_module.get<create_project_func>("create_project_func");
		auto fn_destroy_project = m_module.get<destroy_project_func>("destroy_project_func");

		std::unique_ptr<project, destroy_project_func> project_ptr(fn_create_project(), fn_destroy_project);

		m_project = std::move(project_ptr);
	}

	void engine::impl::load_project(const std::filesystem::path& project_path)
	{
		if (!std::filesystem::exists(project_path))
		{
			BOOST_LOG_TRIVIAL(warning) << "'" << project_path.c_str() << "' project doesn't exist";
			return;
		}

		if (!std::filesystem::is_regular_file(project_path))
		{
			BOOST_LOG_TRIVIAL(warning) << "'" << project_path.c_str() << "' is not a regular file";
			return;
		}

		boost::property_tree::ptree pt;
		std::vector<std::filesystem::path> all_tmx;

		boost::property_tree::read_json(project_path.string(), pt);

		for (const auto& entry : pt.get_child("fileStates"))
		{
			all_tmx.emplace_back(entry.first);
		}

		const auto is_not_valid_tmx = [](const std::filesystem::path& path) -> bool
			{
				const bool is_tmx = path.extension() == ".tmx";
				const bool no_forbidden_chars = 
					path.filename().string().find('$') == std::string::npos &&
					path.filename().string().find('#') == std::string::npos;
				return !(is_tmx && no_forbidden_chars);
			};

		std::erase_if(all_tmx, is_not_valid_tmx);
	}

	void engine::impl::main_loop(std::string_view title, std::size_t width, std::size_t height, bool fullscreen, bool resizable)
	{
		pxg::gfx::window window(title, width, height, fullscreen, resizable, glfw_error_callback);
		pxg::gfx::renderer renderer(gl_error_callback);

		BOOST_LOG_TRIVIAL(info) << "GLFW v" << window.glfw_version() << " successfully initialized";
		BOOST_LOG_TRIVIAL(info) << "OpenGL v3.3 Core Profile rendering mode";
		BOOST_LOG_TRIVIAL(info) << "Window successfully created";

		if (m_project)
		{
			BOOST_LOG_TRIVIAL(info) << m_project->name() << " v" << m_project->version() << " successfully loaded";
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << "Engine launched without any project";
		}

		while (!window.should_close())
		{
			window.poll_events();

			renderer.clear();

			renderer.draw_all();

			window.swap_buffers();
		}
	}

#pragma endregion

}