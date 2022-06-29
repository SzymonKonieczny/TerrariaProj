#pragma once
#include "shaderClass.h"
#include <glm/glm.hpp>

 class Drawable
{
	
public:
	

	virtual void Draw(Shader& shader, glm::vec2 Position) =0;

};