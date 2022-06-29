#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
class Camera
{
	int modelLoc;
		
	int viewLoc;
		
	int projLoc;



public:
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);		//The Camera
	glm::mat4 proj = glm::mat4(1.0f);
	

	glm::vec3 Position;

	Camera(glm::vec3 position);
	void UpdateView(Shader& shaderProgram);

	void GetUniformLocations(Shader& shaderProgram);

	int GetModelUniformLocation();


};
