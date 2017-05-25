#include "GNCube.h"
#include "..\Camera.h"
#include "Light.h"




GNCube::GNCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color)
	: Cube(width, height, length, "shaders/defaultLight.vert", "shaders/material.frag")
{
	this->color = glm::vec4(color, 1.0);
}

void GNCube::setMaterial(glm::vec3 ambientColor, glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness)
{
	ambient = ambientColor;
	diffuse = diffColor;
	specular = specColor;
	this->shiness = shiness;
}

GNCube::~GNCube()
{
}

void GNCube::setUniforms()
{
	Cube::setUniforms();

	GLint viewPosLoc = glGetUniformLocation(shader->get_programID(), "viewPos");

	GLint matAmbientLoc = glGetUniformLocation(shader->get_programID(), "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader->get_programID(), "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader->get_programID(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader->get_programID(), "material.shininess");

	GLint lightAmbientLoc = glGetUniformLocation(shader->get_programID(), "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(shader->get_programID(), "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(shader->get_programID(), "light.specular");
	GLint lightPosLoc = glGetUniformLocation(shader->get_programID(), "light.position");

	glUniform3f(matAmbientLoc, ambient.x, ambient.y, ambient.z);
	glUniform3f(matDiffuseLoc, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(matSpecularLoc, specular.x, specular.y, specular.z);
	glUniform1f(matShineLoc, shiness);

	glUniform3f(viewPosLoc, mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	for (auto light : Light::lights)
	{
		glUniform3f(lightPosLoc, light->getPosition().x, light->getPosition().y, light->getPosition().z);
		glUniform3f(lightAmbientLoc, light->ambient.x, light->ambient.y, light->ambient.z);
		glUniform3f(lightDiffuseLoc, light->diffuse.x, light->diffuse.y, light->diffuse.z );
		glUniform3f(lightSpecularLoc, light->specular.x, light->specular.y, light->specular.z);
	}
}
