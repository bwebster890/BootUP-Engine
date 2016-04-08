#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "State.hpp"
#include "Component.hpp"

Texture* texture = new Texture;

void LoadModel(State* state, std::string entity, std::string path)
{
	std::ifstream modelFile;
	std::string currentString;

	Vertices* vertices = new Vertices;
	Indices* indices = new Indices;

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

	state->AddComponent(entity, vertices);
	state->AddComponent(entity, indices);
}

void LoadModel(State* state, std::string entity, std::string filePath, std::string texturePath)
{
	LoadModel(state, entity, filePath);

	texture->texture = LoadPNG(texturePath);
	state->AddComponent(entity, texture);
}

#endif//MODEL_LOADER_HPP