#pragma once
#include "..\RawObject.h"
#include "..\Camera.h"
#include "Light.h"
#include <string>

class MaterialRawObject :
	public RawObject
{
public:
	using RawObject::RawObject;
	~MaterialRawObject();

	void setMaterial(glm::vec3 ambientColor, glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness)
	{
		ambient = ambientColor;
		diffuse = diffColor;
		specular = specColor;
		this->shiness = shiness;
	}
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shiness;

	void setUniforms()
	{
		RawObject::setUniforms();

		GLint viewPosLoc = glGetUniformLocation(shader->get_programID(), "viewPos");

		GLint matAmbientLoc = glGetUniformLocation(shader->get_programID(), "material.ambient");
		GLint matDiffuseLoc = glGetUniformLocation(shader->get_programID(), "material.diffuse");
		GLint matSpecularLoc = glGetUniformLocation(shader->get_programID(), "material.specular");
		GLint matShineLoc = glGetUniformLocation(shader->get_programID(), "material.shininess");

		glUniform3f(matAmbientLoc, ambient.x, ambient.y, ambient.z);
		glUniform3f(matDiffuseLoc, diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(matSpecularLoc, specular.x, specular.y, specular.z);
		glUniform1f(matShineLoc, shiness);

		glUniform3f(viewPosLoc, mainCamera.cameraPos.x, mainCamera.cameraPos.y, mainCamera.cameraPos.z);

		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		std::string tableName = "pointLights";
		for (int i = 0; i < Light::lights.size(); i++)
		{
			std::string index = std::to_string(i);
			std::string fullName = tableName + "[" + index + "].";
			//std::cout << fullName << "\n";
			glUniform3f(glGetUniformLocation(shader->get_programID(), (fullName + "position").c_str()), Light::lights[i]->getPosition().x, Light::lights[i]->getPosition().y, Light::lights[i]->getPosition().z);
			glUniform3f(glGetUniformLocation(shader->get_programID(), (fullName + "ambient").c_str()), Light::lights[i]->ambient.x, Light::lights[i]->ambient.y, Light::lights[i]->ambient.z);
			glUniform3f(glGetUniformLocation(shader->get_programID(), (fullName + "diffuse").c_str()), Light::lights[i]->diffuse.x, Light::lights[i]->diffuse.y, Light::lights[i]->diffuse.z);
			glUniform3f(glGetUniformLocation(shader->get_programID(), (fullName + "specular").c_str()), Light::lights[i]->specular.x, Light::lights[i]->specular.y, Light::lights[i]->specular.z);
			glUniform1f(glGetUniformLocation(shader->get_programID(), (fullName + "constant").c_str()), Light::lights[i]->constant);
			glUniform1f(glGetUniformLocation(shader->get_programID(), (fullName + "linear").c_str()), Light::lights[i]->linear);
			glUniform1f(glGetUniformLocation(shader->get_programID(), (fullName + "quadratic").c_str()), Light::lights[i]->quadratic);
		}
	}
};

