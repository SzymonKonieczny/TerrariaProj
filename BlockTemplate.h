#pragma once
#ifndef BLOCK_TEMPLATE_H
#define BLOCK_TEMPLATE_H
#include <glad/glad.h>
#include <glm/glm.hpp>
struct BlockType
{
	enum BlockTypes
	{
		Grass,
		ShubiumOre,
		Stone,
		Dirt,
		Log,
		Leaves,
		Sand,
		Water,
		Air,
		ShubiumCrystal
	};

};
struct BlockTemplate
{
	glm::vec2 textureCoordinatesX;  //x mininmum, y maximim 
	glm::vec2 textureCoordinatesY;
	bool Collidable;
	std::string name;
	BlockType::BlockTypes drops;

};

#endif // !BLOCK_TEMPLATE_H


