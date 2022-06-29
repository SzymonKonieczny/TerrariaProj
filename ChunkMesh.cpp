#include "ChunkMesh.h"




void ChunkMesh::Generate(std::vector<Block>& BlockColumns)
{
	vertices.clear();
	indices.clear();
	int vert_count = 0;



	for (std::vector<Block>::iterator it = BlockColumns.begin(); it != BlockColumns.end(); ++it)
	{
		if ((*it).ID == BlockType::Air) continue;
						
			
			
			//		BLOCK TO THE RIGHT-BOTTOM OF THE POINT
		vertices.push_back(Vertex{
				 glm::vec3((*it).LocalPos.x,  (*it).LocalPos.y, 0.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesX.x , Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesY.y)
			}); // upper left
		vertices.push_back(Vertex{
			 glm::vec3((*it).LocalPos.x + 1.0f, (*it).LocalPos.y, 0.0f),
			 glm::vec3(1.0f, 1.0f, 1.0f),
			 glm::vec2(Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesX.y, Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesY.y)
			}); //upper right
		vertices.push_back(Vertex{
			 glm::vec3((*it).LocalPos.x + 1.0f,  (*it).LocalPos.y - 1.0f, 0.0f),
			 glm::vec3(1.0f, 1.0f, 1.0f),
			 glm::vec2(Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesX.y, Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesY.x)
			}); //lower right
		vertices.push_back(Vertex{
			 glm::vec3((*it).LocalPos.x,  (*it).LocalPos.y - 1.0f, 0.0f),
			 glm::vec3(1.0f, 1.0f, 1.0f),
			 glm::vec2(Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesX.x, Util::GetInstance()->BLOCKS[(*it).ID].textureCoordinatesY.x)
			}); // lower left

			
		indices.push_back(vert_count);
		indices.push_back(vert_count + 1);
		indices.push_back(vert_count + 2);
		indices.push_back(vert_count + 3);
		indices.push_back(vert_count + 2);
		indices.push_back(vert_count);
		vert_count += 4;

	}

	
}