#pragma once

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
		TextRendering(Window* Window);
		~TextRendering();

		void Render(std::string message, Vector3f color, int x, int y);

	private:
		Window* m_Window;
	};
}