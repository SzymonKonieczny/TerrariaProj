#pragma once
#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
#include "Collider.h"
class Ray
{

public:


	struct RayInfo
	{
		glm::vec2 HitPos;
		glm::vec2 HitFromPos;
		bool Miss;

	};
	RayInfo RayCastResult;
	glm::vec2 direction;
	glm::vec2 Position;

	Collider vectorHeadCollider;
	Ray(glm::vec2 dir, glm::vec2 pos);
	void Cast(int distance);

};







#endif // !RAY_H
