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
		if (components[i]->id == COMP_ORI)
		{
			m_orientation = dynamic_cast<Orientation*>(components[i]);

			// Object Orientation Matrix
			glm::mat4 obj_orientation;

			// Set the object's position in the matix
			obj_orientation = glm::translate(obj_orientation, m_orientation->position);

			// Apply rotation if it is avalible (otherwise skip...if zeros are supplied the object will not be visible)
			if (m_orientation->rotationSpeed > 0.0)
			{
				// Set the object's rotation in the matix
				obj_orientation = glm::rotate(obj_orientation, (GLfloat)glfwGetTime() * m_orientation->rotationSpeed, m_orientation->rotation);
			}

			m_mvp = m_camera->get_matrix() * obj_orientation;
			//m_mvp = m_camera->get_matrix() * glm::translate(glm::mat4(1.0), m_orientation->position);

			m_uniformLoc = glGetUniformLocation(*m_program->get_program(), "MVP");
			glUniformMatrix4fv(m_uniformLoc, 1, false, &m_mvp[0][0]);
		}

		if (components[i]->id == COMP_VERTICES)
		{
			m_vertices = dynamic_cast<Vertices*>(components[i]);

			glBindVertexArray(m_vertices->vao);
		}

		if (components[i]->id == COMP_TEXTURE)
		{
			m_texture = dynamic_cast<Texture*>(components[i]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture->texture);

			m_uniformLoc = glGetUniformLocation(*m_program->get_program(), "tex");
			glUniform1i(m_uniformLoc, 0);
		}

		if (components[i]->id == COMP_INDICES)
		{
			m_indices = dynamic_cast<Indices*>(components[i]);

			glDrawElements(GL_TRIANGLES, m_indices->indices.size(), GL_UNSIGNED_INT, &m_indices->indices[0]);
			glBindVertexArray(0);
		}
	}
}
void RenderSystem::AddComponent(Component* component)
{
	components.push_back(component);

	if (component->id == COMP_ORI){}

	if (component->id == COMP_VERTICES)
	{
		m_vertices = dynamic_cast<Vertices*>(component);

		glBindVertexArray(m_vertices->vao);

		glGenBuffers(1, &m_vertices->vbo);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertices->vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices->vertices.size() * sizeof(GLfloat), &m_vertices->vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
	}

	if (component->id == COMP_TEXTURE)
	{
		m_texture = dynamic_cast<Texture*>(component);

		glGenBuffers(1, &m_texture->vbo);

		glBindBuffer(GL_ARRAY_BUFFER, m_texture->vbo);
		glBufferData(GL_ARRAY_BUFFER, m_texture->coords.size() * sizeof(GLfloat), &m_texture->coords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
	}

	if (component->id == COMP_INDICES){}
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