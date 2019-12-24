#pragma once

#include <iostream>
#include <math.h>

#include "Renderer.h"
#include "Camera.h"

#include <glm/vec3.hpp>

#include <GL\freeglut.h>

using namespace glm;

class Application {

public:
	Application() : frameIndex(0), height(480), width(640){

	}

	void onInit() {
		renderer.init();
	}

	void onDraw() {
		frameIndex++;
		// TODO: update scene

		// TODO: pass scene to renderer
		renderer.onRender(camera, vec3(0.0f,abs(sin(frameIndex * 0.01f)),1.0f), frameIndex);
	}

	void onKeyDown(int key) {
	
		switch (key) {
		case(GLUT_KEY_UP):
			camera.ProcessKeyboard(Camera_Movement::FORWARD, 0.016f);
			std::cout << "UP" << std::endl;
			break;
		case(GLUT_KEY_DOWN):
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.016f);
			std::cout << "DOWN" << std::endl;
			break;
		case(GLUT_KEY_RIGHT):
			camera.ProcessKeyboard(Camera_Movement::RIGHT, 0.016f);
			std::cout << "RIGHT" << std::endl;
			break;
		case(GLUT_KEY_LEFT):
			camera.ProcessKeyboard(Camera_Movement::LEFT, 0.016f);
			std::cout << "LEFT" << std::endl;
			break;
		}

	}
	void onMouseMotion() {}
	void onMouseWheel() {}

private:
	int height;
	int width;
	int frameIndex;
	Renderer renderer;
	Camera camera;
};