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
	float rotationSpeed;

	Orientation()
	{
		this->position = glm::vec3(0.0, 0.0, 0.0);
		this->rotation = glm::vec3(0.0, 0.0, 0.0);
		this->rotationSpeed = 0.0;
		id = COMP_ORI;
	}
	Orientation(glm::vec3 startingPosition)
	{
		this->position = startingPosition;
		this->rotation = glm::vec3(0.0, 0.0, 0.0);
		this->rotationSpeed = 0.0;
		id = COMP_ORI;
	}

	Orientation(glm::vec3 startingPosition, glm::vec3 startingRotation, float rotationSpeed)
	{
		this->position = startingPosition;
		this->rotation = startingRotation;
		this->rotationSpeed = rotationSpeed;
		id = COMP_ORI;
	}

	// Set new position/rotation
	void setPosition(glm::vec3 newPosition) { this->position = newPosition; }
	void setRotation(glm::vec3 newRotation) { this->rotation = newRotation; }

	// Shift position/rotation
	void adjustPosition(glm::vec3 shiftPosition) { this->position += shiftPosition; }
	void adjustRotation(glm::vec3 shiftRotation) { this->rotation += shiftRotation; }

	virtual ~Orientation(){}
};

struct Vertices : public Component
{
	unsigned vbo, vao;
	std::vector <float> vertices;

	Vertices()
	{
		id = COMP_VERTICES;
		glGenVertexArrays(1, &vao);
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
	std::vector <unsigned> indices;

	Indices()
	{
		id = COMP_INDICES;
	}
	virtual ~Indices(){}

	inline void AddIndex(unsigned index){ indices.push_back(index); }
};

struct Texture : public Component
{
	std::vector <float> coords;
	unsigned texture, vbo;

	Texture()
	{
		id = COMP_TEXTURE;
	}
	Texture(std::string path)
	{
		texture = LoadPNG(path);
		id = COMP_TEXTURE;
	}
	Texture(const Texture& tex)
	{
		texture = tex.texture;

		coords = tex.coords;

		id = COMP_TEXTURE;
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