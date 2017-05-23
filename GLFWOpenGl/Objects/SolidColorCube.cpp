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


void SolidColorCube::setUniforms()
{
	Cube::setUniforms();

	GLint objectColorLoc = glGetUniformLocation(shader->get_programID(), "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader->get_programID(), "lightColor");
	glUniform3f(objectColorLoc, color.x, color.y, color.z);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	for (auto light : Light::lights)
		lightColor = lightColor * light->color;

	glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
}
