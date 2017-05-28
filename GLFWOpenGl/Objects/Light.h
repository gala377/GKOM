#pragma once
#include "Cube.h"
class Light :
	public Cube
{
public:
	static void addNewLight(glm::vec3 postion, glm::vec3 ambientColor = glm::vec3(0.1), glm::vec3 diffuseColor = glm::vec3(1.0), glm::vec3 specularColor = glm::vec3(1.0), GLfloat constantPow = 1, GLfloat lineraPow = 0.1, GLfloat quadraticPow = 0.032);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;


	static std::vector<Light*> lights;
	~Light();
private:
	void setUniforms();
	Light();

};

