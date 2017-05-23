#pragma once
#include "..\RawObject.h"
class Cube :
	public RawObject
{
public:
	Cube(GLfloat width, GLfloat height, GLfloat length);
	Cube(GLfloat width, GLfloat height, GLfloat length, const char* vert, const char* frag);
	~Cube();
};

