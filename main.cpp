#include "Window.h"
#include "Renderer.h"
#include "Application.h"

#include <glm/vec3.hpp>

using namespace glm;

int main(int argc, char** argv)
{
	Window::apiInit(argc, argv);

	Window window;
	Application app;
	RenderSettings settings;
	settings.height = 1080;
	settings.width = 1920;

	window.init("Minecraft", settings.width, settings.height, &app);
	window.startMainLoop();

	return 0;
}