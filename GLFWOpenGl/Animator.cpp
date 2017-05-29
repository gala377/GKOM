#include "Animator.h"



Animator::Animator()
{
	lastFrameTime = glfwGetTime();
}

Animator::~Animator()
{
}

void Animator::addObject(RawObject * obj)
{
	objects.push_back(obj);
}

void Animator::removeObject(RawObject * obj)
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i] == obj)
			objects.erase(objects.begin()+i);
}

void Animator::addFrame(Frame f)
{
	frames.push_back(f);
}

void Animator::start()
{
	currentFrame = 0;
	lastFrameTime = glfwGetTime();
}

void Animator::update()
{
	if (currentFrame < 0)
		return;
	
	updateFrame();

	currentFrameTime += glfwGetTime() - lastFrameTime;
	lastFrameTime = glfwGetTime();
}

GLfloat Animator::updateFrame()
{
	bool nextFrame = true;
	const GLfloat epsilon = 0.000001;
	GLfloat currTime = glfwGetTime();

	for (RawObject* el : objects)
	{
		glm::vec3 translation = frames[currentFrame].transaltion - frames[currentFrame].translatedBy;
		glm::vec3 rotation = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)* glm::vec3(frames[currentFrame].rotation);

		if (glm::length(translation) > epsilon || glm::length(rotation) > epsilon)
			nextFrame = false;
		else {
			el->translate(translation.x, translation.y, translation.z);
			el->rotate(rotation.x, 1, 0, 0);
			el->rotate(rotation.y, 0, 1, 0);
			el->rotate(rotation.z, 0, 0, 1);
			continue;
		}

		GLfloat deltaTime = (currTime - lastFrameTime);
		GLfloat rotatedAngle = (frames[currentFrame].rotation.w - frames[currentFrame].rotatedBy)*frames[currentFrame].speed * deltaTime;;
		
		translation *= frames[currentFrame].speed * deltaTime;
		rotation *= frames[currentFrame].speed * deltaTime;

		el->translate(translation.x, translation.y, translation.z);
		el->rotate(rotation.x, 1, 0, 0);
		el->rotate(rotation.y, 0, 1, 0);
		el->rotate(rotation.z, 0, 0, 1);

		frames[currentFrame].translatedBy += translation;
		frames[currentFrame].rotatedBy += rotatedAngle;
	}

	if (nextFrame)
		currentFrame++;
	if (currentFrame == frames.size())
		currentFrame = loop ? 0 : -1;
			
	return currTime;
}
