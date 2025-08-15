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

namespace pxg::core
{

	struct command_line_info
	{		
		static constexpr std::size_t default_width = 640;
		static constexpr std::size_t default_height = 480;
		static constexpr const char* default_title = "NO WINDOW TITLE";

		bool help = false; 
		std::filesystem::path module;
		std::filesystem::path project;
		std::string title;
		std::size_t width = default_width;
		std::size_t height = default_height;
		bool fullscreen = false;
		bool resizable = false;
	};

	inline command_line_info parse_command_line(int argc, char** argv)
	{
		command_line_info cli;

		boost::program_options::options_description options("Allowed options");
		options.add_options()
			("help,h", boost::program_options::bool_switch(&cli.help), "Show help message")
			("module,m", boost::program_options::value<std::filesystem::path>(&cli.module)->required(), "Path to the game module")
			("project,p", boost::program_options::value<std::filesystem::path>(&cli.project)->required(), "Path to the tiled map editor project file")
			("title,t", boost::program_options::value<std::string>(&cli.title)->default_value(command_line_info::default_title), "Window title")
			("width,w", boost::program_options::value<std::size_t>(&cli.width)->default_value(command_line_info::default_width), "Window width")
			("height,h", boost::program_options::value<std::size_t>(&cli.height)->default_value(command_line_info::default_height), "Window height")
			("fullscreen,f", boost::program_options::bool_switch(&cli.fullscreen)->default_value(false), "Enable fullscreen mode")
			("resizable,r", boost::program_options::bool_switch(&cli.resizable)->default_value(false), "Enable resizable window");

		boost::program_options::variables_map variables;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), variables);
		boost::program_options::notify(variables);

		return cli;
	}


}