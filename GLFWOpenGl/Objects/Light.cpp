#include "Light.h"
#include "..\Camera.h"
#include <iostream>

std::vector<Light*> Light::lights;

void Light::setUniforms() 
{
	Cube::setUniforms();
	GLint lightColorLoc = glGetUniformLocation(shader->get_programID(), "ourColor");
	glUniform3f(lightColorLoc, diffuse.x, diffuse.y, diffuse.z);
}

Light::Light()
	: Cube(0.1, 0.1, 0.1, "shaders/lightVert.vert", "shaders/lightFrag.frag")
{
}

void Light::addNewLight(glm::vec3 postion, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
{
	Light* light = new Light();
	light->translate(postion.x, postion.y, postion.z);
	light->ambient = ambientColor;
	light->diffuse = diffuseColor;
	light->specular = specularColor;
	lights.push_back(light);
}

Light::~Light()
{
}

