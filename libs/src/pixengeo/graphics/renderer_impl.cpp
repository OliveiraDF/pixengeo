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
#include "renderer_impl.h"
#include "glcheck.h"

namespace pxg::gfx
{

#pragma region Constructors

	renderer::impl::impl(error_callback_t callback)
		: m_next(0)
		, m_callback(callback)
	{
		BOOST_ASSERT_MSG(callback, "A callback must be set");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("[GLAD] Unable to load OpenGL procedures");
		}

		glCheck(glDisable(GL_CULL_FACE));
		glCheck(glDisable(GL_DEPTH_TEST));
		glCheck(glEnable(GL_BLEND));
	}

#pragma endregion
#pragma region Operations

	renderer::entity renderer::impl::create_entity(std::span<vertex> vertices, 
												   topology topology, 
												   blend_mode blend_mode, 
												   std::string_view shader_name,
												   std::optional<std::string_view> texture_name)
	{
		mesh_component mesh;
		shader_component shader;
		blend_component blend;

		glCheck(glGenBuffers(1, &mesh._vbo_id));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, mesh._vbo_id));
		glCheck(glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW));

		glCheck(glGenVertexArrays(1, &mesh._vao_id));
		glCheck(glBindVertexArray(mesh._vao_id));
	
		shader._program_id = m_shader_programs.find(shader_name.data())->second;
		const GLint pos_location = glGetAttribLocation(shader._program_id, "vPos");
		glCheck(glEnableVertexAttribArray(pos_location));
		glCheck(glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, _position)));
		const GLint color_location = glGetAttribLocation(shader._program_id, "vColor");
		glCheck(glEnableVertexAttribArray(color_location));
		glCheck(glVertexAttribPointer(color_location, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, _color)));
		if (texture_name)
		{
			const GLint texcoord_location = glGetAttribLocation(shader._program_id, "vTexCoord");
			glCheck(glEnableVertexAttribArray(texcoord_location));
			glCheck(glVertexAttribPointer(texcoord_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, _tex_coords)));	
		}

		if (texture_name) /* Non la texture GPU ne doit pas être créée ici */
		{
			const GLint texture_id = m_images.find(texture_name->data())->second;

			texture_component texture;

			texture._texture_id = texture_id;

			m_textures[m_next] = texture;
		}


		const auto& [src, dst] = to_native(blend_mode);
		blend._src_factor = src;
		blend._dst_factor = dst;

		mesh._topology = to_native(topology);
		mesh._vertex_count = static_cast<GLsizei>(vertices.size());

		m_meshes[m_next] = mesh;
		m_shaders[m_next] = shader;
		m_blendmodes[m_next] = blend;

		return m_next++;
	}

	void renderer::impl::clear() const noexcept
	{
		glCheck(glClearColor(0.f, 0.f, 0.f, 1.f));
		glCheck(glClear(GL_COLOR_BUFFER_BIT));
	}

	void renderer::impl::draw_all() const
	{
		glCheck(glViewport(0, 0, 640, 480));

		for (auto entity : m_entities)
		{
			const auto& mesh = m_meshes.at(entity);
			const auto& shader = m_shaders.at(entity);
			const auto& blendmode = m_blendmodes.at(entity);
			const auto& transform = m_transforms.at(entity);

			glCheck(glBlendFunc(blendmode._src_factor, blendmode._dst_factor));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, mesh._vbo_id));
			glCheck(glBindVertexArray(mesh._vao_id));
			glCheck(glUseProgram(shader._program_id));

			if (m_textures.contains(entity))
			{				
				const auto& texture = m_textures.at(entity);
				glCheck(glBindTexture(GL_TEXTURE_2D, texture._texture_id));
			}

			const glm::mat4x4& model = transform._model;
			const glm::mat4x4 view = glm::mat4x4(1.f);
			const glm::mat4x4 projection = glm::ortho(0.f, 640.f, 480.f, 0.f, -1.f, 1.f);
			const glm::mat4x4 mvp = projection * view * model;

			const GLint mvp_location = glGetUniformLocation(shader._program_id, "MVP");
			glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

			glCheck(glDrawArrays(mesh._topology, 0, mesh._vertex_count));
		}
	}

#pragma endregion
#pragma region Implementations

	GLenum renderer::impl::to_native(topology topology) const noexcept
	{
		static constexpr const std::array<std::uint32_t, static_cast<std::size_t>(topology::COUNT)> TOPOLOGIES =
		{
			GL_POINTS,
			GL_LINES,
			GL_LINE_STRIP,
			GL_LINE_LOOP,
			GL_TRIANGLES,
			GL_TRIANGLE_STRIP,
			GL_TRIANGLE_FAN,
			GL_QUADS,
		};

		return TOPOLOGIES[static_cast<std::size_t>(topology)];
	}

	const std::pair<GLenum, GLenum>& renderer::impl::to_native(blend_mode blend_mode) const noexcept
	{
		using BlendFactors = std::pair<std::uint32_t, std::uint32_t>;
		static constexpr const std::array<BlendFactors, static_cast<std::size_t>(blend_mode::COUNT)> BLENDMODES =
		{ {
			{ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA },
			{ GL_SRC_ALPHA, GL_ONE },
			{ GL_DST_COLOR, GL_ZERO },
			{ GL_ONE, GL_ZERO },
		} };

		return BLENDMODES[static_cast<std::size_t>(blend_mode)];
	}

#pragma endregion

}