#include "Chunk.h"
std::vector<Chunk*> *Chunk::CHUNKS = nullptr;

Chunk::Chunk(glm::ivec2 ChunkPos_)
{
	ChunkPos = ChunkPos_;


}
void Chunk::NoiseInit()
{
	

		


}

void Chunk::Draw(Shader & shader)
{
	if(isMeshReady.try_acquire())
	mesh.Draw(shader, glm::vec2((ChunkPos.x * ChunkSize),(ChunkPos.y * ChunkSize)));
	isMeshReady.release();
}
void Chunk::Generate()
{
	NoiseInit();

	FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm>  fnFractal;
	FastNoise::SmartNode<> fnGenerator;
	fnSimplex = FastNoise::New<FastNoise::Simplex>();
	fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource(fnSimplex);
	fnFractal->SetOctaveCount(5);
	fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");

	std::cout << "Generating chunk nr:" << ChunkPos.x << std::endl;
	float columnsNoise[16];
	fnGenerator->GenUniformGrid2D(columnsNoise, ChunkPos.x * ChunkSize, 0, ChunkSize, 1,0.02, map_seed);
	for (int i = 0; i < ChunkSize; i++)
	{
		//int column_height = (int)(30 + ((1 + MainNoise.noise((ChunkPos.x * ChunkSize + i)*0.05)) / 2)* 50);


		int column_height = ((columnsNoise[i]+1)/2)  * 50 +32;


		column_heights[i] = column_height;
		for (int k = ChunkHeight; k >= 0; k--)
		{

			if (k == column_height)									// Trawa and Piach
			{
				if (k < WATERLEVEL + 3)	setblock(glm::vec2(i, k), 6);	//BlockColumns.push_back(Block{ glm::vec2(i ,k), 6 }); 
				else
				{
					setblock(glm::vec2(i, k), 0);

				}
			}
			else
			{
				if (k < column_height && k > column_height - 3)		//Ziemia and Piach
				{			// 23					21
					if (k < WATERLEVEL + 3)
					{
						setblock(glm::vec2(i, k), 6);
					}
					else
					{
						setblock(glm::vec2(i, k), 3);
					}
				}
				else												// Kamulec
				{
					if (k < column_height) setblock(glm::vec2(i, k), 2);
				}

				if (k < WATERLEVEL && k > column_height) setblock(glm::vec2(i, k), 7); // Woda


			}

		
		}

	}

	GenerateFeatures();

	std::cout << "Generating chunk nr:" << ChunkPos.x << " is done" << std::endl;

}

void Chunk::UpdateMesh()
{
	mesh.Generate(BlockColumns);
	isMeshReady.release();
}
Block* Chunk::vec2ToBlock(glm::vec2 LocPos) {

	auto search_result = block_map.find(LocPos);
	if (search_result != block_map.end())
	{
		return & BlockColumns[(*search_result).second];
	}
	else return nullptr;

}
void Chunk::GenerateFeatures()
{

	for (int i = 0; i < 6; i++)
	{
		glm::vec2 RandomPos = glm::vec2(random(2, 12), random(1, 50));
		Block* block = vec2ToBlock(RandomPos);
		if (block != nullptr)
		{
			if ((*block).ID == 2)		// Ores
			{
				BlockColumns[block_map[RandomPos]].ID = 1;
				BlockColumns[block_map[glm::vec2(RandomPos.x, RandomPos.y + 1)]].ID = 1;
				BlockColumns[block_map[glm::vec2(RandomPos.x - random(0, 2), RandomPos.y + random(0, 2))]].ID = 1;
				BlockColumns[block_map[glm::vec2(RandomPos.x - random(0, 2), RandomPos.y + random(0, 3))]].ID = 1;
				BlockColumns[block_map[glm::vec2(RandomPos.x + random(0, 2), RandomPos.y)]].ID = 1;
			}
		}
	}
	int random_tree_Column = random(2, 12);
	glm::vec2 RandomPos = glm::vec2(random(2, 12), random(1, 60));
	Block* block = vec2ToBlock(RandomPos);

	block = vec2ToBlock(glm::vec2(random_tree_Column, column_heights[random_tree_Column]));
	if (block != nullptr)
	{
		if ((*block).ID == 0)		// Tree
		{
			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 1), 4);
			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 2), 4);
			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 3), 4);
			setblock(glm::vec2((*block).LocalPos.x - 1, (*block).LocalPos.y + 4), 5);
			setblock(glm::vec2((*block).LocalPos.x - 2, (*block).LocalPos.y + 4), 5);
			setblock(glm::vec2((*block).LocalPos.x + 1, (*block).LocalPos.y + 4), 5);
			setblock(glm::vec2((*block).LocalPos.x + 2, (*block).LocalPos.y + 4), 5);
			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 4), 5);

			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 5), 5);
			setblock(glm::vec2((*block).LocalPos.x - 1, (*block).LocalPos.y + 5), 5);
			setblock(glm::vec2((*block).LocalPos.x - 2, (*block).LocalPos.y + 5), 5);
			setblock(glm::vec2((*block).LocalPos.x + 1, (*block).LocalPos.y + 5), 5);
			setblock(glm::vec2((*block).LocalPos.x + 2, (*block).LocalPos.y + 5), 5);

			setblock(glm::vec2((*block).LocalPos.x - 1, (*block).LocalPos.y + 6), 5);
			setblock(glm::vec2((*block).LocalPos.x, (*block).LocalPos.y + 6), 5);
			setblock(glm::vec2((*block).LocalPos.x + 1, (*block).LocalPos.y + 6), 5);



		}
	}


}

void setWorldBlock(glm::vec2 LocPos)
{
	int chunkPos = LocPos.x / ChunkSize;

}


void Chunk::setblock(glm::vec2 LocPos, int ID)
{
	if (!isBlockViable(LocPos))
	{
		std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
		return;
	}
	if (block_map.find(glm::vec2(LocPos.x, LocPos.y)) != block_map.end())
	{
		BlockColumns[block_map[glm::vec2(LocPos.x, LocPos.y)]].ID = ID;
	}
	else
	{
		BlockColumns.push_back(Block{ glm::vec2(LocPos.x, LocPos.y), ID });
		block_map.insert(std::make_pair(glm::vec2(LocPos.x, LocPos.y), BlockColumns.size()-1));
	}

}
void Chunk::deleteblock(glm::vec2 LocPos)
{
	if (!isBlockViable(LocPos))
	{
		std::cout << "Not a viable position. Block requested at " << LocPos.x << " " << LocPos.y + '\n';
		return;
	}
	if (block_map.find(glm::vec2(LocPos.x, LocPos.y)) != block_map.end())
	{
		//BlockColumns[block_map[glm::vec2(LocPos.x, LocPos.y)]].ID = ;
	}
	

}

bool Chunk::isBlockViable(glm::vec2 LocPos)
{
	return !(LocPos.x > ChunkSize - 1 || LocPos.x < 0 || LocPos.y < 0 || LocPos.y > ChunkHeight - 1);
}

//Create a light map for a chunk, and a function for caltulating it
// float LightMap[256][16] Using it change the vertex colors
