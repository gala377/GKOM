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

	void setShiness(GLfloat shiness);
private:
	GLfloat shiness;

	GLuint diffuseMap;
	GLuint	specularMap;
	void setUniforms();
};

