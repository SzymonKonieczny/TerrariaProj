#pragma once
#include "Mesh.h"

class ChunkMesh : public Mesh
{
public:
	void Generate(std::vector<Block>& BlockColumns);

};

