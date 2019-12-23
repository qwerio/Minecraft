#pragma once

#include <string>
#include <iostream>
#include <map>

#include "Application.h"

#include <glm/vec3.hpp>
using namespace glm;

class Window;

class Window {
private:
	int id;
	Application* app;
	
public:
	Window();

	static void apiInit(int argc, char** argv);

	void init(const std::string& title, int width, int height, Application* app);

	static void onDrawStatic();

	void onDraw();
			
	void startMainLoop();
};