#include "Window.h"
#include "Renderer.h"
#include "Application.h"

#include <glm/vec3.hpp>

using namespace glm;

int main(int argc, char** argv)
{
	Window::ApiInit(argc, argv);

	Window window;
	Application app;
	RenderSettings settings;

	settings.height = 1080;
	settings.width = 1920;
	settings.backGroundColor.x = 0.3f;
	settings.backGroundColor.y = 0.3f;
	settings.backGroundColor.z = 0.9f;
	settings.backGroundColor.w = 1.0f;

	window.Init("Minecraft", settings, &app);
	window.StartMainLoop();

	return 0;
}