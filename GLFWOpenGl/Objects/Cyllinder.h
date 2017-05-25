#pragma once
#include "..\RawObject.h"
class Cyllinder :
	public RawObject
{
public:
	Cyllinder(GLfloat radius, GLfloat height, GLuint segments);
	Cyllinder(GLfloat radius, GLfloat height, GLuint segments, const char* vert, const char* frag);
	~Cyllinder();
};

