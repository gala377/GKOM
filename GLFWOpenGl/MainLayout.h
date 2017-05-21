#pragma once
#include "MainWindow.h"
#include "RawObject.h"
#include "Layout.h"
#include <vector>

class MainLayout
{
public:
	MainLayout(MainWindow* window); 

	void Draw();
	void addLayout(Layout* lay);
	void addObject(RawObject* obj);
private:
	MainWindow* parent;
	int width;
	int height;

	std::vector<RawObject*> objects;
	std::vector<Layout*> layouts;
};

