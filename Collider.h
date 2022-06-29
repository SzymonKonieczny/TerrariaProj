#pragma once
#ifndef COLLIDER.H

#include <glm/glm.hpp>
#include "Chunk.h"

class Collider {
	glm::vec2 A, B, C, D; //left top, right top,, right bot, left bot
	
public:
	Collider(glm::vec2 LeftTop, glm::vec2 RightTop, glm::vec2 RightBot , glm::vec2 LeftBot);
	bool checkCollision(glm::vec2 Position);
	glm::vec2 Translate(glm::vec2 Position);

};

#endif // !COLLIDER.H
