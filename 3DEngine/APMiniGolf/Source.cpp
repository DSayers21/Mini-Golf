//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <MainComp.h>
#include "TestGame.h"

#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	std::string Title = "Advanced Programming Assignment";
	D3DEngine::MainComp m_MainComp(Title, 800, 600, 120, new TestGame());
	return 0;
}