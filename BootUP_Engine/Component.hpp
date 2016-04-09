#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ImageLoader.h"
#include "ComponentID.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Component
{
	unsigned id;
	std::string entity;

	Component()
	{
		id = COMP_NONE;
	}
	virtual ~Component(){}
};

struct Orientation : public Component
{
	glm::vec3 position;
	glm::vec3 rotation;
	float rotationSpeed, angle;

	Orientation()
	{
		this->position = glm::vec3(0.0, 0.0, 0.0);
		this->rotation = glm::vec3(0.0, 0.0, 0.0);
		this->rotationSpeed = 0.0;
		this->angle = 0.0;
		id = COMP_ORI;
	}
	Orientation(glm::vec3 startingPosition)
	{
		this->position = startingPosition;
		this->rotation = glm::vec3(0.0, 0.0, 0.0);
		this->rotationSpeed = 0.0;
		this->angle = 0.0;
		id = COMP_ORI;
	}
	Orientation(glm::vec3 startingPosition, glm::vec3 startingRotation, float rotationSpeed)
	{
		this->position = startingPosition;
		this->rotation = startingRotation;
		this->rotationSpeed = rotationSpeed;
		this->angle = 0.0;
		id = COMP_ORI;
	}
	Orientation(const Orientation& ori)
	{
		this->position = ori.position;
		this->rotation = ori.rotation;
		this->rotationSpeed = ori.rotationSpeed;
		this->angle = ori.angle;
		id = COMP_ORI;
	}

	// Set new position/rotation
	inline void setPosition(glm::vec3 newPosition) { this->position = newPosition; }
	inline void setRotation(glm::vec3 newRotation) { this->rotation = newRotation; }

	// Shift position/rotation
	inline void adjustPosition(glm::vec3 shiftPosition) { this->position += shiftPosition; }
	inline void adjustRotation(glm::vec3 shiftRotation) { this->rotation += shiftRotation; }

	virtual ~Orientation(){}
};

struct Vertices : public Component
{
	unsigned vbo, vao;
	std::vector <float> vertices;

	Vertices()
	{
		id = COMP_VERTICES;
	}
	Vertices(const Vertices& vertices, unsigned vao)
	{
		id = COMP_VERTICES;

		this->vao = vao;
		vbo = vertices.vbo;

		this->vertices = vertices.vertices;
	}
	virtual ~Vertices()
	{

	}

	void AddVertex(float x, float y, float z)
	{
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}

};

struct Indices : public Component
{
	unsigned ebo, vao;
	std::vector <unsigned> indices;

	Indices()
	{
		id = COMP_INDICES;
	}
	Indices(const Indices& indices, unsigned vao)
	{
		id = COMP_INDICES;

		this->vao = vao;
		ebo = indices.ebo;

		this->indices = indices.indices;
	}
	virtual ~Indices(){}

	inline void AddIndex(unsigned index){ indices.push_back(index); }
};

struct Texture : public Component
{
	std::vector <float> coords;
	unsigned texture, vbo, vao;

	Texture()
	{
		id = COMP_TEXTURE;
	}
	Texture(std::string path)
	{
		id = COMP_TEXTURE;
		texture = LoadPNG(path);
	}
	Texture(const Texture& tex, unsigned vao)
	{
		id = COMP_TEXTURE;
		texture = tex.texture;

		this->vao = vao;
		vbo = tex.vbo;

		coords = tex.coords;
	}
	virtual ~Texture(){}

	void AddCoords(float x, float y)
	{
		coords.push_back(x);
		coords.push_back(y);
	}
};

struct Gravity : public Component
{
	float customGravity = 0.0;

	Gravity() { id = COMP_GRAVITY; }
	Gravity(float customGravity)
	{
		this->customGravity = customGravity;
		id = COMP_GRAVITY;
	}
	virtual ~Gravity() {}
};

struct Velocity : public Component
{
	glm::vec3 velocity;

	Velocity()
	{
		this->velocity = glm::vec3(0.0, 0.0, 0.0);
		id = COMP_VELOCITY;
	}
	Velocity(float x, float y, float z)
	{
		this->velocity = glm::vec3(x, y, z);
		id = COMP_VELOCITY;
	}

	inline void adjustXVelocity(float x) { this->velocity.x = x; }
	inline void adjustYVelocity(float y) { this->velocity.y = y; }
	inline void adjustZVelocity(float z) { this->velocity.z = z; }

	virtual ~Velocity() {}
};

#endif//COMPONENT_HPP