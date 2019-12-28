#include "Window.h"
#include "Camera.h"

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

void Window::onKeyDownSpecialStatic(int key, int x, int y) {
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->onKeyDown(key);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::onKeyDownStatic(unsigned char key, int x, int y) {
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->onKeyDown(key);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::onPassiveMouseMotionStatic(int x, int y) {
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->onPassiveMouseMotion(x, y);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::onDraw() {
	app->onDraw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Window::onKeyDown(int key) {
	app->onKeyDown(key);
}

void Window::onPassiveMouseMotion(int x, int y) {
	app->onPassiveMouseMotion(x, y);
}

// Later
//void Window::onMouseWheel(){}

void Window::startMainLoop() {
	glutDisplayFunc(&Window::onDrawStatic);
	glutKeyboardFunc(&Window::onKeyDownStatic);
	glutSpecialFunc(&Window::onKeyDownSpecialStatic);
	glutPassiveMotionFunc(&Window::onPassiveMouseMotionStatic);
	glutMainLoop();
}