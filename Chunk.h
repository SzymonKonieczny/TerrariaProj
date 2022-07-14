#pragma once
#ifndef CHUNK_H
#define CHUNK_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <future>
#include <thread>
#include <chrono>
#include <semaphore>

#include "Block.h"
#include "ChunkMesh.h"
#include "GLOBAL.h"
#include "Drawable.h"


#include "SimplexNoise.h"
class Chunk {
public:


	std::vector<Block> BlockColumns; 
	glm::ivec2 ChunkPos;

	  std::unordered_map<glm::vec2, int> block_map; 
	  std::binary_semaphore isMeshReady{ 0 };

	  /*FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	  FastNoise::SmartNode<FastNoise::FractalFBm>  fnFractal;
	  FastNoise::SmartNode<> fnGenerator;*/
	static std::vector<Chunk*> *CHUNKS;

	ChunkMesh mesh;
	int column_heights[15];
	Chunk(glm::ivec2 ChunkPos_);
	void NoiseInit();
	void Draw(Shader& shader);
	void Generate();
	void GenerateFeatures();
	void UpdateMesh();
	void setblock(glm::vec2 LocPos, int ID);
	void deleteblock(glm::vec2 LocPos);
	void setWorldBlock(glm::vec2 LocPos);
	bool isBlockViable(glm::vec2 LocPos);
	Block* vec2ToBlock(glm::vec2 LocPos);


	//Create a light map for a chunk, and a function for caltulating it
	// float LightMap[256][16] Using it change the vertex colors
};

#endif // !CHUNK_H
