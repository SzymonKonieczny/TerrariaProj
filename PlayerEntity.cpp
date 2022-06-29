#include "PlayerEntity.h"

double PlayerEntity::mouseX = 0;
double PlayerEntity::mouseY = 0;

PlayerEntity::PlayerEntity(Shader& shader, GLFWwindow* window_) :
	collider(
		glm::vec2(-0.4f, +0.9f ), glm::vec2(0.4f, +0.9f),
		glm::vec2(0.4f, -1.f ), glm::vec2(-0.4f, -1.f )),
	UIShader("defaultUI.vert", "default.frag")
{
	float crntTime = glfwGetTime();
	float prevTime = 0;
	 window = window_;
	UsedShader = &shader;
	Position = { 160.0,100.0 };
	mesh.Generate();
	camera = new Camera(glm::vec3(Position,2));

	//UsedShader->Activate(); moved to the function below
	camera->GetUniformLocations(*UsedShader);

	blockSelectMesh.Generate();
	
	glfwSetCursorPosCallback(window, cursor_pos_callback);

	for (int i = 0; i < 10; i++)
	{
		Inventory[i] = { BlockType::BlockTypes::Air, 0 };
	}
}
void PlayerEntity::TryMoveRight(double distance)
{
	glm::vec2 pos(Position);
	Position.x += distance;
	if (collider.checkCollision(Position))
	{
		//std::cout << "collision at  X " << Position.x << std::endl;
		Position = pos;
	}
}

void PlayerEntity::TryMoveUp(double distance)
{
	glm::vec2 pos(Position);
	Position.y += distance;
	if (collider.checkCollision(Position))
	{
		//std::cout << "collision at  Y " <<  Position.y << std::endl;
		Position = pos;
	}
}

void PlayerEntity::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
}
int PlayerEntity::FindViableInventorySlot(BlockType::BlockTypes Type )
{

	for (int i = 0; i < 10; i++)
	{
		if (Inventory[i].Type == Type) return i;
	}
	for (int i = 0; i < 10; i++)
	{
		if (Inventory[i].amount == 0) return i;
	}
	return -1;
}
void PlayerEntity::CheckCollision()
{
}

void PlayerEntity::UpdateCamera()
{

	camera->Position.x = Position.x;
	camera->Position.y = Position.y;
	camera->Position.z = 2;
	camera->UpdateView(*UsedShader);

}

void PlayerEntity::Update(double timeDiff)
{

	ProcessInput(timeDiff);
	if (!Fly)TryMoveUp(-8.1 * timeDiff); //Placeholder gravity

	UpdateCamera();

}
void PlayerEntity::DrawBlockSelect()
{

	float Xpos, Ypos;
	Xpos = ((2.f * mouseX) / (Window::GetInstance()->WinWidth)) - 1;
	Ypos = 1.0f - ((2.f * mouseY) / (Window::GetInstance()->WinHeight));
	glm::vec2 step(Xpos, Ypos);
	Ray ray(step, Position);


	ray.Cast(10);
	RayCastInfo = ray.RayCastResult;
	if (!ray.RayCastResult.Miss)
		blockSelectMesh.Draw(*UsedShader, glm::vec2(RayCastInfo.HitFromPos));

}
void PlayerEntity::BreakBlock()
{
	// PLACE BLOCK CODE, CHANGE IT TO BREAK BLOCK
	if (RayCastInfo.Miss) return;
	int index = (int)RayCastInfo.HitPos.x / 16;
	glm::vec2 Pos((int)RayCastInfo.HitPos.x % 16, RayCastInfo.HitPos.y);
	if (glm::abs(Pos.x - Position.x) < 0.5 && glm::abs(Pos.y - Position.y) < 0.5) return;
	

	if ((*Chunk::CHUNKS)[index]->vec2ToBlock(Pos) == nullptr) return;
	BlockType::BlockTypes Type = Util::GetInstance()->BLOCKS[(*Chunk::CHUNKS)[index]->vec2ToBlock(Pos)->ID].drops;
	int slot = FindViableInventorySlot(Type);
	if (slot >=0 && slot <=9 && Type != BlockType::Air)
	{
		if (Type == BlockType::ShubiumCrystal)
		{
			Inventory[slot].amount += random(2, 5);									//Inside Joke for the class
			Inventory[slot].Type = Type;
		}
		else																		//if i was to ever present it in front of them
		{
			Inventory[slot].amount += 1;
			Inventory[slot].Type = Type;
		}
		
	}

	(*Chunk::CHUNKS)[index]->setblock(Pos, BlockType::Air);
	(*Chunk::CHUNKS)[index]->UpdateMesh();

}
void PlayerEntity::PlaceBlock()
{
	if (RayCastInfo.Miss || Inventory[currentSelectedSlot].amount<1) return;

	int index = (int)RayCastInfo.HitFromPos.x / 16;
	glm::vec2 Pos((int)RayCastInfo.HitFromPos.x % 16, RayCastInfo.HitFromPos.y);
	if (glm::abs(Pos.x - Position.x) < 0.5 && glm::abs(Pos.y - Position.y) < 0.5) return;
	(*Chunk::CHUNKS)[index]->setblock(Pos, Inventory[currentSelectedSlot].Type);
	Inventory[currentSelectedSlot].amount -= 1;
	(*Chunk::CHUNKS)[index]->UpdateMesh();

}
void PlayerEntity::Draw(Shader& shader)
{
	DrawBlockSelect();
	mesh.Draw(shader, Position);
	
}

void PlayerEntity::ProcessInput(double deltaTime)
{


	crntTime = glfwGetTime();
	
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if ( crntTime - fly_cooldown >  0.5f)
		{
			Fly = !Fly;
			fly_cooldown = glfwGetTime();
		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (crntTime - break_cooldown > 0.08f)
		{
			BreakBlock();
			break_cooldown = glfwGetTime();
		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (crntTime - place_cooldown > 0.08f)
		{
			PlaceBlock();
			place_cooldown = glfwGetTime();
		}
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) 
	{
		std::cout<<"Breaking"<<std::endl;// for breakPoining
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (crntTime - InventoryCheck_cooldown > 0.5f)
		{
			for (int i = 0; i < 10; i++)
			{
				std::cout << Util::GetInstance()->BLOCKS[Inventory[i].Type].name + " : " << Inventory[i].amount << std::endl;
			}
			InventoryCheck_cooldown = glfwGetTime();
		}
		
	}


	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		currentSelectedSlot = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		currentSelectedSlot =1;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		currentSelectedSlot = 2;
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		currentSelectedSlot = 3;
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		currentSelectedSlot = 4;
	}
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		currentSelectedSlot = 5;
	}
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		currentSelectedSlot = 6;
	}
	else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		currentSelectedSlot = 7;
	}
	else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		currentSelectedSlot = 8;
	}
	else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
	{
		currentSelectedSlot = 9;
	}



	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//Position.x -= speed * deltaTime;
		TryMoveRight(-speed * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//Position.x += speed * deltaTime;
		TryMoveRight(speed * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 10.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 6.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && Fly)
	{
		//Position.y += speed * deltaTime;
		TryMoveUp(speed * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && Fly)
	{
		//Position.y -= speed * deltaTime;
		TryMoveUp(-speed * deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//Position.y -= speed * deltaTime;
		TryMoveUp(20 * deltaTime);

	}

}
