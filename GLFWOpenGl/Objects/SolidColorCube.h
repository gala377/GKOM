#pragma once
#include "Cube.h"
#include "Light.h"
class SolidColorCube :
	public Cube
{
public:
	SolidColorCube(GLfloat width, GLfloat height, GLfloat length, glm::vec3 color);
	~SolidColorCube();
	void Draw();
private:
	glm::vec4 color;

};

