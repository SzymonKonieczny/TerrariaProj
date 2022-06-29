
#pragma once
#ifndef PLAYER_ENTITY.H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "GLOBAL.h"
#include"Collider.h"
#include "BlockSelectMesh.h"
#include"Camera.h"
#include "PlayerMesh.h"
#include "Entity.h"
#include "Ray.h"
#include "Window.h"
class PlayerEntity : public Entity
{
	Shader UIShader;
	GLFWwindow* window;
	Shader* UsedShader;
	int speed = 5;
	Collider collider;
	
	InvetorySlot Inventory[10];
	int currentSelectedSlot=0;
	void TryMoveRight(double distance);
	void TryMoveUp(double distance);
	bool Fly = false;
	float fly_cooldown = 0.5;
	float break_cooldown = 0.1;
	float place_cooldown = 0.1;
	float InventoryCheck_cooldown = 0.5;
	float crntTime = 0;
	float prevTime = 0;
	static double mouseX, mouseY;
	BlockSelectMesh blockSelectMesh;
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void DrawBlockSelect();
	void BreakBlock();
	void PlaceBlock();
	int FindViableInventorySlot(BlockType::BlockTypes Type);
	Ray::RayInfo RayCastInfo;
public:
	int WinHeight;
	int WinWidth;

	void CheckCollision();
	PlayerMesh mesh;

	Camera* camera;
	glm::vec2 Position;
	PlayerEntity(Shader& shader, GLFWwindow* window_);
	void UpdateCamera();
	void Update(double timeDiff) override;
	void Draw(Shader& shader) ;
	void ProcessInput(double deltaTime);
	
};



#endif // !PLAYER_ENTITY.H
