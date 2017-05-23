#include "Light.h"
#include "..\Camera.h"
#include <iostream>

std::vector<Light*> Light::lights;

void Light::addNewLight(glm::vec3 postion, glm::vec3 color)
{
	Light* light = new Light(color.x, color.y, color.z);
	light->translate(postion.x, postion.y, postion.z);
	lights.push_back(light);
}

Light::Light(GLfloat r, GLfloat g, GLfloat b)
	: Cube(0.1, 0.1, 0.1, "shaders/lightVert.vert", "shaders/lightFrag.frag")
{
	color = glm::vec3(r, g, b);
}

Light::~Light()
{
}

void Light::Draw()
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

	GLint lightColorLoc = glGetUniformLocation(shader->get_programID(), "ourColor");
	
	std::cout << "colorx: " << color.x << " colory: " << color.y << " colorz: " << color.z << "\n";
	glUniform3f(lightColorLoc, color.x, color.y, color.z);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
