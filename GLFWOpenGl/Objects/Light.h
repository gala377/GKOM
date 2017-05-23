#pragma once
#include "Cube.h"
class Light :
	public Cube
{
public:
	static void addNewLight(glm::vec3 postion, glm::vec3 color);
	glm::vec3 color;
	static std::vector<Light*> lights;
	~Light();
	void Draw();
private:

	Light(GLfloat r, GLfloat g, GLfloat b);


};

