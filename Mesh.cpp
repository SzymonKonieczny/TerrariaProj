#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices_, std::vector < GLuint>& indices_)
{
	Mesh::vertices = vertices_;
	Mesh::indices = indices_;
	// Generates Vertex Array Object and binds it
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO1 = new VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO1 = new EBO(indices);

	// Links VBO to VAO
	VAO.LinkAttrib(*VBO1, 0, 3, GL_FLOAT,  sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(*VBO1, 1, 3, GL_FLOAT,  sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(*VBO1, 2, 2, GL_FLOAT,  sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

}
Mesh::Mesh()
{

	// Generates Vertex Array Object and binds it

	VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO1 = new VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO1 = new EBO(indices);

	// Links VBO to VAO
	VAO.LinkAttrib(*VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(*VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(*VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO1->Unbind();
	EBO1->Unbind();

}
void Mesh::Draw(Shader& shader, glm::vec2 Position)  {

	shader.Activate();
	VBO1->Rebuffer(vertices);
	EBO1->Rebuffer(indices);
	VAO.Bind();
	
	model = glm::translate(glm::vec3(Position, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));


	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VAO.Unbind();

}
