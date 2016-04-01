#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ImageLoader.h"
#include "ComponentID.h"

#include <vector>
#include <fstream>

struct Component
{
	unsigned id;

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

struct Rect : public Component
{
	float w, h, rect[8];
	unsigned *vbo, vao;

	Rect()
	{
		vbo = new unsigned();

		glGenVertexArrays(1, &vao);
		id = COMP_RECT;

		w = 100;
		h = 100;

		rect[0] = 0;
		rect[1] = h-20;

		rect[2] = 0;
		rect[3] = 0;

		rect[4] = w;
		rect[5] = h;

		rect[6] = w;
		rect[7] = 0;

	}
	Rect(float w, float h)
	{
		vbo = new unsigned();

		glGenVertexArrays(1, &vao);
		id = COMP_RECT;

		this->w = w; 
		this->h = h;

		rect[0] = 0;
		rect[1] = h;

		rect[2] = 0;
		rect[3] = 0;

		rect[4] = w;
		rect[5] = h;

		rect[6] = w;
		rect[7] = 0;
	}
	~Rect()
	{
		delete vbo;
	}
};

struct Texture : public Component
{
	float coords[8];
	unsigned texture, *vbo;

	Texture()
	{
		vbo = new unsigned;
		id = COMP_TEXTURE;

		coords[0] = 0;
		coords[1] = 0;

		coords[2] = 0;
		coords[3] = 1;

		coords[4] = 1;
		coords[5] = 0;

		coords[6] = 1;
		coords[7] = 1;
	}
	Texture(std::string path)
	{
		texture = LoadPNG(path);

		vbo = new unsigned();
		id = COMP_TEXTURE;

		coords[0] = 0;
		coords[1] = 0;

		coords[2] = 0;
		coords[3] = 1;

		coords[4] = 1;
		coords[5] = 0;

		coords[6] = 1;
		coords[7] = 1;
	}
	~Texture()
	{
		delete vbo;
	}
};

#endif//COMPONENT_HPP