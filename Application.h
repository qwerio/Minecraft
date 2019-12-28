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
	Application() : frameIndex(0), height(480), width(640), lastX(0), lastY(0), firstMouse(true){

	}

	void onInit() {
		renderer.init();
	}

	void onDraw() {
		frameIndex++;
		// TODO: update scene
		// TODO: pass scene to renderer

		renderer.onRender(camera, settings, frameIndex);
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
	void onPassiveMouseMotion(int x, int y) {
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		else
		{
			camera.ProcessMouseMovement(x - lastX, lastY - y);
			lastX = x;
			lastY = y;
		}
	}

	//Later
	//void onMouseWheel() {}

private:
	int height;
	int width;
	int frameIndex;
	int lastX;
	int lastY;
	bool firstMouse = true;
	RenderSettings settings;
	Renderer renderer;
	Camera camera;
};