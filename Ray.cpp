#include "Ray.h"

Ray::Ray(glm::vec2 dir, glm::vec2 pos) : direction(glm::normalize(dir)), vectorHeadCollider(
	glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f),
	glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f)), Position(pos)
{

}

void Ray::Cast(int distance)
{
	RayCastResult.Miss = true;
	RayCastResult.HitFromPos = glm::floor(Position);
	RayCastResult.HitPos = glm::floor(Position);

	for (float i = 0; i < distance; i+=0.2f)
	{
		RayCastResult.HitFromPos = RayCastResult.HitPos;
		RayCastResult.HitPos = RayCastResult.HitFromPos + (direction * 0.2f);
		if (vectorHeadCollider.checkCollision(RayCastResult.HitPos))
		{
			RayCastResult.HitPos = glm::floor(RayCastResult.HitPos  + glm::vec2(0, 1));
			RayCastResult.HitFromPos = glm::floor(RayCastResult.HitFromPos + glm::vec2(0,1));

			RayCastResult.Miss = false;
			return;

		}

		
	}

}
