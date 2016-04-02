#include <glew/glew.h>

#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
	m_id = SYS_RENDER;
	m_enabled = true;
}
RenderSystem::~RenderSystem()
{

}

void RenderSystem::Update()
{
	for (unsigned i = 0; i < components.size(); i++)
	{
		if (components[i]->id == COMP_POS)
		{
			m_position = dynamic_cast<Position*>(components[i]);

			m_mvp = m_camera->get_matrix() * glm::translate(glm::mat4(0.1), glm::vec3(m_position->x, m_position->y, m_position->z));

			m_uniformLoc = glGetUniformLocation(*m_program->get_program(), "MVP");
			glUniformMatrix4fv(m_uniformLoc, 1, false, &m_mvp[0][0]);
		}

		if (components[i]->id == COMP_RECT)
		{
			m_rect = dynamic_cast<Rect*>(components[i]);

			glBindVertexArray(m_rect->vao);
		}

		if (components[i]->id == COMP_TEXTURE)
		{
			m_texture = dynamic_cast<Texture*>(components[i]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture->texture);

			m_uniformLoc = glGetUniformLocation(*m_program->get_program(), "tex");
			glUniform1i(m_uniformLoc, 0);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
		}
	}
}
void RenderSystem::AddComponent(Component* component)
{
	components.push_back(component);

	if (component->id == COMP_POS){}

	if (component->id == COMP_RECT)
	{
		m_rect = dynamic_cast<Rect*>(component);

		glBindVertexArray(m_rect->vao);

		glGenBuffers(1, m_rect->vbo);

		glBindBuffer(GL_ARRAY_BUFFER, *m_rect->vbo);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), m_rect->rect, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
	}

	if (component->id == COMP_TEXTURE)
	{
		m_texture = dynamic_cast<Texture*>(component);

		glGenBuffers(1, m_texture->vbo);

		glBindBuffer(GL_ARRAY_BUFFER, *m_texture->vbo);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), m_texture->coords, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
	}
}
void RenderSystem::SetCamera(Camera* camera)
{
	m_camera = camera;
}
void RenderSystem::SetShaderProgram(ShaderProgram* program)
{
	m_program = program;
	program->use();
}