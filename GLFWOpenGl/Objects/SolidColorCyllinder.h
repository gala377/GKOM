#pragma once
#include "..\RawObject.h"
#include "..\Camera.h"
#include "Light.h"

class SolidColorCyllinder : public RawObject
{
public:
	using RawObject::RawObject;
	void setColor(glm::vec4 color) {
		this->color = color;
	}
private:
	glm::vec4 color;
	void setUniforms()
	{
		RawObject::setUniforms();

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
			lightColor = lightColor * light->diffuse;
			lightPos = light->getPosition();
		}
		glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	}
};

