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
	static void onKeyDownStatic(unsigned char key, int x, int y);
	static void onKeyDownSpecialStatic(int key, int x, int y);
	static void onMouseMotionStatic();
	static void onMouseWheelStatic();

	void onDraw();
	void onKeyDown(int key);
	void onMouseMotion();
	void onMouseWheel();
	
	void startMainLoop();
};