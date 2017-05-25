#pragma once
#include "Cube.h"
class GNCube :
	public Cube
{
public:
	GNCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color);
	void setMaterial(glm::vec3 ambientColor, glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness);
	~GNCube();
private:
	glm::vec4 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shiness;
	void setUniforms();
};

