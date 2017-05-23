#pragma once
#include "Cube.h"
class Light :
	public Cube
{
public:
	Light(GLfloat r, GLfloat g, GLfloat b);
	~Light();

private:
	glm::vec3 color;
};

