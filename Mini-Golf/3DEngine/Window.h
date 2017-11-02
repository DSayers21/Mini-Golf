#pragma once

#include <tchar.h>
#include <string>
#include <glut.h>

namespace D3DEngine
{
	class Window
	{
	public:
		Window();
		~Window();

		void Init(std::string Title, int Width, int Height);
	};
}