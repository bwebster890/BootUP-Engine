#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <glew/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "System.hpp"
#include "Component.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"


class RenderSystem : public System
{
private:
	glm::mat4 m_mvp;
	int m_uniformLoc;

	Position* m_position;
	Rect* m_rect;
	Texture* m_texture;

	Camera* m_camera;
	ShaderProgram* m_program;
public:
	RenderSystem();
	~RenderSystem();

	void Update();
	void AddComponent(Component*);
	void SetCamera(Camera*);
	void SetShaderProgram(ShaderProgram*);
};

#endif//RENDER_SYSTEM_HPP