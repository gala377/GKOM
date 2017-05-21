#pragma once
#include <GLFW\glfw3.h>
class RawObject
{
public:
	RawObject();
	~RawObject();
	virtual void Draw(GLuint VBO);
};

