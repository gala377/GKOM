#include "SolidColorCube.h"
#include "..\Camera.h"



SolidColorCube::SolidColorCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color)
	: Cube(width, height, length, "shaders/defaultLight.vert", "shaders/defaultLightSpecular.frag")
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
	GLint lightPosLoc = glGetUniformLocation(shader->get_programID(), "lightPos");
	GLint viewPosLoc = glGetUniformLocation(shader->get_programID(), "viewPos");

	glUniform3f(objectColorLoc, color.x, color.y, color.z);
	glUniform3f(viewPosLoc, mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos;
	for (auto light : Light::lights)
	{
		lightColor = lightColor * light->color;
		lightPos = light->getPosition();
	}
	glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
}
