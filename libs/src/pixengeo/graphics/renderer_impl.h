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

	class renderer::impl
	{
#pragma region Constructors

	public:

		impl(error_callback_t callback);
		~impl() = default;
		impl(const impl&) = delete;
		impl& operator=(const impl&) = delete;

#pragma endregion
#pragma region Attributes

	private:

		entity												m_next;
		error_callback_t									m_callback;
		std::vector<entity>									m_entities;
		std::unordered_map<entity, blend_component>			m_blendmodes;
		std::unordered_map<entity, mesh_component>			m_meshes;
		std::unordered_map<entity, transform_component>		m_transforms;
		std::unordered_map<entity, shader_component>		m_shaders;
		std::unordered_map<entity, texture_component>		m_textures;
		std::map<std::string, GLuint>						m_shader_programs;
		std::map<std::string, GLuint>						m_images;

#pragma endregion
#pragma region Operations

	public:

		entity create_entity(std::span<vertex> vertices, 
							 topology topology, 
							 blend_mode blend_mode, 
							 std::string_view shader,
							 std::optional<std::string_view> texture = std::nullopt);
		void clear() const noexcept;
		void draw_all() const;

#pragma endregion
#pragma region Implementations

	private:

		GLenum to_native(topology topology) const noexcept;
		const std::pair<GLenum, GLenum>& to_native(blend_mode blend_mode) const noexcept;

#pragma endregion
	};

}