#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <future>



#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"
#include"Chunk.h"
#include"PlayerEntity.h"
#include "GLOBAL.h"
#include "SimplexNoise.h"
#include "Window.h"

class Game{
	PlayerEntity* Player;
	Shader* shaderProgram;
	Texture* TextureAtlas;
	Texture* PlayerTxt;

	
	std::vector<Chunk*> Chunks;
	int chunkamount = 100;
	std::vector<std::future<void>> futures;
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	void UpdatePlayer();
	void LoadBlocks();
public:

	Game();
	~Game();
	void GenerateWorld();
	void setup();
	void initiateShaders();
	void DisplayFPS(bool Display);

	void RenderChunksInFrustum();
	void tickEntities();
	void DrawEntities();
	GLFWwindow* getWindow();
	void ClearScreen();
};

#endif // !GAME_H
