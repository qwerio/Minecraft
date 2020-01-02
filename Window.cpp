#include "Window.h"
#include "Camera.h"

#include <GL\freeglut.h>

static std::map<int, Window*> windows;

Window::Window() : id(-1), lastDelta(0), deltaMarker(std::chrono::steady_clock::now()), app(nullptr)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //give main window settings - GLUT_DOUBLE - use double buffering
}

void Window::ApiInit(int argc, char** argv) 
{
	glutInit(&argc, argv); //pass command line options for glut 
}

void Window::Init(const std::string& title, const RenderSettings& settings, Application* app)
{
	glutInitWindowSize(settings.width, settings.height); // set window size when not in fullscreen
	id = glutCreateWindow(title.c_str()); //create the main window and specify title
	this->app = app;
	app->OnInit(settings);
	windows[id] = this;
}

void Window::OnDrawStatic() 
{
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->OnDraw();
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::OnKeyDownSpecialStatic(int key, int x, int y) 
{
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->OnKeyDown(key);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::OnKeyDownStatic(unsigned char key, int x, int y) 
{
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->OnKeyDown(key);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::OnPassiveMouseMotionStatic(int x, int y) 
{
	int id = glutGetWindow();
	Window* window = windows[id];
	if (window) {
		window->OnPassiveMouseMotion(x, y);
	}
	else {
		std::cout << "Error Window Loading" << std::endl;
	}
}

void Window::OnDraw() 
{
	TimePoint currentTime = std::chrono::steady_clock::now();
	lastDelta = std::chrono::duration_cast<std::chrono::milliseconds> (currentTime - deltaMarker).count() * 0.001f;
	deltaMarker = currentTime;

	app->OnDraw(lastDelta);
	glutSwapBuffers();
	glutPostRedisplay();
}

void Window::OnKeyDown(int key) 
{
	app->OnKeyDown(key, lastDelta);
}

void Window::OnPassiveMouseMotion(int x, int y)
{
	app->OnPassiveMouseMotion(x, y);
}

void Window::StartMainLoop() 
{
	glutDisplayFunc(&Window::OnDrawStatic);
	glutKeyboardFunc(&Window::OnKeyDownStatic);
	glutSpecialFunc(&Window::OnKeyDownSpecialStatic);
	glutPassiveMotionFunc(&Window::OnPassiveMouseMotionStatic);
	glutMainLoop();
}