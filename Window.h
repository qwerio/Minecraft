#pragma once

#include <GL\freeglut.h>
#include <string>
#include <iostream>
#include <map>

#include "Application.h"

#include <glm/vec3.hpp>
using namespace glm;

class Window;

std::map<int, Window*> windows;

class Window {
private:
	int id;
	Application* app;
	
public:
	Window() : id(-1) {
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //give main window settings - GLUT_DOUBLE - use double buffering
	}

	void init(const std::string& title, int width, int height, Application* app) {
		glutInitWindowSize(width, height); // set window size when not in fullscreen
		id = glutCreateWindow(title.c_str()); //create the main window and specify title
		this->app = app;
		windows[id] = this;
	}

	static void onDrawStatic() {
		int id = glutGetWindow();
		Window* window = windows[id];
		if (window) {
			window->onDraw();
		}
		else {
			// TODO: print error
		}
	}

	void onDraw() {
		std::cout << "sdasd " << std::endl;
		app->onDraw();
		glutSwapBuffers();
		glutPostRedisplay();
	}
			
	void startMainLoop() {
		glutDisplayFunc(&Window::onDrawStatic);
		glutMainLoop();
	}
};