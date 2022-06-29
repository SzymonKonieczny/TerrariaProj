#pragma once
#ifndef MESH_H
#define	MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "shaderClass.h"
#include "VBO.h"
#include"VAO.h"
#include"EBO.h"
#include"Texture.h"
#include "Block.h"
#include "GLOBAL.h"
#include "Camera.h"
class Mesh{
public:
	  // STATIC to ma byc
	glm::mat4 model;
	std::vector<Vertex> vertices;
	std::vector < GLuint> indices;
	Mesh(std::vector<Vertex>& vertices_, std::vector < GLuint>& indices_);
	Mesh();
	//void Generate(const std::vector<std::vector<Block>>& BlockColumns,const glm::ivec2 ChunkPos );
	void Draw(Shader& shader, glm::vec2 Position);
	VAO VAO;
	VBO* VBO1;
	EBO* EBO1;

};

#endif // !MESH_H
