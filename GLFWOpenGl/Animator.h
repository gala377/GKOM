#pragma once
#include <vector>
#include "RawObject.h"
#include <GLFW\glfw3.h>

class Animator
{
public:
	struct Frame {
		glm::vec3 transaltion;
		glm::vec4 rotation;
		GLfloat time;
	};

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
	void updateFrame();
};

