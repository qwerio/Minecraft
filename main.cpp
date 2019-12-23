#include "Window.h"
#include "Renderer.h"
#include "Application.h"

#include <glm/vec3.hpp>
using namespace glm;

int main(int argc, char** argv)
{

	glutInit(&argc, argv); //pass command line options for glut 

	Window window;
	Application app;

	window.init("Minecraft", 640, 480, &app);
	window.startMainLoop();

	return 0;
}