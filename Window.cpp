#include "Window.h"

#include <GL\freeglut.h>

static std::map<int, Window*> windows;

Window::Window() : id(-1), app(nullptr) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //give main window settings - GLUT_DOUBLE - use double buffering
}

void Window::apiInit(int argc, char** argv) {
	glutInit(&argc, argv); //pass command line options for glut 
}

void Window::init(const std::string& title, int width, int height, Application* app) {
	glutInitWindowSize(width, height); // set window size when not in fullscreen
	id = glutCreateWindow(title.c_str()); //create the main window and specify title
	this->app = app;
	app->onInit();
	windows[id] = this;
}

void Window::onDrawStatic() {
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->onDraw();
	}
	else {
		// TODO: print error
	}
}

void Window::onDraw() {
	std::cout << "sdasd " << std::endl;
	app->onDraw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Window::startMainLoop() {
	glutDisplayFunc(&Window::onDrawStatic);
	glutMainLoop();
}