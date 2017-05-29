#pragma once
#include <vector>
#include "RawObject.h"

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
private:
	std::vector<RawObject*> objects;
	std::vector<Frame> frames;
};

