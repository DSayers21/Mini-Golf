#include "Window.h"

namespace D3DEngine
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	void Window::Init(std::string Title, int Width, int Height)
	{
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(Width, Height);
		//glutFullScreen();
		glutCreateWindow(&Title[0]);


		glEnable(GL_DEPTH_TEST);
	}
}