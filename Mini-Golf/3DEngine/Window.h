#pragma once

#include <tchar.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>

namespace D3DEngine
{
	class Window
	{
	public:
		Window();
		~Window();

		void Init(std::string& Title, int Width, int Height);

		void SwapBuffers();

		void Update();

		void Clear(float R, float G, float B, float A);

		//Getters
		bool IsClosed() { return m_isClosed; }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_glContext;
		bool m_isClosed;

		int m_Width, m_Height;
	};
}