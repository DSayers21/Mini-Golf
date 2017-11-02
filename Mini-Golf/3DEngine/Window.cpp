#include "Window.h"



Window::Window()
{
}


Window::~Window()
{
}

void Window::Init(std::string Title)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 700);
	//glutFullScreen();
	glutCreateWindow(&Title[0]);


	glEnable(GL_DEPTH_TEST);
}
