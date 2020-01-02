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
	void Init(const std::string& title, const RenderSettings& settings, Application* app);
	
	static void ApiInit(int argc, char** argv);
	static void OnDrawStatic();
	static void OnKeyDownStatic(unsigned char key, int x, int y);
	static void OnKeyDownSpecialStatic(int key, int x, int y);
	static void OnPassiveMouseMotionStatic(int x, int y);

	void OnDraw();
	void OnKeyDown(int key);
	void OnPassiveMouseMotion(int x, int t);
	
	void StartMainLoop();
};