//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <MainComp.h>
#include "MiniGolf.h"

//Main update
#ifdef _WIN32
#undef main
#endif

int main(int argc, char** argv)
{
	//Create Title
	std::string Title = "Advanced Programming Assignment";
	//Create main component with a MiniGolf game
	D3DEngine::MainComp m_MainComp(Title, 1200, 800, 60, new MiniGolf());

	return 0;
}