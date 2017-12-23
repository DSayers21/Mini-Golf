#pragma once

//Includes
#include <string>
#include <cstdlib>
#include <iostream>
#include <glut.h>

#include "Window.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class TextRendering
	{
	public:
		//Constructor
		TextRendering(Window* Window);
		//Destructor
		~TextRendering();
		//Render the text
		void Render(const std::string& message, Vector3f color, int x, int y);

	private:
		//Pointer to the window
		Window* m_Window;
	};
}