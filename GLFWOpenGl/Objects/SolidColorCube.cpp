#include "SolidColorCube.h"
#include "..\Camera.h"



SolidColorCube::SolidColorCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color)
	: Cube(width, height, length, "shaders/default.vert", "shaders/defaultLight.frag")
{
	this->color = glm::vec4(color, 1.0f);
}

SolidColorCube::~SolidColorCube()
{
}

void SolidColorCube::Draw()
{
	shader->Use();
	GLuint transformLoc = glGetUniformLocation(shader->get_programID(), "transform");
	GLint modelLoc = glGetUniformLocation(shader->get_programID(), "model");
	GLint viewLoc = glGetUniformLocation(shader->get_programID(), "view");
	GLint projectionLoc = glGetUniformLocation(shader->get_programID(), "projection");

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mainCamera.model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mainCamera.view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(mainCamera.projection));

	GLint objectColorLoc = glGetUniformLocation(shader->get_programID(), "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader->get_programID(), "lightColor");
	glUniform3f(objectColorLoc, color.x, color.y, color.z);
	
	glm::vec3 lightColor(1, 1, 1);
	for (auto light : Light::lights)
		lightColor = lightColor * light->color;

	glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}