#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "State.hpp"
#include "Component.hpp"

void LoadModel(State* state, std::string entity, std::string path)
{
	std::ifstream modelFile;
	std::string currentString;

	Vertices* vertices = new Vertices;
	Indices* indices = new Indices;
	Texture* texture = new Texture;

	float x, y, z;
	unsigned index;

	modelFile.open(path);

	int numMeshes, numData;
	modelFile >> numMeshes >> numData;

	for (int i = 0; i < numData; i++)
	{
		while (modelFile >> currentString)
		{
			if (currentString == "V")
			{
				modelFile >> x >> y >> z;
				vertices->AddVertex(x, y, z);
			}

			if (currentString == "I")
			{
				modelFile >> index;
				indices->AddIndex(index);
			}

			if (currentString == "T")
			{
				modelFile >> x >> y;
				texture->AddCoords(x, y);
			}
		}
	}

	texture->texture = LoadPNG("images/crate_texture.png");

	state->AddComponent(entity, vertices);
	state->AddComponent(entity, texture);
	state->AddComponent(entity, indices);
}

#endif//MODEL_LOADER_HPP