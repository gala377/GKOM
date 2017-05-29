#pragma once
#include "..\RawObject.h"
#include "Light.h"
#include "..\Camera.h"
#include <soil.h>

class TexturedRawObject :
	public RawObject
{
public:
	using RawObject::RawObject;
	~TexturedRawObject();

	void setMaterial(const char* diffText, const char* specText, GLfloat shiness);
private:
	GLfloat shiness;

	GLuint diffuseMap;
	GLuint	specularMap;
	void setUniforms();
};

