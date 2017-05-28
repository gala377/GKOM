#pragma once
#include "..\RawObject.h"
#include "..\Camera.h" 

class TexturedCube :
	public RawObject
{
public:
	TexturedCube(GLfloat width, GLfloat height, GLfloat length);
	TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* diffText, const char* specText);
	TexturedCube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag, const char* diffText, const char* specText);
	~TexturedCube();

	void setMaterial(glm::vec3 diffColor, glm::vec3 specColor, GLfloat shiness);
private:
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shiness;

	GLuint diffuseMap;
	GLuint	specularMap;
	void setUniforms();
};

