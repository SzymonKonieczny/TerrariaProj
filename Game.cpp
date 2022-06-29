#include "Game.h"
void GenerateAsync(int i)
{
	(*Chunk::CHUNKS)[i]->Generate();
	(*Chunk::CHUNKS)[i]->UpdateMesh();
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window::GetInstance()->WinHeight = height;
	Window::GetInstance()->WinWidth = width;
	glViewport(0, 0, width, height);
}


Game::Game()
{
	setup();

	LoadBlocks();

	shaderProgram = new Shader("default.vert", "default.frag");
	TextureAtlas = new Texture("textures/textureatlas.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	PlayerTxt = new Texture("textures/Player.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	Player = new PlayerEntity(*shaderProgram, Window::GetInstance()->window);
	initiateShaders();

}

Game::~Game()
{
	free(Player);
	free(shaderProgram);
	free(TextureAtlas);
	free(PlayerTxt);

	shaderProgram->Delete();

	glDeleteTextures(1, &TextureAtlas->ID);
	glDeleteTextures(1, &PlayerTxt->ID);

	// Delete window before ending the program
	glfwDestroyWindow(Window::GetInstance()->window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Game::setup()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	Window::GetInstance()->window = glfwCreateWindow(Window::GetInstance()->WinWidth,
		Window::GetInstance()->WinHeight, "This Is a Project. In English", NULL, NULL);
	// Error check if the window fails to create
	
	if (Window::GetInstance()->window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(Window::GetInstance()->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //GLAD init check, just in case
		std::cout << "Could not initialize GLAD!" << std::endl;
		glfwTerminate();

	}
	
	glfwSetFramebufferSizeCallback(Window::GetInstance()->window, framebuffer_size_callback);
	glViewport(0, 0, Window::GetInstance()->WinWidth, -(Window::GetInstance()->WinHeight));
	glfwSwapInterval(1);

}

void Game::LoadBlocks()
{
	

	int loadedAmout = 0;
	for (int i = 0; i < 5; i++) // 5 x 5 slots in the current atlas
	{
		if (loadedAmout >= amoutOfBlocks) break;
		for (int k = 0; k < 5; k++)
		{
			glm::vec2 testingX = glm::vec2(texturedimention * k, texturedimention * k + texturedimention);
			glm::vec2 testingY = glm::vec2(texturedimention * i, texturedimention * i + texturedimention);

			Util::GetInstance()->BLOCKS.push_back(BlockTemplate({ testingX,testingY ,true , "Unnamed", BlockType::Air }));
			loadedAmout++;
			if (loadedAmout >= amoutOfBlocks) break;
		}
	}
	//Here load properties of every block.
	Util::GetInstance()->BLOCKS[BlockType::Air].Collidable = false;
	Util::GetInstance()->BLOCKS[BlockType::Water].Collidable = false;

	Util::GetInstance()->BLOCKS[BlockType::Grass].name = "Grass Block";
	Util::GetInstance()->BLOCKS[BlockType::ShubiumOre].name = "Shubium Ore";
	Util::GetInstance()->BLOCKS[BlockType::Stone].name = "Stone";
	Util::GetInstance()->BLOCKS[BlockType::Dirt].name = "Dirt";
	Util::GetInstance()->BLOCKS[BlockType::Log].name = "Wood";
	Util::GetInstance()->BLOCKS[BlockType::Leaves].name = "Leaves";
	Util::GetInstance()->BLOCKS[BlockType::Sand].name = "Sand";
	Util::GetInstance()->BLOCKS[BlockType::Water].name = "Water";
	Util::GetInstance()->BLOCKS[BlockType::ShubiumCrystal].name = "Shubium Crystal";

	Util::GetInstance()->BLOCKS[BlockType::Grass].drops = BlockType::Dirt;
	Util::GetInstance()->BLOCKS[BlockType::ShubiumOre].drops = BlockType::ShubiumCrystal;
	Util::GetInstance()->BLOCKS[BlockType::Stone].drops = BlockType::Stone;
	Util::GetInstance()->BLOCKS[BlockType::Dirt].drops = BlockType::Dirt;
	Util::GetInstance()->BLOCKS[BlockType::Log].drops = BlockType::Log;
	Util::GetInstance()->BLOCKS[BlockType::Leaves].drops = BlockType::Air;
	Util::GetInstance()->BLOCKS[BlockType::Sand].drops = BlockType::Sand;
	Util::GetInstance()->BLOCKS[BlockType::Water].drops = BlockType::Air;

}
void Game::initiateShaders()
{
	TextureAtlas->texUnit(*shaderProgram, "tex0", 0);
	PlayerTxt->texUnit(*shaderProgram, "tex0", 1);

}
void Game::GenerateWorld()
{
	Chunk::CHUNKS = &Chunks;
	for (int i = 0; i < chunkamount; i++)
	{
		(*Chunk::CHUNKS).push_back(new Chunk(glm::vec2(i, 0)));

		futures.push_back(std::async(std::launch::async,GenerateAsync, i));
	}

}
GLFWwindow* Game::getWindow()
{
	return Window::GetInstance()->window;
}

void Game::ClearScreen()
{
	glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shaderProgram->Activate();


}

void Game::DisplayFPS(bool Display)
{
	crntTime = glfwGetTime();
	timeDiff = crntTime - prevTime;
	counter++;
	if (timeDiff >= 1.0 / 30.0)
	{
		if (Display)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "Prodzekto - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(Window::GetInstance()->window, newTitle.c_str());
		}
		prevTime = crntTime;
		counter = 0;
	}
}

void Game::tickEntities()
{
	UpdatePlayer();
}
void Game::DrawEntities()
{

	glBindTexture(GL_TEXTURE_2D, PlayerTxt->ID);

	Player->Draw(*shaderProgram);

}
void Game::RenderChunksInFrustum()
{

	glBindTexture(GL_TEXTURE_2D, TextureAtlas->ID);

	int index = (int)(Player->Position.x / ChunkSize) - 2;

	if (index < 0) index = 0;
	else if (index >= chunkamount) index = chunkamount - 3;


	for (int i = index; i < index + 5; i++)
	{
		Chunks[i]->Draw(*shaderProgram);
	}

}
void Game::UpdatePlayer()
{
	if (timeDiff >= 1.0 / 30.0)
	{
		Player->Update(timeDiff);
	}
}
