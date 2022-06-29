#include "Collider.h"


Collider::Collider(glm::vec2 LeftTop, glm::vec2 RightTop, glm::vec2 RightBot, glm::vec2 LeftBot) : 
	A(LeftTop), B(RightTop), C(RightBot), D(LeftBot)
{

}

bool Collider::checkCollision(glm::vec2 Position)
{

	Block* collision;
	int index = (int)((Position + A).x / ChunkSize) ;

	if (!(index >= (*Chunk::CHUNKS).size() || index < 0))
	{
	collision = (*Chunk::CHUNKS)[index]->vec2ToBlock(Translate(Position + A));
		if (collision != nullptr)
		{
		if(Util::GetInstance()->BLOCKS[(*collision).ID].Collidable)
			{
				return true;
			}
		}
	}

	index = (int)((Position + B).x / ChunkSize);
	if (!(index >= (*Chunk::CHUNKS).size() || index < 0))
	{
	collision = (*Chunk::CHUNKS)[index]->vec2ToBlock(Translate(Position + B));
		if (collision != nullptr)
		{
			if (Util::GetInstance()->BLOCKS[(*collision).ID].Collidable)
			{
				return true;
			}
		}
	}

	 index = (int)((Position + C).x / ChunkSize);
	if (!(index >= (*Chunk::CHUNKS).size() || index < 0))
	{
		collision = (*Chunk::CHUNKS)[index]->vec2ToBlock(Translate(Position + C));
		if (collision != nullptr)
		{
			if (Util::GetInstance()->BLOCKS[(*collision).ID].Collidable)
			{
				return true;
			}
		}
	}

	 index = (int)((Position + D).x / ChunkSize);
	if (!(index >= (*Chunk::CHUNKS).size() || index < 0))
	{
		collision = (*Chunk::CHUNKS)[index]->vec2ToBlock(Translate(Position + D));
		if (collision != nullptr)
		{
			if (Util::GetInstance()->BLOCKS[(*collision).ID].Collidable)
			{
				return true;
			}
		}
	}
	

	return false;


}
glm::vec2 Collider::Translate(glm::vec2 Position)
{
	glm::vec2 newPos;
	if (Position.x > (int)Position.x) newPos.x = ((int)Position.x ) % ChunkSize;
	else newPos.x = (int)Position.x-1 % ChunkSize; //To chunk-internal (local) pos:
	if (Position.y > (int)Position.y) newPos.y = (int)Position.y  + 1;
	else newPos.y = (int)Position.y;
	/*
	newPos.x = ((int)Position.x) % ChunkSize;
	newPos.y = (int)Position.y  +1;*/
	return newPos;

}

