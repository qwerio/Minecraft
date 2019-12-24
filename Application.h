#pragma once

#include <iostream>
#include <math.h>

#include "Renderer.h"

#include <glm/vec3.hpp>

using namespace glm;

class Application {

public:
	Application() : frameIndex(0) {

	}
	void onInit() {
		renderer.init();
	}

	void onDraw() {
		frameIndex++;
		// TODO: update scene

		// TODO: pass scene to renderer
		renderer.onRender(vec3(0.0f,abs(sin(frameIndex * 0.01f)),1.0f), frameIndex);
	}

private:
	int frameIndex;
	Renderer renderer;
};