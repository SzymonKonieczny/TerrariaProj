#pragma once
#ifndef ENTITY.H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "GLOBAL.h"
#include"Camera.h"
#include "Mesh.h"
 class Entity 
{
	glm::vec2 Position;
	
public:
	virtual void Update(double timeDiff) =0;
	virtual void Draw(Shader& shader) = 0;


};
 struct InvetorySlot{
	 BlockType::BlockTypes Type;
	 int amount;
 };



#endif // !ENTITY.H
