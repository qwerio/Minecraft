#pragma once

#include <GL\freeglut.h>
#include <iostream>
#include <math.h>

#include "Renderer.h"

#include <glm/vec3.hpp>
using namespace glm;

class Application {

public:
	Application() : frameIndex(0) {

	}
	void onDraw() {
		frameIndex++;
		std::cout << "Application" << std::endl;
		// TODO: update scene

		// TODO: pass scene to renderer
		renderer.onRender(vec3(0.0f,abs(sin(frameIndex * 0.01f)),1.0f));
	}

private:
	int frameIndex;
	Renderer renderer;
};