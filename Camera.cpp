#include "Camera.h"
Camera::Camera(glm::vec3 position) {
	Position = position;


}
void Camera::UpdateView(Shader& shaderProgram)
{

	view = glm::lookAt(Position, Position + glm::vec3(0.0f, 0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	proj = glm::ortho(-32.0f  , 32.0f , -18.0f, 18.0f , 0.1f, 100.0f);


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}
void Camera::GetUniformLocations(Shader & shaderProgram)
{
	shaderProgram.Activate();
	 modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	 viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	 projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	std::cout << "proj : " << projLoc << "view: " << viewLoc << "model: " << modelLoc << std::endl;

}
int  Camera::GetModelUniformLocation()
{
	return modelLoc;
}



