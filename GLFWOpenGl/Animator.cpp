#include "Animator.h"



Animator::Animator()
{
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
