#pragma once
#include "..\RawObject.h"
class ColorCube :
	public RawObject
{
public:
	ColorCube(GLfloat width, GLfloat height, GLfloat length);
	ColorCube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag);
	~ColorCube();
};

