#pragma once
#include "..\RawObject.h"
#include "..\Camera.h" 

class TexturedCube :
	public RawObject
{
public:
	TexturedCube(GLfloat width, GLfloat height, GLfloat length);
	TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* texture);
	TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag, const char* texture);
	~TexturedCube();

	void setMaterial(glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness);
private:
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shiness;

	GLuint diffuseMap;
	void setUniforms();
};

