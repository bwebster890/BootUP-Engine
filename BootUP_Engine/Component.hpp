#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ImageLoader.h"
#include "ComponentID.h"

#include <vector>

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

struct Position : public Component
{
	float x, y, z;

	Position()
	{
		x = 0;
		y = 0;
		z = 0;

		id = COMP_POS;
	}
	Position(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		id = COMP_POS;
	}
	virtual ~Position(){}
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
	float x, y, z;

	Velocity()
	{
		id = COMP_VELOCITY;

		x = 0;
		y = 0;
		z = 0;
	}
	Velocity(float x, float y, float z)
	{
		id = COMP_VELOCITY;

		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void adjustXVelocity(float x) { this->x = x; }
	inline void adjustYVelocity(float y) { this->y = y; }
	inline void adjustZVelocity(float z) { this->z = z; }

	virtual ~Velocity() {}
};

#endif//COMPONENT_HPP