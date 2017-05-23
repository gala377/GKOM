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

void Light::setUniforms() 
{
	Cube::setUniforms();
	GLint lightColorLoc = glGetUniformLocation(shader->get_programID(), "ourColor");
	glUniform3f(lightColorLoc, color.x, color.y, color.z);
}

Light::Light(GLfloat r, GLfloat g, GLfloat b)
	: Cube(0.1, 0.1, 0.1, "shaders/lightVert.vert", "shaders/lightFrag.frag")
{
	color = glm::vec3(r, g, b);
}

Light::~Light()
{
}

