//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <MainComp.h>
#include "MiniGolf.h"

#include "GolfCourse.h"

#ifdef _WIN32
#undef main
#endif
const int COLOR_MODE_CYAN = 0;
int gColorMode = COLOR_MODE_CYAN;

int main(int argc, char** argv)
{
	std::string Title = "Advanced Programming Assignment";
	D3DEngine::MainComp m_MainComp(Title, 1200, 800, 120, new MiniGolf());

	return 0;
}