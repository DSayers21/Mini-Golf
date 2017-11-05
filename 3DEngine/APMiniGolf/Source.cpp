//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <Window.h>
#include <MainComp.h>

#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	D3DEngine::Window m_Window;
	std::string Title = "Hello";
	m_Window.Init(Title, 800, 600);
	D3DEngine::MainComp m_MainComp(m_Window);
	m_MainComp.Start();
	return 0;
}