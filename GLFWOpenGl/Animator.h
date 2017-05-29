#pragma once
#include <vector>
#include "RawObject.h"
#include <GLFW\glfw3.h>
#include <math.h>

class Animator
{
public:
	struct Frame {
		glm::vec3 transaltion;
		glm::vec4 rotation;
		GLfloat speed;

		glm::vec3 translatedBy;
		GLfloat rotatedBy;
	};

	bool loop = false;

	Animator();
	~Animator();

	void addObject(RawObject* obj);
	void removeObject(RawObject* obj);

	void addFrame(Frame f);
	void start();

	void update();
private:
	GLint currentFrame = -1;
	GLfloat currentFrameTime = 0.0f;
	GLfloat lastFrameTime;
	
	std::vector<RawObject*> objects;
	std::vector<Frame> frames;
	
	
	GLfloat updateFrame();
};

