#pragma once

#include <string>
#include <iostream>
#include <map>
#include <chrono>

#include "Application.h"

#include <glm/vec3.hpp>
using namespace glm;

class Window;

class Window {
private:
	typedef std::chrono::steady_clock::time_point TimePoint;
	int id;
	float lastDelta;
	TimePoint deltaMarker;
	Application* app;
	
public:
	Window();
	
	void init(const std::string& title, const RenderSettings& settings, Application* app);
	static void apiInit(int argc, char** argv);
	
	static void onDrawStatic();
	static void onKeyDownStatic(unsigned char key, int x, int y);
	static void onKeyDownSpecialStatic(int key, int x, int y);
	static void onPassiveMouseMotionStatic(int x, int y);

	void onDraw();
	void onKeyDown(int key);
	void onPassiveMouseMotion(int x, int t);
	
	void startMainLoop();
};