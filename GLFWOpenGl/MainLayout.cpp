#include "MainLayout.h"

MainLayout::MainLayout(MainWindow* window) : parent(window) 
{
	glfwGetFramebufferSize(parent->window, &width, &height);
}

void MainLayout::Draw()
{
	for (RawObject* obj : objects)
		obj->Draw();
	for (Layout* lay : layouts)
		lay->Draw(parent);
}

void MainLayout::addLayout(Layout* lay)
{
	layouts.push_back(lay);
}

void MainLayout::addObject(RawObject* obj)
{
	objects.push_back(obj);
}