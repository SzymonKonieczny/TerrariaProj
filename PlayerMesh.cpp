#include "PlayerMesh.h"

/*void PlayerMesh::Draw(Shader & shader, glm::vec2 & Position)
{
	shader.Activate();
	VBO1->Rebuffer(vertices);
	VAO.Bind();

	model = glm::translate( glm::vec3(Position.x , Position.y, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	VAO.Unbind();
	//std::cout << "PlayerMesh at : " << Position.x << " " << Position.y << std::endl;

}*/
auto subrange_to_float = [](auto word)->float {
	std::string w;
	for (auto c : word)
		w += c;
	return std::stof(w);
};

void PlayerMesh::Generate()
{

	
	std::filesystem::path modelPath = std::filesystem::current_path();
	modelPath /= "forplayermodel";
	modelPath /= "player.model";
	if (!std::filesystem::exists(modelPath))
	{	//Load default
		vertices = {
			{ glm::vec3(-0.4f,   +0.9f, 0.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0,1.f) },
			{ glm::vec3(0.4f,   +0.9f, 0.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0.125f, 1.f) },
			{ glm::vec3(0.4f,  -1.f, 0.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0.125f , 0) },
			{ glm::vec3(-0.4f,  -1.f, 0.0f),
				 glm::vec3(1.0f, 1.0f, 1.0f),
				 glm::vec2(0,0)},
		};

		indices = { 0,1,2,3,2,0 };
	}
	else
	{
	std::ifstream in(modelPath);
		std::string str;
		int vert_count = 0;
		int interationcounter = 0;
		while (in >> str)
		{
		auto coordinates = std::views::split(std::string_view(str), std::string_view(",")) | std::views::transform(subrange_to_float);

		float values[8];
		int i = 0;
			for (float c : coordinates| std::views::take(8)) 
			{
				values[i] = c;
				i++;
			}
			vertices.push_back({ glm::vec3(values[0], values[1], values[2]),
								glm::vec3(values[3], values[4], values[5]),
								glm::vec2(values[6],values[7])});

		
			if(interationcounter >= 3)
			{
			indices.push_back(vert_count);
			indices.push_back(vert_count + 1);
			indices.push_back(vert_count + 2);
			indices.push_back(vert_count + 3);
			indices.push_back(vert_count + 2);
			indices.push_back(vert_count);
			vert_count += 4;
			interationcounter = 0;
			}
			interationcounter++;
		}

	}


}
