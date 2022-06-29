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


#include "Game.h"

int main()
{
	enum ActiveState
	{
		World,
		Menu,
	};
	ActiveState GameState = ActiveState::World;
	Game game;
	game.GenerateWorld();
	while (!glfwWindowShouldClose(game.getWindow()))
	{
		switch (GameState)
		{
		case ActiveState::World:
			game.DisplayFPS(true);
			game.ClearScreen();

			game.RenderChunksInFrustum();
			game.DrawEntities();

			game.tickEntities();

			glfwSwapBuffers(game.getWindow());
			glfwPollEvents();
			break;
		case ActiveState::Menu:

			break;

		default:
			break;
		}
	}
	return 0;
}
